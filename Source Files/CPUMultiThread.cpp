#include "CPUSingleThread.h"
#include <future>
#include <thread>
#include <future>




std::vector<std::shared_future<std::vector <RiemanPair>>> values;

std::vector <RiemanPair> GenerateValuesMultiThread(double ymin, double ymax, double step, double accuracy, int threadCount) {

    std::vector <RiemanPair> ReturnValues;
    double Sections = (ymax - ymin) / threadCount;

    for (int i = 0; i < threadCount; i++) {

        std::shared_future<std::vector <RiemanPair>> ret = std::async(&GenerateValuesSinlgeThread, i * (Sections), ((double)i + 1) * Sections, step, accuracy);
        values.push_back(ret);

    }

    for (std::shared_future<std::vector <RiemanPair>>& value: values){
        for (auto &pair : value.get()) {

            ReturnValues.push_back(pair);
        }
    }

    return ReturnValues;


}


