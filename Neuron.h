//
// Created by Joao Pedro Noronha on 26/11/23.
//
#include <iostream>
#include <vector>

#ifndef MLP_IA_NEURON_H
#define MLP_IA_NEURON_H


class Neuron {
    private:
        size_t m_nWeights;
        std::vector<double> m_weights;
        double m_activation;
        double m_output;
        double m_delta;

        void initWeights(int n_weights);

    public:
        Neuron(int n_weights);
        ~Neuron();

        void activate(std::vector<double> inputs);
        void transfer();
        double transfer_derivative() {
            return static_cast<double>(m_output * (1.0 - m_output));
        }

        std::vector<double>& get_weights() {
            return m_weights;
        }

        double get_output() {
            return m_output;
        }
        double get_activation() {
            return m_activation;
        }
        double get_delta() {
            return m_delta;
        }

        void set_delta(double delta) {
            m_delta = delta;
        }
};


#endif //MLP_IA_NEURON_H
