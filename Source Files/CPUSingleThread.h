#pragma once

#include <complex>
#include <iostream>
#include <vector>

//Struct containing a pair of input and output from the Rieman Zeta Function
struct RiemanPair {

    std::complex<double> input;
    std::complex<double> output;

    RiemanPair(std::complex<double> input_ , std::complex<double> output_) {
        input = input_;
        output = output_;

    }

};

std::complex<double> GenerateValue(std::complex<double> input, double accuracy);

std::vector <RiemanPair> GenerateValuesSinlgeThread(double ymin, double ymax, double step, double accuracy);