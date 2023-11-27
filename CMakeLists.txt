cmake_minimum_required(VERSION 3.26)
project(mlp_ia)

set(CMAKE_CXX_STANDARD 23)

add_executable(mlp_ia main.cpp
        Neuron.cpp
        Neuron.h
        Layer.cpp
        Layer.h
        Network.cpp
        Network.h
)
