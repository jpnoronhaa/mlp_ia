//
// Created by Joao Pedro Noronha on 25/11/23.
//

#include "cstdlib"
#include "ctime"
#include "cmath"

#include "Neuronio.h"

Neuronio::Neuronio() {
    entradas = nullptr;
    pesos = nullptr;
    qtEntradas = 0;
    taxa = 0.1;
}

void Neuronio::setEntradas(double *valores) {
    entradas = valores;
}

void Neuronio::setTxAprendizado(double valor) {
    taxa = valor;
}

void Neuronio::setPeso(int i, double valor) {
    if (qtEntradas > 0 && pesos != nullptr) {
        pesos[i] = valor;
    }
}

double Neuronio::getTxAprendizado() {
    return taxa;
}

double Neuronio::getSaida() {
    return saida;
}

int Neuronio::getQtentradas() {
    return qtEntradas;
}

double Neuronio::getPeso(int i) {
    return pesos[i];
}

double Neuronio::getEntrada(int i) {
    if (entradas != nullptr) {
        return entradas[i];
    }
    return -1000.0;
}

void Neuronio::iniciaNeuronio(int qtPesos) {
    qtEntradas = qtPesos;
    if (pesos != nullptr) {
        free(pesos);
        pesos = nullptr;
    }
    pesos = (double*)malloc(sizeof(double)*qtEntradas);
    srand(time(nullptr));
    for (int i = 0; i < qtEntradas; ++i) {
        pesos[i] = (rand()%2001-1000)/1000.0;
    }
}

void Neuronio::propaga() {
    double soma = 0;
    for (int i = 0; i < qtEntradas; ++i) {
        soma += entradas[i] * pesos[i];
    }
    saida = tanh(soma);
}

void Neuronio::treina(double erro) {
    double delta = (1.0 - pow(saida, 2)) * erro;
    for (int i = 0; i < qtEntradas; ++i) {
        pesos[i] = pesos[i] + (taxa*entradas[i]*delta);
    }
}