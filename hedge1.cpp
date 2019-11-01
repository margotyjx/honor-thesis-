#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
#include"BSmodel.h"
#include"hedge1.h"
using namespace std;

BS putoption1;

void HEDGE::hedge1_1(double stockvalue1, double strike1, double i, bool& C, double interest1, double volatility1, double t, double maturity1,
	double step, double& accountvalue1,  double& put1_1, double& put1_2) {

	put1_1 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
	//this is the "put option" we sold

	if (stockvalue1 < strike1 && i != step) {
		if (C == true) {
			put1_2 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
			//if the stock price is below 100, and owns a put option, leave it, but the value changed.
		}
		else {
			accountvalue1 -= putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1* t);
			put1_2 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
			C = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
		}
	}

	if (stockvalue1 < strike1 && i == step) {
		//at the final maturity date, the stock price below 100
		if (C == true) {
			put1_2 = 0.0;
			C = false;
			//if the stock price is below 100, and owns a put option, exercise it, the value of put option we bought expires.
			//the company does not lose anything
		}
		else {
			accountvalue1 += (stockvalue1 - strike1) * exp(-interest1 *maturity1);
			put1_2 = 0.0;
		}
	}

	if (stockvalue1 >= strike1) {
		if (C == true) {
			accountvalue1 += putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
			put1_2 = 0.0;
			C = false; //if the stock price (account value) is above 100, but owns a put option, sell it.
		}
		else {
			put1_2 = 0.0;
		}
	}
	//accountvalue1 = accountvalue1 * exp(-interest1 * maturity1);
	
}

//***************************************************************************************************************************************************************
void HEDGE::hedge1_2(double stockvalue1, double strike1, double i, bool& C, double interest1, double volatility1, double t, double maturity1,
	double step, double& accountvalue1, double& put1_1, double& put1_2) {

	put1_1 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
	//this is the "put option" we sold

	if (i != step) {
		if (stockvalue1 < (strike1*0.9)) {
			if (C == true) {
				put1_2 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				C = true;
				//if the stock price is below 100, and owns a put option, leave it, but the value changed.
			}
			else {
				accountvalue1 -= putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				put1_2 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				C = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
			}
		}
		if (stockvalue1 > (strike1 * 1.1)) {
			if (C == true) {
				accountvalue1 += putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				put1_2 = 0.0;
				C = false;
			}
			else {
				put1_2 = 0.0;
				C = false;
			}
		}
		else {
		}
	}
	
	if (i == step) {
		if (stockvalue1 < strike1) {
			//at the final maturity date, the stock price below 100
			if (C == true) {
				put1_2 = 0.0;
				C = false;
				//if the stock price is below 100, and owns a put option, exercise it, the value of put option we bought expires.
				//the company does not lose anything
			}
			else {
				accountvalue1 += (stockvalue1 - strike1) * exp(-interest1 * maturity1);
				put1_2 = 0.0;
				C = false;
			}
		}
		else {
			put1_2 = 0.0;
			C = false;
		}
	}
}

//**********************************************************************************************************************************************
void HEDGE::hedge1_3(double stockvalue1, double strike1, double i, bool& C, double interest1, double volatility1, double t, double maturity1,
	double step, double& accountvalue1, double& put1_1, double& put1_2) {

	put1_1 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
	//this is the "put option" we sold

	if (i != step) {
		if (stockvalue1 < (strike1*0.8)) {
			if (C == true) {
				put1_2 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				C = true;
				//if the stock price is below 100, and owns a put option, leave it, but the value changed.
			}
			else {
				accountvalue1 -= putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				put1_2 = putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				C = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
			}
		}
		if (stockvalue1 > (strike1 * 1.2)) {
			if (C == true) {
				accountvalue1 += putoption1.BS_put(strike1, interest1, (maturity1 - t), volatility1, stockvalue1) * exp(-interest1 * t);
				put1_2 = 0.0;
				C = false;
			}
			else {
				put1_2 = 0.0;
				C = false;
			}
		}
		else {
		}
	}

	if (i == step) {
		if (stockvalue1 < strike1) {
			//at the final maturity date, the stock price below 100
			if (C == true) {
				put1_2 = 0.0;
				C = false;
				//if the stock price is below 100, and owns a put option, exercise it, the value of put option we bought expires.
				//the company does not lose anything
			}
			else {
				accountvalue1 += (stockvalue1 - strike1) * exp(-interest1 * maturity1);
				put1_2 = 0.0;
				C = false;
			}
		}
		else {
			put1_2 = 0.0;
			C = false;
		}
	}
}