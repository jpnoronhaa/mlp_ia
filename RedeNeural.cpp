//
// Created by Joao Pedro Noronha on 25/11/23.
//
#include "cstdlib"
#include "cmath"
#include "cstdio"

#include "RedeNeural.h"

RNA::RNA(int valor1, int valor2, int valor3, double taxa) {
    entradas = nullptr;
    camadaOculta = nullptr;
    camadaSaida = nullptr;
    saidasEsperadas = nullptr;
    montar(valor1, valor2, valor3, taxa);
}

RNA::~RNA() {
    if (entradas != nullptr) free(entradas);
    if (camadaOculta != nullptr) delete camadaOculta;
    if (camadaSaida != nullptr) delete camadaSaida;
}

void RNA::montar(int valor1, int valor2, int valor3, double taxa) {
    qtEntradas = valor1;
    if (entradas != nullptr) free(entradas);
    entradas = nullptr;

    qtCamadaOculta = valor2;
    if (camadaOculta != nullptr) delete camadaOculta;
    camadaOculta = new Neuronio[qtCamadaOculta];

    qtCamadaSaida = valor3;
    if (camadaSaida != nullptr) delete camadaSaida;
    camadaSaida = new Neuronio[qtCamadaSaida];

    saidasEsperadas = nullptr;

    setTxAprendizado(taxa);

    for (int i = 0; i < qtCamadaOculta; ++i) {
        camadaOculta[i].iniciaNeuronio(qtEntradas + 1);
    }

    for (int i = 0; i < qtCamadaSaida; ++i) {
        camadaSaida[i].iniciaNeuronio(qtCamadaOculta + 1);
    }
}

void RNA::setEntradas(double *valor) {
    if (entradas != nullptr) free(entradas);
    entradas = (double*) malloc(sizeof(double)*(qtEntradas + 1));

    for (int i = 0; i < qtEntradas; ++i) {
        entradas[i+1] = valor[i];
    }
    entradas[0] = 1.0;

    for (int i = 0; i < qtCamadaOculta; ++i) {
        camadaOculta[i].setEntradas(entradas);
    }
}

void RNA::setTxAprendizado(double valor) {
    for (int i = 0; i < qtCamadaOculta; ++i) {
        camadaOculta[i].setTxAprendizado(valor);
    }

    for (int i = 0; i < qtCamadaSaida; ++i) {
        camadaSaida[i].setTxAprendizado(valor);
    }
}

void RNA::propaga(double *valores) {
    if (valores != nullptr) {
        setEntradas(valores);

        double *tmp = (double*) malloc(sizeof(double)*(qtCamadaOculta + 1));
        tmp[0] = 1.0;

        for (int i = 0; i < qtCamadaOculta; ++i) {
            camadaOculta[i].propaga();
            tmp[i+1] = camadaOculta[i].getSaida();
        }

        for (int i = 0; i < qtCamadaSaida; ++i) {
            camadaSaida[i].setEntradas(tmp);
            camadaSaida[i].propaga();
        }

        delete tmp;
    }
}

int RNA::getQtEntradas() {
    return qtEntradas;
}

int RNA::getQtSaidas() {
    return qtCamadaSaida;
}

int RNA::getQtNeuroniosSaidas() {
    return qtCamadaSaida;
}

double RNA::getEntrada(int i) {
    return entradas[i+1];
}

double RNA::getSaida(int i) {
    return camadaSaida[i].getSaida();
}

double *RNA::getSaidas() {
    double *result = (double*) malloc(sizeof(double)*qtCamadaSaida);
    for (int i = 0; i < qtCamadaSaida; ++i) {
        result[i] = camadaSaida[i].getSaida();
    }
    return result;
}

void RNA::setSaidasEsperadas(double *valor) {
    saidasEsperadas = valor;
}

void RNA::treina(double *saidas) {
    setSaidasEsperadas(saidas);

    double *delta = (double*) malloc(sizeof(double)*qtCamadaSaida);
    for (int i = 0; i < qtCamadaSaida; ++i) {
        delta[i] = (1.0 - pow(camadaSaida[i].getSaida(), 2))*(saidasEsperadas[i]-camadaSaida[i].getSaida());
        camadaSaida[i].treina(saidasEsperadas[i]-camadaSaida[i].getSaida());
    }

    double *erro = (double*) malloc(sizeof(double)*qtCamadaOculta);
    for (int i = 0; i < qtCamadaOculta; ++i) {
        erro[i] = 0.0;
        for (int j = 0; j < qtCamadaSaida; ++j) {
            erro[i] += delta[j]*camadaSaida[j].getPeso(i+1);
        }
        camadaOculta[i].treina(erro[i]);
    }

    free(delta);
    free(erro);
}

int RNA::WinnerTakesAll() {
    double max = -9999.9;
    int classe = -1;
    for (int i = 0; i < qtCamadaSaida; ++i) {
        if (camadaSaida[i].getSaida() > max) {
            max = camadaSaida[i].getSaida();
            classe = i;
        }
    }

    return classe;
}

void RNA::Salvar(char *filename) {
    FILE *saida = fopen(filename, "+w");

    if (saida != nullptr) {
        fprintf(saida, "%d\n", qtEntradas);
        fprintf(saida, "%d\n", qtCamadaOculta);
        fprintf(saida, "%d\n", qtCamadaSaida);
        fprintf(saida, "%lf\n", camadaOculta[0].getTxAprendizado());

        for (int i = 0; i < qtCamadaOculta; ++i) {
            for (int j = 0; j < qtEntradas; ++j) {
                fprintf(saida, "%lf\n", camadaOculta[i].getPeso(j));
            }
        }

        for (int i = 0; i < qtCamadaSaida; ++i) {
            for (int j = 0; j < qtCamadaOculta; ++j) {
                fprintf(saida, "%lf\n", camadaSaida[i].getPeso(j));
            }
        }
    } else {
        printf("O arquivo %s nao pode ser aberto!\n", filename);
        exit(1);
    }

    fclose(saida);
}

void RNA::Abrir(char *filename) {
    FILE *entrada = fopen(filename, "r");

    if (entrada != nullptr) {
        int valor1, valor2, valor3;
        double taxa;
        char *string = new char[100];
        int length = 0;
        int estado = 0;
        char ch;
        int pesosOculta = 0;
        int pesosSaida = 0;

        while((ch = fgetc(entrada)) != EOF) {
            if (ch == '\n') {
                string[length] = '\n';
                length = 0;
                if (estado == 0) {
                    valor1 = atoi(string);
                } else if (estado == 1) {
                    valor2 == atoi(string);
                } else if (estado == 2) {
                    valor3 = atoi(string);
                } else if (estado == 3) {
                    taxa = atof(string);
                    montar(valor1, valor2, valor3, taxa);
                } else if (estado - 4 < (valor1 + 1) * valor2) {
                    camadaOculta[pesosOculta].setPeso((estado - 4)%(valor1 + 1), atoi(string));
                    if ((estado - 4)%(valor1 + 1) == valor1) {
                        pesosOculta++;
                    }
                } else if (estado - ((valor1 + 1)*valor2 + 4) < (valor2 + 1)*valor3) {
                    camadaSaida[pesosSaida].setPeso((estado - ((valor1 + 1)*valor2+4))%(valor2 + 1), atof(string));
                    if ((estado - ((valor1 + 1)*valor2+4))%(valor2 + 1) == valor2) {
                        pesosSaida++;
                    }
                }
                estado++;
            } else {
                string[length++] = ch;
            }
        }

        free(string);
    } else {
        printf("O arquivo %s nao pode ser aberto!\n", filename);
        exit(1);
    }
    fclose(entrada);
}