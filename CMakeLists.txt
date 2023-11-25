cmake_minimum_required(VERSION 3.26)
project(mlp_ia)

set(CMAKE_CXX_STANDARD 23)

add_executable(mlp_ia main.cpp
        RedeNeural.cpp
        Neuronio.cpp
        Neuronio.h
        RedeNeural.h)
