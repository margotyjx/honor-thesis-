#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
#include"BSmodel.h"
#include"bull.h"
using namespace std;

BS putoption;


//********************************************************************************************************************************************
 

void Bull_spread::BULL3(double stockvalue_b, double strike_b1, double strike_b2, double i_b, bool& putb_C, double interest_b, double volatility_b, double t_b, double maturity_b,
double step_b, double& accountvalue_b, double& stock_b, double& putb_1, double& putb_2, int interval_used_b, double time_left_b, double T_e_b, double S_0){

	double put_b2 = putoption.BS_put(strike_b2, interest_b, (maturity_b - 0), volatility_b, S_0);

	putb_1 = putoption.BS_put(strike_b1, interest_b, (maturity_b - t_b), volatility_b, stockvalue_b)* exp(-interest_b * t_b); //"put option" we sold

	if (interval_used_b != 0) {
		if (stockvalue_b < strike_b2 - put_b2) {
			//if the stock price is below strike price, and not at the maturity date.
			if (putb_C == true) {
				//if we own an option, we do nothing
				putb_2 = putoption.BS_put(strike_b2, interest_b, time_left_b, volatility_b, stockvalue_b) * exp(-interest_b * t_b);

			}
			else {
				accountvalue_b -= (putoption.BS_put(strike_b2, interest_b, time_left_b, volatility_b, stockvalue_b) * exp(-interest_b * t_b));
				putb_2 = putb_2 = putoption.BS_put(strike_b2, interest_b, time_left_b, volatility_b, stockvalue_b) * exp(-interest_b * t_b);

				putb_C = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
			}
		}
		else {
			if (putb_C == true) {
				accountvalue_b += (putoption.BS_put(strike_b2, interest_b, time_left_b, volatility_b, stockvalue_b) * exp(-interest_b * t_b));
				putb_2 = 0.0;
				putb_C = false;
			}
			else {
				putb_2 = 0.0;
				putb_C = false;
			}
		}
	}

		if (interval_used_b == 0) {
			if (i_b != step_b) {
				//not at the final maturity
				if (stockvalue_b < strike_b2) {
					if (putb_C == true) {
						//if owns a put option, we exercise it and buy the same assets back:
						accountvalue_b += (strike_b2 - stockvalue_b)* exp(-interest_b *t_b);
						if (stockvalue_b < strike_b2 - put_b2) {
							accountvalue_b -= putoption.BS_put(strike_b2, interest_b, T_e_b, volatility_b, stockvalue_b)*exp(-interest_b * t_b);
							putb_2 = putoption.BS_put(strike_b2, interest_b, T_e_b, volatility_b, stockvalue_b)*exp(-interest_b * t_b);
							putb_C = true;
						}
						else {
							putb_2 = 0.0;
							putb_C = false;
						}
					}
					else {
						if (stockvalue_b < strike_b2 - putb_C) {
							accountvalue_b -= putoption.BS_put(strike_b2, interest_b, T_e_b, volatility_b, stockvalue_b)*exp(-interest_b * t_b);
							putb_2 = putoption.BS_put(strike_b2, interest_b, T_e_b, volatility_b, stockvalue_b)*exp(-interest_b * t_b);
							putb_C = true;
						}
						else {
							putb_2 = 0.0;
							putb_C = false;
						}
					}
				}
				if (stockvalue_b >= strike_b2) {
					putb_2 = 0.0;
					putb_C = false;
				}
			}
			else {
				putb_2 = 0.0;
				//at final maturity date
				if (stockvalue_b < strike_b1) {
					if (stockvalue_b < strike_b2) {
						if (putb_C == true) {
							accountvalue_b -= (strike_b1 - strike_b2) *exp(-interest_b * t_b);
							putb_C = false;
						}
						else {
							accountvalue_b -= (strike_b1 - stockvalue_b) * exp(-interest_b * t_b);
							putb_C = false;
						}
					}
					else {
						accountvalue_b -= (strike_b1 - stockvalue_b) * exp(-interest_b * t_b);
						putb_C = false;
					}
				}
				else {
					putb_C = false;
				}
			}
		}
		stock_b = 0.0;
}


