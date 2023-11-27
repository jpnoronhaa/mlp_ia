//
// Created by Joao Pedro Noronha on 26/11/23.
//

#include "Neuron.h"
#include <random>

Neuron::Neuron(int n_weights) {
    this->initWeights(n_weights);
    m_nWeights = n_weights;
    m_activation = 0;
    m_output = 0;
    m_delta = 0;
}

Neuron::~Neuron() = default;

void Neuron::initWeights(int n_weights) {

    for (int i = 0; i < n_weights; i++) {
        m_weights.push_back(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
    }
}

void Neuron::activate(std::vector<double> inputs) {
    m_activation = m_weights[m_nWeights-1];

    for (size_t i = 0; i < m_nWeights-1; i++) {
        m_activation += m_weights[i] * inputs[i];
    }
}

void Neuron::transfer() {
    m_output = 1.0f / (1.0f + std::exp(-m_activation));
}
