//
// Created by Joao Pedro Noronha on 25/11/23.
//

#ifndef MLP_IA_NEURONIO_H
#define MLP_IA_NEURONIO_H

#endif //MLP_IA_NEURONIO_H

class Neuronio {
    private:
        double taxa;
        double *entradas;
        int qtEntradas;
        double *pesos;
        double saida;
    public:
        Neuronio();
        void setEntradas(double *valores);
        void setTxAprendizado(double valor);
        void setPeso(int i, double valor);
        double getTxAprendizado();
        double getSaida();
        double getPeso(int i);
        int getQtentradas();
        double getEntrada(int i);
        void iniciaNeuronio(int qtPesos);
        void propaga();
        void treina(double erro);
};