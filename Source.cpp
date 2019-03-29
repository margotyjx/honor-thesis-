#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
using namespace std;

double Calloption1(double S_0, double T, double sigma, double r, double K, int n) {
	double sum = 0;
	for (int k = 0; k < n / 2;k++) {
		random_device rd;   // non-deterministic generator
		mt19937 gen(rd());  // to seed mersenne twister.
		uniform_real_distribution<double> dist(0.0, 1.0);
		double u1 = 2 * dist(gen) - 1;
		double u2 = 2 * dist(gen) - 1;
		double X = pow(u1, 2) + pow(u2, 2);
		while (X>1) {
			u1 = 2 * dist(gen) - 1;
			u2 = 2 * dist(gen) - 1;
			X = pow(u1, 2) + pow(u2, 2);
		}
		double Y = sqrt((-2 * log(X) / X));
		double U1 = Y * u1, U2 = Y * u2;

		double stock1 = S_0 * exp(T*(r - sigma*sigma*0.5) + sqrt(T* sigma*sigma)* U1);
		double stock2 = S_0 * exp(T*(r - sigma * sigma*0.5) + sqrt(T* sigma*sigma)* U2);

		sum = max(stock1 - K, 0.0) + max(stock2 - K, 0.0) + sum;
		//sum += max(stock1 - K, 0.0);
	}
	double price =  sum / n * exp(-r * T);
	return price;
}

double Calloption2(double S_0, double T, double sigma, double r, double K, int n) {
	//S_0 is the initial stock price, T is the expiration date, sigma is the volatility, r is the risk free rate 
	//random is a random number (0,1], K is the strike price at the expiry date

	//calculate the stock price at T using the formula 
	double sum = 0;
	for (int k = 0; k < n; k++) {
		random_device rd;   // non-deterministic generator
		mt19937 gen(rd());  // to seed mersenne twister.
		normal_distribution<double> dist(0.0, 1.0);
		double R = dist(gen);


		double stock = S_0 * exp(T*(r - sigma * sigma*0.5)) * exp(sqrt(T* sigma*sigma)* R);

		sum += (max(stock - K, 0.0)* exp(-r * T));
	}
	//add the payoff of all paths, calculate the average and discounted by the risk free rate 

	double price = (1.0* sum / n) ;
	return price;


}


int main() {
	double S_0 = 100.0;
	double K = 101.0;
	double T = 0.5;
	double sigma = 0.1;
	double r = 0.05;

	int n = 0;
	int N = 1000000;
	ofstream call;
	ofstream callCI;
	call.open("call.txt");
	callCI.open("callCI.txt");
	/*for (int k = 0; k < 1; k++) {
		callCI << Calloption1(S_0, T, sigma, r, K, n) << endl;
	}*/

	while (n < 1000) {
		callCI << Calloption1(S_0, T, sigma, r, K, n) << endl;
		n = 100 + n;
	}
	while (n >= 1000 && n <= 10000) {
		callCI << Calloption1(S_0, T, sigma, r, K, n) << endl;
		n += 1000;
	}
	while (n >= 10000 && n <= N) {
		callCI << Calloption1(S_0, T, sigma, r, K, n) << endl;
		n += 10000;
	}

	
	system("pause");
	return 0;
}