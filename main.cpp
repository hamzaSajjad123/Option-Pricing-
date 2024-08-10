#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <random>

struct optionParams{
    double S;
    double K;
    double r;
    double v;
    double T;
};

double monteCarloCall(const int nSim, const optionParams p){
    double drift = (p.r - 0.5 * p.v * p.v) * p.T;
    double diffusion = p.v * sqrt(p.T);

    double payoffSum = 0;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, 1);

    for(int i = 0; i < nSim; i++){
        double Z = distribution(generator);
        double SForward = p.S * exp(drift + diffusion * Z);

        payoffSum += std::max(SForward - p.K, 0.0);
    }

    return (payoffSum / nSim) * exp(-p.r * p.T);
}

int main(){
    optionParams params;
    params.S = 100;
    params.K = 100;
    params.r = 0.05;
    params.v = 0.2;
    params.T = 1;

    std::ofstream outFile("monteCarloResults.csv");
    outFile << "nSim,OptionPrice\n";

    for(int nSim = 100; nSim <= 10000; nSim += 100){
        double monte_price_call = monteCarloCall(nSim, params);
        outFile << nSim << "," << monte_price_call << "\n";
    }

    outFile.close();
    return 0;
}