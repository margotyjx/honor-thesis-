#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
using namespace std;




int main() {
	ofstream method2;
	ofstream E;
	E.open("expected age'.txt");
	method2.open("method2.txt");
//*******************************************************************************************
//this part calculated stock price and account value at maturity date with the promised value
	
	for (int k = 0; k < 10; k++) {
		double S_0 = 100.0;
		double K = 100.0;
		double T = 20;
		double sigma = 0.19;
		double r = 0.0478;
		int N = 100000;
		double* stock = NULL;

		stock = new double[N]; //creat dynamic array to store value for stock prices.
		for (int i = 0; i < N; i++) {
			random_device rd;   // non-deterministic generator
			mt19937 gen(rd());  // to seed mersenne twister.
			normal_distribution<double> distribution(0.0, 1.0);
			double U = distribution(gen);
			stock[i] = S_0 * exp(T*(r - sigma * sigma*0.5) + sqrt(T* sigma*sigma)* U);

		}
		double A = 0.0;
		for (int i = 0; i < N; i++) {
			if (stock[i] > 100) {
				A = stock[i];
			}
			else A = 100;
		}


		//**********************************************************************************
		//this part calculated the actual need for annuity. 
		double sum_A = 0.0;
		double sum_W = 0.0;// both of them for calculating the adequate amount of annuity	

		for (int i = 0; i < N; i++) {
			random_device rd;
			mt19937 gen(rd());
			bernoulli_distribution dist1(0.0128805);
			bernoulli_distribution dist2(0.013891);
			bernoulli_distribution dist3(0.015034);
			bernoulli_distribution dist4(0.0163255);
			bernoulli_distribution dist5(0.017785);
			bernoulli_distribution dist6(0.0194835);
			bernoulli_distribution dist7(0.0214);
			bernoulli_distribution dist8(0.023456);
			bernoulli_distribution dist9(0.025639);
			bernoulli_distribution dist10(0.0280275);
			bernoulli_distribution dist11(0.030807);
			bernoulli_distribution dist12(0.0340275);
			bernoulli_distribution dist13(0.037602);
			bernoulli_distribution dist14(0.0415465);
			bernoulli_distribution dist15(0.0459585);
			bernoulli_distribution dist16(0.0510775);
			bernoulli_distribution dist17(0.0569275);
			bernoulli_distribution dist18(0.063357);
			bernoulli_distribution dist19(0.070367);
			bernoulli_distribution dist20(0.0868545);
			bernoulli_distribution dist21(0.0967355);
			bernoulli_distribution dist22(0.107898);
			bernoulli_distribution dist23(0.1204045);
			bernoulli_distribution dist24(0.134258);
			bernoulli_distribution dist25(0.1494365);
			bernoulli_distribution dist26(0.165899);
			bernoulli_distribution dist27(0.183593);
			bernoulli_distribution dist28(0.2024615);
			bernoulli_distribution dist29(0.2224385);
			bernoulli_distribution dist30(0.2424245);
			bernoulli_distribution dist31(0.262069);
			bernoulli_distribution dist32(0.2809955);
			bernoulli_distribution dist33(0.2988125);
			bernoulli_distribution dist34(0.315127);
			bernoulli_distribution dist35(0.332339);
			bool D[35] = { dist1(gen),dist2(gen),dist3(gen),dist4(gen),dist5(gen),dist6(gen),dist7(gen),dist8(gen),dist9(gen),dist10(gen),dist11(gen),dist12(gen),dist13(gen),dist14(gen),dist15(gen),
				dist16(gen), dist17(gen), dist18(gen), dist19(gen), dist20(gen), dist21(gen), dist22(gen), dist23(gen), dist24(gen), dist25(gen), dist26(gen), dist27(gen), dist28(gen), dist29(gen),
				dist30(gen), dist31(gen), dist32(gen),dist33(gen),dist34(gen),dist35(gen), };

			//whether the person will die next year starting from the maturtiy date 
			int a = 0;
			double W = 0.0;

			//double annuity = 1.0 / ((1 - exp(-r * 18.2)) / (1 - exp(-r)));


			sum_A += A;

			while (D[a] == 0 && a < 35) {

				W += A * exp(-r * a);

				a++;
			}

			sum_W += W;
		}
		double annuity = sum_A / (sum_W);
		//cout << sum_A << "and " << sum_W << endl;
		cout << "annuity is: " << annuity << endl;

		//*********************************************************************************************
		//this part is the actual output part, with the actual calculated annuity and death probability, the average
		//output for this part should be 0 if the "annuity" variable is fair.
		double sum = 0.0;

		for (int i = 0; i < N; i++) {
			random_device rd;
			mt19937 gen(rd());
			bernoulli_distribution dist1(0.0128805);
			bernoulli_distribution dist2(0.013891);
			bernoulli_distribution dist3(0.015034);
			bernoulli_distribution dist4(0.0163255);
			bernoulli_distribution dist5(0.017785);
			bernoulli_distribution dist6(0.0194835);
			bernoulli_distribution dist7(0.0214);
			bernoulli_distribution dist8(0.023456);
			bernoulli_distribution dist9(0.025639);
			bernoulli_distribution dist10(0.0280275);
			bernoulli_distribution dist11(0.030807);
			bernoulli_distribution dist12(0.0340275);
			bernoulli_distribution dist13(0.037602);
			bernoulli_distribution dist14(0.0415465);
			bernoulli_distribution dist15(0.0459585);
			bernoulli_distribution dist16(0.0510775);
			bernoulli_distribution dist17(0.0569275);
			bernoulli_distribution dist18(0.063357);
			bernoulli_distribution dist19(0.070367);
			bernoulli_distribution dist20(0.0868545);
			bernoulli_distribution dist21(0.0967355);
			bernoulli_distribution dist22(0.107898);
			bernoulli_distribution dist23(0.1204045);
			bernoulli_distribution dist24(0.134258);
			bernoulli_distribution dist25(0.1494365);
			bernoulli_distribution dist26(0.165899);
			bernoulli_distribution dist27(0.183593);
			bernoulli_distribution dist28(0.2024615);
			bernoulli_distribution dist29(0.2224385);
			bernoulli_distribution dist30(0.2424245);
			bernoulli_distribution dist31(0.262069);
			bernoulli_distribution dist32(0.2809955);
			bernoulli_distribution dist33(0.2988125);
			bernoulli_distribution dist34(0.315127);
			bernoulli_distribution dist35(0.332339);
			bool D[35] = { dist1(gen),dist2(gen),dist3(gen),dist4(gen),dist5(gen),dist6(gen),dist7(gen),dist8(gen),dist9(gen),dist10(gen),dist11(gen),dist12(gen),dist13(gen),dist14(gen),dist15(gen),
				dist16(gen), dist17(gen), dist18(gen), dist19(gen), dist20(gen), dist21(gen), dist22(gen), dist23(gen), dist24(gen), dist25(gen), dist26(gen), dist27(gen), dist28(gen), dist29(gen),
				dist30(gen), dist31(gen), dist32(gen),dist33(gen),dist34(gen),dist35(gen), };

			//whether the person will die next year starting from the maturtiy date 

			int a = 0;
			double W = 0.0;

			while (D[a] == 0 && a < 35) {

				W += annuity * A * exp(-r * a);

				a++;
			}

			sum += W;
		}
		cout << "average revenue is : " << (sum - sum_A) / N << endl;
	}

	system("pause");
	return 0;
}