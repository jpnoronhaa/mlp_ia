//
// Created by Joao Pedro Noronha on 25/11/23.
//

#ifndef MLP_IA_REDENEURAL_H
#define MLP_IA_REDENEURAL_H

#endif //MLP_IA_REDENEURAL_H

#include "Neuronio.h"

class RNA {
    private:
        double *entradas;
        int qtEntradas;
        Neuronio *camadaOculta;
        int qtCamadaOculta;
        Neuronio *camadaSaida;
        int qtCamadaSaida;
        double *saidasEsperadas;
    public:
    RNA(int valor1, int valor2, int valor3, double taxa);
    ~RNA();
    void montar(int valor1, int valor2, int valor3, double taxa);
    void setEntradas(double *valor);
    void setTxAprendizado(double valor);
    void setErroQuadratico(double valor);
    void setSaidasEsperadas(double *valor);
    int getQtEntradas();
    int getQtSaidas();
    int getQtNeuroniosSaidas();
    double getEntrada(int i);
    double getSaida(int i);
    double *getSaidas();
    void propaga(double *valoes);
    void treina(double *saidas);
    int WinnerTakesAll();
    void Salvar(char *filename);
    void Abrir(char *filename);
};