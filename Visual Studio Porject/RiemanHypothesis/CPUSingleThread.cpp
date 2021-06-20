#include <complex>
#include <iostream>
#include <vector>
#include "CPUSingleThread.h"




std::complex<double> GenerateValue(std::complex<double> input, double accuracy) {

    std::complex<double> value{ 0,0 };
    for (double x = 1; x < accuracy; x++) {
        value += (pow(-1.0, x + 1.0)) / (pow(x, input));
    }
    return value;
}

std::vector <RiemanPair> GenerateValuesSinlgeThread(double ymin, double ymax, double step, double accuracy) {

    std::vector <RiemanPair> Results;
    for (double i = ymin; i <= ymax; i += step) {
        std::complex<double> input = { 0.5, i };

        RiemanPair Pair = RiemanPair(
            input,
            GenerateValue(input, accuracy)
        );

        Results.push_back(Pair);
    }

    return Results;
}

