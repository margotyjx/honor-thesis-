#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
#include "BSmodel.h"

using namespace std;

double BS::BS_put(double K, double r, double time, double sigma, double stock) {
	double d_plus = (log(stock / K) + (r + 0.5*sigma*sigma)*time) / (sigma*sqrt(time));
	double d_minus = d_plus - sigma * (sqrt(time));
	double normal_minus_minus = 0.5* erfc(d_minus / sqrt(2));
	double normal_minus_plus = 0.5* erfc(d_plus / sqrt(2));
	double putoption = K * exp(-r * time)*normal_minus_minus - stock * normal_minus_plus;
	return putoption;
}

double BS::BS_call(double K, double r, double time, double sigma, double stock) {
	double d_plus = (log(stock / K) + (r + 0.5*sigma*sigma)*time) / (sigma*sqrt(time));
	double d_minus = d_plus - sigma * (sqrt(time));
	double normal_plus_minus = 0.5* erfc(-d_minus / sqrt(2));
	double normal_plus_plus = 0.5* erfc(-d_plus / sqrt(2));
	double calloption = stock * normal_plus_plus - K * exp(-r * time)*normal_plus_minus;
	return calloption;
}

double BS::N_d_plus(double K, double r, double time, double sigma, double stock) {
	double d_plus = (log(stock / K) + (r + 0.5*sigma*sigma)*time) / (sigma*sqrt(time));
	double normal_plus_plus = 0.5* erfc(-d_plus / sqrt(2));
	return normal_plus_plus;
}

double BS::N_d_minus(double K, double r, double time, double sigma, double stock) {
	double d_plus = (log(stock / K) + (r + 0.5*sigma*sigma)*time) / (sigma*sqrt(time));
	double d_minus = d_plus - sigma * (sqrt(time));
	double normal_plus_minus = 0.5* erfc(-d_minus / sqrt(2));
	return normal_plus_minus;
}