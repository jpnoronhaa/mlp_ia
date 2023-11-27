//
// Created by Joao Pedro Noronha on 26/11/23.
//

#include "Layer.h"
#include "Neuron.h"

Layer::Layer(int n_neurons, int n_weights) {
    this->initNeurons(n_neurons, n_weights);
}

Layer::~Layer() = default;

void Layer::initNeurons(int n_neurons, int n_weights) {
    for (int i = 0; i < n_neurons; i++) {
        m_neurons.push_back(Neuron(n_weights));
    }
}