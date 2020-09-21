// Rieman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <complex>
#include <future>
#include <fstream>

double accuracy{ 5000 };
double step{0.001};
double yMin = {0};
double yMax = {150};


class Complex {




};


std::complex<double> Rieman (std::complex<double> s) {

    std::complex<double> value{ 0,0 };

    for (double x = 1; x < accuracy; x++) {

        value += (pow(-1.0, x + 1.0)) / (pow(x, s));

        //value += (1.0 / (pow(x, s)));

    }

    //value = value * (1.0 - (2.0 / (pow(2.0, s))));

    return value;

}


std::vector<std::string> Final_Values[10];






std::string toString(std::complex<double> i) {

    std::string value = ("(" + std::to_string(std::real(i)) + "," + std::to_string(std::imag(i)) + ")");

    //std::cout << value << std::endl;
    return value;
}

std::vector<std::string> DataCalc(double xlow, double xmax) {
    std::vector<std::string> valuesreturn;
    
    
    std::complex<double> ans{ 0,  0 };
    for (double real = xlow; real < xmax; real += step) {
        for (double x = yMin; x < yMax; x += step) {
            std::complex<double> value{ real,  x };
            ans = Rieman(value);
            std::string newal = (toString(value) + "\t\t" + toString(ans));
            valuesreturn.push_back(newal);
        }
    }


    return valuesreturn;



}

int main()
{




    yMax += step;
    

    //Multi-threading

    auto ftr = std::async(&DataCalc,0.0,0.1);
    auto ftr1 = std::async(&DataCalc, 0.1, 0.2);
    auto ftr2 = std::async(&DataCalc, 0.2, 0.3);
    auto ftr3 = std::async(&DataCalc, 0.3, 0.4);
    auto ftr4 = std::async(&DataCalc, 0.4, 0.5);
    auto ftr5 = std::async(&DataCalc, 0.5, 0.6);
    auto ftr6 = std::async(&DataCalc, 0.6, 0.7);
    auto ftr7 = std::async(&DataCalc, 0.7, 0.8);
    auto ftr8 = std::async(&DataCalc, 0.8, 0.9);
    auto ftr9 = std::async(&DataCalc, 0.9, 1+step);

    Final_Values[0] = ftr.get();
    Final_Values[1] = ftr1.get();
    Final_Values[2] = ftr2.get();
    Final_Values[3] = ftr3.get();
    Final_Values[4] = ftr4.get();
    Final_Values[5] = ftr5.get();
    Final_Values[6] = ftr6.get();
    Final_Values[7] = ftr7.get();
    Final_Values[8] = ftr8.get();
    Final_Values[9] = ftr9.get();
    std::ofstream outfile;
    outfile.open("C:\\Users\\Loels\\Desktop\\RiemanDense.txt");

    std::cout << " writing to file" << std::endl;


    for (auto& element : Final_Values) {
        for (std::string& text : element) {
            //std::cout << text << std::endl;
            outfile << text << std::endl;





        }
    }


    std::cout << "done" << std::endl;



    outfile.close();



}

