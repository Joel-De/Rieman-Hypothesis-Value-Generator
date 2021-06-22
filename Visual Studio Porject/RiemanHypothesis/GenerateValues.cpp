#include <iostream>
#include "GPUAccerlerated.cuh"
#include "CPUMultiThread.h"
#include "CPUSingleThread.h"

#include <iostream>
#include <fstream>




// Function to convert Complex struct to readable string
std::string ComplexToString(std::complex<double> number) {
	return std::to_string(number.real()) + ", " + std::to_string(number.imag());
}

int main() {

	double accuracy{ 5000 };
	double step{ 0.001 };
	double yMin = { 0 };
	double yMax = { 100 };
	
	clock_t start, end;
	double time_taken;
	std::vector <RiemanPair> results;

	start = clock();
	results = GenerateValuesSinlgeThread(yMin, yMax, step, accuracy);
	end = clock();
	time_taken = ((double)end - (double)start) / double(CLOCKS_PER_SEC);
	std::cout << "Time Taken for Single Thread:\t" + std::to_string( time_taken) << std::endl;


	start = clock();
	results = GenerateValuesMultiThread(yMin, yMax, step, accuracy, 8);
	end = clock();
	time_taken = ((double)end - (double)start) / double(CLOCKS_PER_SEC);
	std::cout <<"Time Taken for MultiThread:\t" +  std::to_string(time_taken) << std::endl;


	start = clock();
	results = GenerateValuesCuda(yMin, yMax, step, accuracy);
	end = clock();
	time_taken = ((double)end - (double)start) / double(CLOCKS_PER_SEC);
	std::cout << "Time Taken for CUDA:\t" + std::to_string(time_taken) << std::endl;
	
	
	std::ofstream myfile;
	myfile.open("example.csv");
	myfile << "Input,,,Output\n";
	myfile << "Real,Imaginary,,Real,Imaginary\n";


	for (auto &value : results) {
		myfile << ComplexToString(value.input) + ",," + ComplexToString(value.output) + "\n";
	}

	
	myfile.close();
	return 0;
	


}