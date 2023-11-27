#include <iostream>
#include "cstdlib"
#include "fstream"
#include "string"
#include <vector>
#include "iterator"
#include <map>
#include <set>
#include "numeric"
#include "Network.h"


std::vector<std::vector<double> > load_data(std::string filename);
std::vector<double> evaluate_network(std::vector<std::vector<double> > dataset, int n_folds, double l_rate, int n_epoch, int n_hidden);
double accuracy_metric(std::vector<int> expect, std::vector<int> predict);

int main() {
    std::cout << "Neural Network" << std::endl;

    std::vector<std::vector<double> > data = load_data("iris.data");

    std::map<int, int> lookup;
    int index = 0;
    for (auto& vec : data) {
        std::pair<std::map<int, int>::iterator, bool> ret;
        ret = lookup.insert(std::pair<int, int>(static_cast<int>(vec.back()),index));
        vec.back() = static_cast<double>(ret.first->second);
        if (ret.second) {
            index++;
        }
    }

    int n_folds = 5;
    double l_rate = 0.3f;
    int n_epoch = 500;
    int n_hidden = 5;

    std::vector<double> scores = evaluate_network(data, n_folds, l_rate, n_epoch, n_hidden);

    double mean = std::accumulate(scores.begin(), scores.end(), decltype(scores)::value_type(0)) / static_cast<double>(scores.size());

    std::cout << "Mean accuracy: " << mean << std::endl;

    return 0;
}

std::vector<double> evaluate_network(std::vector<std::vector<double> > dataset, int n_folds, double l_rate, int n_epoch, int n_hidden) {

    std::vector<std::vector<std::vector<double> > > dataset_splits;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<double> scores;

    size_t fold_size = static_cast<unsigned int>(dataset.size() / n_folds);
    for (int i = 0; i < n_folds; i++) {
        std::vector<std::vector<double> > fold;
        while (fold.size() < fold_size) {
            int n = rand() % dataset.size();

            std::swap(dataset[n], dataset.back());
            fold.push_back(dataset.back());
            dataset.pop_back();
        }

        dataset_splits.push_back(fold);
    }

    for (size_t i = 0; i < dataset_splits.size(); i++) {
        std::vector<std::vector<std::vector<double> > > train_sets = dataset_splits;
        std::swap(train_sets[i], train_sets.back());
        std::vector<std::vector<double> > test_set = train_sets.back();
        train_sets.pop_back();

        std::vector<std::vector<double> > train_set;
        for (auto &set: train_sets) {
            for (auto& row : set) {
                train_set.push_back(row);
            }
        }

        std::vector<int> expected;
        for (auto& row: test_set) {
            expected.push_back(static_cast<int>(row.back()));
            row.back() = 42;
        }

        std::vector<int> predicted;

        std::set<double> results;
        for (const auto& row : train_set) {
            results.insert(row.back());
        }
        int n_outputs = results.size();
        int n_inputs = train_set[0].size() - 1;

        Network* network = new Network();
        network->initialize_network(n_inputs, n_hidden, n_outputs);
        network->train(train_set, l_rate, n_epoch, n_outputs);

        for (const auto& row: test_set) {
            predicted.push_back(network->predict(row));
        }

        scores.push_back(accuracy_metric(expected, predicted));
    }

    return scores;
}

double accuracy_metric(std::vector<int> expect, std::vector<int> predict) {
    int correct = 0;

    for (size_t i = 0; i < predict.size(); i++) {
        if (predict[i] == expect[i]) correct++;
    }

    return static_cast<double>(correct * 100.0f / predict.size());
}


std::vector<std::vector<double> > load_data(std::string filename) {
    std::ifstream data_file;
    data_file.open( filename);
    double sepal_length, sepal_width, petal_length, petal_width;
    char ch;
    std::string class_name;

    std::vector<std::vector<double> > data;

    if (data_file.is_open()) {
        while (data_file) {
            data_file >> sepal_length >> ch >> sepal_width >> ch >> petal_length >> ch >> petal_width >> ch
                      >> class_name;

            std::vector<double> line(5);
            line.push_back(sepal_length);
            line.push_back(sepal_width);
            line.push_back(petal_length);
            line.push_back(petal_width);

            if (class_name == "Iris-setosa") {
                line.push_back(1.0);
            } else if (class_name == "Iris-versicolor") {
                line.push_back(2.0);
            } else {
                line.push_back(3.0);
            }
            data.push_back(line);
        }
    }

    return data;
}