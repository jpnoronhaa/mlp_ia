//
// Created by Joao Pedro Noronha on 26/11/23.
//

#include "Network.h"
#include "Neuron.h"
#include "Layer.h"
#include "random"

Network::Network() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    m_nLayers = 0;
}

Network::~Network() = default;

void Network::initialize_network(int n_inputs, int n_hidden, int n_outputs) {

    this->add_layer(n_hidden, n_inputs+1);

    this->add_layer(n_outputs, n_hidden+1);
}

void Network::add_layer(int n_neurons, int n_weights) {
    m_layers.push_back(Layer(n_neurons, n_weights));
    m_nLayers++;
}

std::vector<double> Network::forward_propagate(std::vector<double> inputs) {
    std::vector<double> new_inputs;
    for (size_t i = 0; i < m_nLayers; i++)  {
        new_inputs.clear();

        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();
        for (size_t j = 0; j < layer_neurons.size(); j++) {
            layer_neurons[j].activate(inputs);
            layer_neurons[j].transfer();
            new_inputs.push_back(layer_neurons[j].get_output());
        }
        inputs = new_inputs;
    }
    return inputs;
}

void Network::backward_propagate_error(std::vector<double> expected) {
    for (size_t i = m_nLayers; i --> 0;) {
        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();

        for (size_t j = 0; j < layer_neurons.size(); j++) {
            double error = 0.0;
            if (i == m_nLayers - 1) {
                error = expected[j] - layer_neurons[j].get_output();
            } else {
                for (auto& neuron : m_layers[i + 1].get_neurons()) {
                    error += (neuron.get_weights()[j] * neuron.get_delta());
                }
            }
            layer_neurons[j].set_delta(error * layer_neurons[j].transfer_derivative());
        }
    }
}

void Network::update_weights(std::vector<double> inputs, double l_rate) {
    for (size_t i = 0; i < m_nLayers; i++) {
        std::vector<double> new_inputs;
        if (i != 0) {
            for (auto &neuron: m_layers[i-1].get_neurons()) {
                new_inputs.push_back(neuron.get_output());
            }
        } else {
            new_inputs = std::vector<double>(inputs.begin(), inputs.end() - 1);
        }

        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();

        for (size_t j = 0; j < layer_neurons.size(); j++) {
            std::vector<double>& weights = layer_neurons[j].get_weights();
            for (size_t k = 0; k < new_inputs.size(); k++) {
                weights[k] += l_rate * layer_neurons[j].get_delta() * new_inputs[k];
            }
            weights.back() += l_rate * layer_neurons[j].get_delta();
        }
    }
}

void Network::train(std::vector<std::vector<double> >trainings_data, double l_rate, size_t n_epoch, size_t n_outputs) {
    for (size_t e = 0; e < n_epoch; e++) {
        double sum_error = 0;

        for (const auto &row: trainings_data) {
            std::vector<double> outputs = this->forward_propagate(row);
            std::vector<double> expected(n_outputs, 0.0);
            expected[static_cast<int>(row.back())] = 1.0;
            for (size_t i = 0; i < n_outputs; i++) {
                sum_error += static_cast<double>(std::pow((expected[i] - outputs[i]), 2));
            }
            this->backward_propagate_error(expected);
            this->update_weights(row, l_rate);
        }
        std::cout << "[>] epoch=" << e << ", l_rate=" << l_rate << ", error=" << sum_error << std::endl;
    }
}

int Network::predict(std::vector<double> input) {
    std::vector<double> outputs = this->forward_propagate(input);
    return std::max_element(outputs.begin(), outputs.end()) - outputs.begin();
}
