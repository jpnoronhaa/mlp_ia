//
// Created by Joao Pedro Noronha on 26/11/23.
//
#include "Neuron.h"
#include "Layer.h"

#ifndef MLP_IA_NETWORK_H
#define MLP_IA_NETWORK_H


class Network {
    private:
        size_t m_nLayers;
        std::vector<Layer> m_layers;
    public:
        Network();
        ~Network();

        void initialize_network(int n_inputs, int n_hidden, int n_outputs);
        void add_layer(int n_neurons, int n_weights);
        std::vector<double> forward_propagate(std::vector<double> inputs);
        void backward_propagate_error(std::vector<double> expected);
        void update_weights(std::vector<double> inputs, double l_rate);
        void train(std::vector<std::vector<double> > trainings_data, double l_rate, size_t n_epoch, size_t n_outputs);
        int predict(std::vector<double> input);

        void display_human();
};


#endif //MLP_IA_NETWORK_H
