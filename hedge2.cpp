#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include "BSmodel.h"
#include"hedge2.h"
using namespace std;


BS putO;

void HEDGE2::hedge2_1(double stockvalue2, double strike2, bool& put_C, double k, double interest2, double volatility2, double maturity2,
	double steps, double& accountvalue2, double& put2_1, double& put2_2, int interval_used, double time_left, double T_e, double t) {

	put2_1 = putO.BS_put(strike2, interest2, maturity2 - t, volatility2, stockvalue2) * exp(-interest2 * t);

	if (stockvalue2 < strike2 && interval_used != 0) {
		//if the stock price is below strike price, and not at the maturity date.
		if (put_C == true) {
			//if we own an option, we do nothing
			put2_2 = putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t);
		}
		else {
			accountvalue2 -= (putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2* t));
			put2_2 = putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t);
			put_C = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
		}
	}

	if (stockvalue2 < strike2 && interval_used == 0 && k != steps) {
		//if the stock value is below the strike price, and at the maturity date
		if (put_C == true) {
			//if owns a put option, we exercise it and buy the same assets back:
			accountvalue2 += (((strike2 - stockvalue2) - putO.BS_put(strike2, interest2,T_e, volatility2, stockvalue2))*exp(-interest2 * t));
			put2_2 = putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2)*exp(-interest2 * t);
			put_C = true;

		}
		else {
			//if we do not owns a put option, we buy one with maturity period T_e.
			accountvalue2 -= (putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2) *exp(-interest2 * t));
			put2_2 = putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2) *exp(-interest2 * t);
			put_C = true;


		}
	}
	if (stockvalue2 < strike2 && interval_used == 0 && k == steps) {
		//if the stock value is below the strike price, and at the  final maturity date
		if (put_C == true) {
			//if owns a put option, we can exercise it without losing any money
			put2_2 = 0.0;
			put_C = false;
		}
		else {
			//if we do not owns a put option, we need to make up for the difference.
			accountvalue2 += ((stockvalue2 - strike2) *exp(-interest2 * maturity2));
			put2_2 = 0.0;
			put_C = false;
		}
	}


	if (stockvalue2 >= strike2 && interval_used != 0) {

		if (put_C == true) {
			accountvalue2 += (putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) *exp(-interest2 * t));
			put2_2 = 0.0;
			put_C = false;
			//if the stock price (account value) is above 100, but owns a put option, sell it.		
		}
		else {
			put2_2 = 0.0;
			put_C = false;
		}
	}

	if (stockvalue2 >= strike2 && interval_used == 0) {
		if (put_C == true) {
			// at the maturity date, if the stock price is above 100, we let the put option at hand expires
			//no matter if it's at the final maturity date
			put2_2 = 0.0;
			put_C = false;
		}
		else {
			put2_2 = 0.0;
			put_C = false;
		}
	}
	
}

//***********************************************************************************************************************************************************************
void HEDGE2::hedge2_2(double stockvalue2, double strike2, bool& put_C, double k, double interest2, double volatility2, double maturity2,
	double steps, double& accountvalue2, double& put2_1, double& put2_2, int interval_used, double time_left, double T_e, double t) {

	put2_1 = putO.BS_put(strike2, interest2, maturity2 - t, volatility2, stockvalue2) * exp(-interest2 * t);

	if (interval_used != 0) {
		if (stockvalue2 < (strike2*0.9)) {
			//if the stock price is below strike price, and not at the maturity date.
			if (put_C == true) {
				//if we own an option, we do nothing
				put2_2 = putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t);
				put_C = true;
			}
			else {
				accountvalue2 -= (putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t));
				put2_2 = putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t);
				put_C = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
			}
		}
		if (stockvalue2 > (strike2*1.1)) {

			if (put_C == true) {
				accountvalue2 += (putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) *exp(-interest2 * t));
				put2_2 = 0.0;
				put_C = false;
				//if the stock price (account value) is above 100, but owns a put option, sell it.		
			}
			else {
				put2_2 = 0.0;
				put_C = false;
			}
		}
		else {

		}

	}
	
	if (interval_used == 0) {
		if (k != steps) {
			//at exercise time
			if (stockvalue2 < strike2) {
				//if the stock value is below the strike price, and at the maturity date
				if (put_C == true) {
					//if owns a put option, we exercise it and buy the same assets back:
					accountvalue2 += (strike2 - stockvalue2) * exp(-interest2 * t);

					if (stockvalue2 < (strike2 * 0.9)) {
						accountvalue2 -= putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2)*exp(-interest2 * t);
						put2_2 = putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2)*exp(-interest2 * t);
						put_C = true;
					}
					else {
						put2_2 = 0.0;
						put_C = false;
					}
				}
				else {
					//if we do not owns a put option
					if (stockvalue2 < (strike2 * 0.9)) {
						accountvalue2 -= (putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2) *exp(-interest2 * t));
						put2_2 = putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2) *exp(-interest2 * t);
						put_C = true;
					}
					else {
						put2_2 = 0.0;
						put_C = false;
					}
				}
			}
			if (stockvalue2 >= strike2) {
				put2_2 = 0.0;
				put_C = false;
			}
		}

		//at the final maturity date
		else {
			if (stockvalue2 < strike2) {
				//if the stock value is below the strike price
				if (put_C == true) {
					//if owns a put option, we can exercise it without losing any money
					put2_2 = 0.0;
					put_C = false;
				}
				else {
					//if we do not owns a put option, we need to make up for the difference.
					accountvalue2 += ((stockvalue2 - strike2) *exp(-interest2 * maturity2));
					put2_2 = 0.0;
					put_C = false;
				}
			}
			else {
				put2_2 = 0.0;
				put_C = false;
			}
		}
	}
}

//********************************************************************************************************************************************
void HEDGE2::hedge2_3(double stockvalue2, double strike2, bool& put_C, double k, double interest2, double volatility2, double maturity2,
	double steps, double& accountvalue2, double& put2_1, double& put2_2, int interval_used, double time_left, double T_e, double t) {

	put2_1 = putO.BS_put(strike2, interest2, maturity2 - t, volatility2, stockvalue2) * exp(-interest2 * t);

	if (interval_used != 0) {
		if (stockvalue2 < (strike2*0.8)) {
			//if the stock price is below strike price, and not at the maturity date.
			if (put_C == true) {
				//if we own an option, we do nothing
				put2_2 = putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t);
				put_C = true;
			}
			else {
				accountvalue2 -= (putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t));
				put2_2 = putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) * exp(-interest2 * t);
				put_C = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
			}
		}
		if (stockvalue2 > (strike2*1.2)) {

			if (put_C == true) {
				accountvalue2 += (putO.BS_put(strike2, interest2, time_left, volatility2, stockvalue2) *exp(-interest2 * t));
				put2_2 = 0.0;
				put_C = false;
				//if the stock price (account value) is above 100, but owns a put option, sell it.		
			}
			else {
				put2_2 = 0.0;
				put_C = false;
			}
		}
		else {

		}

	}

	if (interval_used == 0) {
		if (k != steps) {
			//at exercise time
			if (stockvalue2 < strike2) {
				//if the stock value is below the strike price, and at the maturity date
				if (put_C == true) {
					//if owns a put option, we exercise it and buy the same assets back:
					accountvalue2 += (strike2 - stockvalue2) * exp(-interest2 * t);

					if (stockvalue2 < (strike2 * 0.8)) {
						accountvalue2 -= putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2)*exp(-interest2 * t);
						put2_2 = putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2)*exp(-interest2 * t);
						put_C = true;
					}
					else {
						put2_2 = 0.0;
						put_C = false;
					}
				}
				else {
					//if we do not owns a put option
					if (stockvalue2 < (strike2 * 0.8)) {
						accountvalue2 -= (putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2) *exp(-interest2 * t));
						put2_2 = putO.BS_put(strike2, interest2, T_e, volatility2, stockvalue2) *exp(-interest2 * t);
						put_C = true;
					}
					else {
						put2_2 = 0.0;
						put_C = false;
					}
				}
			}
			if (stockvalue2 >= strike2) {
				put2_2 = 0.0;
				put_C = false;
			}
		}

		//at the final maturity date
		else {
			if (stockvalue2 < strike2) {
				//if the stock value is below the strike price
				if (put_C == true) {
					//if owns a put option, we can exercise it without losing any money
					put2_2 = 0.0;
					put_C = false;
				}
				else {
					//if we do not owns a put option, we need to make up for the difference.
					accountvalue2 += ((stockvalue2 - strike2) *exp(-interest2 * maturity2));
					put2_2 = 0.0;
					put_C = false;
				}
			}
			else {
				put2_2 = 0.0;
				put_C = false;
			}
		}
	}
}
