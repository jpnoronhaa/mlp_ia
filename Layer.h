//
// Created by Joao Pedro Noronha on 26/11/23.
//

#ifndef MLP_IA_LAYER_H
#define MLP_IA_LAYER_H

#include "Neuron.h"

class Layer {
    private:
        void initNeurons(int n_neurons, int n_weights);
        std::vector<Neuron> m_neurons;
    public:
        Layer(int n_neurons, int n_weights);
        ~Layer();

        std::vector<Neuron>& get_neurons() {
            return m_neurons;
        }
};


#endif //MLP_IA_LAYER_H
