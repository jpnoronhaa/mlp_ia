#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>

#define Training_Set_Size 20
#define PI 3.141592653589793238463
#define N 5
#define epsilon 0.05
#define epoch 50000

double c[N] = {};
double W[N] = {};
double V[N] = {};
double b = 0;

double sigmoid(double x) {
    return (1.0f / (1.0f + std::exp(-x)));
}

double f_theta(double x) {
    double result = b;
    for (int i = 0; i < N; i++) {
        result += V[i] * sigmoid(c[i] + W[i] * x);
    }
    return result;
}

void train(double x, double y) {
    for (int i = 0; i < N; i++) {
        W[i] = W[i] - epsilon * 2 * (f_theta(x) - y) * V[i] * x * (1 - sigmoid(c[i] + W[i] * x)) * sigmoid(c[i] + W[i] * x);
    }

    for (int i = 0; i < N; i++) {
        V[i] = V[i] - epsilon * 2 * (f_theta(x) - y) * sigmoid(c[i] + W[i] * x);
    }

    b = b - epsilon * 2 * f_theta((x) - y);

    for (int i = 0; i < N; i++) {
        c[i] = c[i] - epsilon * 2 * f_theta((x) - y) * V[i] * (1 - sigmoid(c[i] + W[i] * x)) * sigmoid(c[i] + W[i] * x);
    }
}

int main() {
    srand(time(nullptr));

    return 0;
}
