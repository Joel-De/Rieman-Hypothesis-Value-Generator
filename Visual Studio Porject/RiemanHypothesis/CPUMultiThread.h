#pragma once

#include <complex>
#include <iostream>
#include <vector>
#include <CPUSingleThread.h>



std::vector <RiemanPair> GenerateValuesMultiThread(double ymin, double ymax, double step, double accuracy, int threadCount);