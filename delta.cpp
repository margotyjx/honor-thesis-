#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
#include"BSmodel.h"
#include"delta.h"
using namespace std;

BS BlackS;

//*****************************************************************************************************************************************************
//sell short stock for hedging
void DELTA::delta1(double stockvalue_d, double strike_d, double interest_d, double volatility_d, double t, double maturity_d,
	double j, double step_d, double& accountvalue_d, double& x, double& putd_1, bool& hedged, double interval) {

	double dv = x - (BlackS.N_d_plus(strike_d, interest_d, (maturity_d - t), volatility_d, stockvalue_d) - 1);
	double dp = BlackS.N_d_plus(strike_d, interest_d, (maturity_d - t), volatility_d, stockvalue_d) - 1;
	putd_1 = BlackS.BS_put(strike_d, interest_d, maturity_d - t, volatility_d, stockvalue_d)* exp(-interest_d * t);

	if (j != step_d) {
		//if it's not at the final maturity date
		if (dp < -0.5) {
			//if put option have delta < -0.5, having higher probability to be in-the-money, company loses profit
			if (hedged == true /*&& dv < -0.325 || dv > 0.325*/ ) {
				//if the portfolio have |delta|> 0.5, we upgrade the portfolio
				double new_x = BlackS.N_d_plus(strike_d, interest_d, (maturity_d - t), volatility_d, stockvalue_d) - 1;

				accountvalue_d -= ((new_x - x) * stockvalue_d)* exp(-interest_d * t);
				x = new_x;
				hedged = true;
			}
			/*if (hedged == true && dv > -0.325 && dv < 0.325) {
				// we leave it
			}*/
			if (hedged == false) {
				x = BlackS.N_d_plus(strike_d, interest_d, (maturity_d - t), volatility_d, stockvalue_d) - 1;

				accountvalue_d -= (x * stockvalue_d)*exp(-interest_d * t);
				hedged = true;
			}
		}
		
		else {
			// if the portfolio have delta > -0.5, we do not hedge it, the closer the delta of put to zero, the more likely companies earn profit 
			if (hedged == true) {		
				accountvalue_d += (x* stockvalue_d )*exp(-interest_d * t);
				
				x = 0.0;
				hedged = false;
			}
			if (hedged == false) {
				// we leave it
				x = 0.0;
				
			}
		}
	}


	if (j == step_d) {
		if (stockvalue_d < strike_d) {
			accountvalue_d += (x * stockvalue_d - (strike_d - stockvalue_d))*exp(-interest_d * t);
			hedged = false;
			x = 0.0;
		}
		else {
			accountvalue_d += (x * stockvalue_d)*exp(-interest_d * t);
			hedged = false;
			x = 0.0;
		}

	}
	//cout << "x: " << x << " y: " << y << endl;
	//cout << dv << endl;
}

//***********************************************************************************************************************************
//sell short call option at the beginning;

void DELTA::delta2(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
	double step_d, double& accountvalue_d, double& putd_1, double& x, double& calld_1, int interval_used_d, double time_left_d, double T_e_d
) {


	//double x = number of call option we bought/ sell short.
	//double dv = x - (put.N_d_plus(strike_d, interest_d, (maturity_d - t), volatility_d, stockvalue_d) - 1);
	putd_1 = BlackS.BS_put(strike_d, interest_d, maturity_d - t_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
	double dv;

	if (interval_used_d != 0) {

		if (hedged == true) {
			//if we own an option, we do nothing
			double new_x = -1.0 / BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d);
			accountvalue_d -= ((new_x - x) * BlackS.BS_call(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
			x = new_x;
			calld_1 = new_x * BlackS.BS_call(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
			hedged = true;


		}
		else {
			x = -1.0 / BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d);
			accountvalue_d -= (x* BlackS.BS_call(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
			calld_1 = x * BlackS.BS_call(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);

			hedged = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
		}
		dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d);
	}

	if (interval_used_d == 0) {
		if (i_d != step_d) {
			//exercise date but not the final maturity
			if (stockvalue_d < strike_d) {
				//when stockvalue_d < strike_d, we keep the premuim for selling the call option and sell short another call option with same strike price
				x = -1.0 / BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
				accountvalue_d -= (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				calld_1 = (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
				dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
				hedged = true;
			}


			if (stockvalue_d >= strike_d) {
				if (hedged == true) {
					// at exercise date, we sold short of call options, it will be exercised, we lose the difference between strike price and current per contract.
					accountvalue_d += x * (stockvalue_d - strike_d) * exp(-interest_d * t_d);
					x = -1.0 / BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
					calld_1 = (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
					hedged = true;
				}
				else {
					// if no call options have been sold short, we start to hedge
					x = -1.0 / BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
					calld_1 = (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
					hedged = true;
				}
			}
		}
		else {
			//at final maturity date
			dv = 1 + 0 * BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
			calld_1 = 0.0;
			if (stockvalue_d < strike_d) {
				if (hedged == true) {
					//at maturity date, we keep the premuium of call options but pay back policyholders;
					accountvalue_d -= (strike_d - stockvalue_d) *exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
				else {
					//if no call option is sold short, we still need to pay back our policyholders;
					accountvalue_d -= (strike_d - stockvalue_d) * exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
			}
			else {
				//if stockvalue >= strike price. 
				if (hedged == true) {
					// at exercise date,call options will be exercised, we lose the difference between strike price and current per contract
					accountvalue_d += x * (stockvalue_d - strike_d) * exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
				else {
					//if no call options were sold short, we leave it
					x = 0.0;
					hedged = false;
				}
			}
		}
	}
	
	cout << dv << endl;
}

//********************************************************************************************************************************************************************

void DELTA::delta3(double stockvalue_d, double strike_d, double strike_d2, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
	double step_d, double& accountvalue_d, double& putd_1, double& x, double& calld_1, int interval_used_d, double time_left_d, double T_e_d) {

	//double x = number of call option we bought/ sell short.
	double call_d = BlackS.BS_call(strike_d2, interest_d, maturity_d - 0, volatility_d, stockvalue_d);

	putd_1 = BlackS.BS_put(strike_d, interest_d, maturity_d - t_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
	double dv;

	if (interval_used_d != 0) {
		if (stockvalue_d < strike_d2 + call_d) {
			//if the stock price is below strike price, and not at the maturity date.
			if (hedged == true) {
				//if we own an option, we do nothing
				double new_x = -1.0 / BlackS.N_d_plus(strike_d2, interest_d, time_left_d, volatility_d, stockvalue_d);
				accountvalue_d -= ((new_x - x) * BlackS.BS_call(strike_d2, interest_d, time_left_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
				x = new_x;
				calld_1 = new_x * BlackS.BS_call(strike_d2, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
				hedged = true;


			}
			else {
				x = -1.0 / BlackS.N_d_plus(strike_d2, interest_d, time_left_d, volatility_d, stockvalue_d);
				accountvalue_d -= (x* BlackS.BS_call(strike_d2, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				calld_1 = x * BlackS.BS_call(strike_d2, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);

				hedged = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
			}
			dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d);
		}
		else {
			if (hedged == true) {
				accountvalue_d += (x * BlackS.BS_call(strike_d2, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				x = 0.0;
				calld_1 = 0.0;
				hedged = false;
			}
			else {
				x = 0.0;
				calld_1 = 0.0;
				hedged = false;
			}
		}
	}

	if (interval_used_d == 0) {
		if (i_d != step_d) {
			//exercise date but not the final maturity
			if (stockvalue_d < strike_d2) {
				//when stockvalue_d < strike_d2, we keep the premuim for selling the call option and sell short another call option with same strike price
				if (stockvalue_d < strike_d2 + call_d) {
					x = -1.0 / BlackS.N_d_plus(strike_d2, interest_d, T_e_d, volatility_d, stockvalue_d);
					accountvalue_d -= (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
					calld_1 = (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
					hedged = true;
				}
				else {
					x = 0.0;
					hedged = false;
					calld_1 = 0.0;
				}
			}
			if (stockvalue_d >= strike_d2) {
				if (hedged == true) {
					// at exercise date, we sold short of call options, it will be exercised, we lose the difference between strike price and current per contract.
					accountvalue_d += x * (stockvalue_d - strike_d) * exp(-interest_d * t_d);
					if (stockvalue_d < strike_d2 + call_d) {
						x = -1.0 / BlackS.N_d_plus(strike_d2, interest_d, T_e_d, volatility_d, stockvalue_d);
						accountvalue_d -= (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
						calld_1 = (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
						dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
						hedged = true;
					}
					else {
						x = 0.0;
						calld_1 = 0.0;
						hedged = false;
					}
				}
				else {
					// if no call options have been sold short, we leave it
					if (stockvalue_d < strike_d2 + call_d) {
						x = -1.0 / BlackS.N_d_plus(strike_d2, interest_d, T_e_d, volatility_d, stockvalue_d);
						accountvalue_d -= (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
						calld_1 = (x* BlackS.BS_call(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
						dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d);
						hedged = true;
					}
					else {
						x = 0.0;
						calld_1 = 0.0;
						hedged = false;
					}

				}
			}
		}
		else {
			//at final maturity date
			calld_1 = 0.0;
			if (stockvalue_d < strike_d) {
				accountvalue_d -= (strike_d - stockvalue_d * exp(-interest_d * t_d));

				if (stockvalue_d >= strike_d2) {
					if (hedged == true) {
						accountvalue_d += x * (stockvalue_d - strike_d2) * exp(-interest_d * t_d);
						x = 0.0;
						hedged = false;
					}
					else {
						x = 0.0;
						hedged = false;
					}

				}
				else {
					x = 0.0;
					hedged = false;
				}
			}
			else {
				//if stockvalue >= strike price. 
				if (stockvalue_d >= strike_d2) {
					if (hedged == true) {
						accountvalue_d += x * (stockvalue_d - strike_d2) * exp(-interest_d * t_d);
						x = 0.0;
						hedged = false;
					}
					else {
						x = 0.0;
						hedged = false;
					}
				}
				else {
					x = 0.0;
					hedged = false;
				}
			}
		}
	}

	//cout << dv << endl;
}

//***********************************************************************************************************************************************************************************************
//delta hedge using put, hedge whenever we check

void DELTA::delta4(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
	double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d) {


	//double x = number of call option we bought/ sell short.
	
	putd_1 = BlackS.BS_put(strike_d, interest_d, maturity_d - t_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
	double dv;

	if (interval_used_d != 0) {

		if (hedged == true) {
			//if we own an option, we do nothing
			double new_x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
			accountvalue_d -= ((new_x - x) * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
			putd_2 = new_x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
			x = new_x;
			hedged = true;


		}
		else {
			x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
			accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
			putd_2 = x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);

			hedged = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
		}
		dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
	}

	if (interval_used_d == 0) {
		if (i_d != step_d) {
			//exercise date but not the final maturity
			if (stockvalue_d < strike_d) {
				//when stockvalue_d < strike_d, we can exercise the option and hedge the position 
				accountvalue_d += x * (strike_d - stockvalue_d)* exp(-interest_d * t_d);
				x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
				accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
				dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
				hedged = true;
			}


			if (stockvalue_d >= strike_d) {
				if (hedged == true) {
					// at exercise date, if stock >= strike, the put expires worthless
					x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					accountvalue_d -= x * BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d);
					dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					hedged = true;
				}
			}
		}
		else {
			//at final maturity date
			dv = 1 + 0 * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d)-1);
			putd_2 = 0.0;
			if (stockvalue_d < strike_d) {
				if (hedged == true) {
					//at maturity date, we can exercise the put options
					accountvalue_d += (x -1.0)*(strike_d - stockvalue_d) *exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
				else {
					//if no put option at hand, we need to pay back our policyholders;
					accountvalue_d -= (strike_d - stockvalue_d) * exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
			}
			else {
				//if stockvalue >= strike price. 
				if (hedged == true) {
					// at exercise date, the put option at hand will expire worthless
					x = 0.0;
					hedged = false;
				}
				else {
					x = 0.0;
					hedged = false;
				}
			}
		}
	}

	//cout << dv << endl;
}

//*******************************************************************************************************************************************************************************
//delta hedge with same strike price when stock < strike

void DELTA::delta5(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
	double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d) {

	//double x = number of call option we bought/ sell short.
	putd_1 = BlackS.BS_put(strike_d, interest_d, maturity_d - t_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
	double dv;

	if (interval_used_d != 0) {
		if (stockvalue_d < strike_d) {
			//if the stock price is below strike price, and not at the maturity date.
			if (hedged == true) {
				//if we own an option, we adjust it
				double new_x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
				accountvalue_d -= ((new_x - x) * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
				x = new_x;
				putd_2 = new_x * BlackS.BS_call(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
				hedged = true;


			}
			else {
				x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
				accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				putd_2 = x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);

				hedged = true; //if the stock price is below 100 but does not owns a put option, buy one and set the bool to 1
			}
			dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d);
		}
		else {
			if (hedged == true) {
				accountvalue_d += (x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				x = 0.0;
				putd_2 = 0.0;
				hedged = false;
			}
			else {
				x = 0.0;
				putd_2 = 0.0;
				hedged = false;
			}
		}
	}

	if (interval_used_d == 0) {
		if (i_d != step_d) {
			//exercise date but not the final maturity
			if (stockvalue_d < strike_d) {
				//when stockvalue_d < strike_d2, and we have put options at hand, we can exercise them, and hedge again 
				if (hedged == true) {
					accountvalue_d += x * (strike_d - stockvalue_d)* exp(-interest_d * t_d);
					x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
					putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					hedged = true;
				}
				else {
					x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
					putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					hedged = true;
				}
			}
			if (stockvalue_d >= strike_d) {
				if (hedged == true) {
					// stock >= strike at the exercise date, the put option we have expires worthless
					x = 0.0;
					hedged = false;
					putd_2 = 0.0;

				}
				else {
					x = 0.0;
					putd_2 = 0.0;
					hedged = false;
				}
			}
		}
		else {
			// i == step_d at final maturity date
			dv = 1 + 0 * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
			putd_2 = 0.0;
			if (stockvalue_d < strike_d) {
				if (hedged == true) {
					accountvalue_d += (x - 1.0)*(strike_d - stockvalue_d) *exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
				else {
					accountvalue_d -= (strike_d - stockvalue_d)*exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
			}
			else {
				//if stockvalue >= strike price. 
				x = 0.0;
				hedged = false;
			}
		}
	}

	//cout << dv << endl;
}

//****************************************************************************************************************************************************
// delta hedge when no hedging was done

void DELTA::delta6(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
	double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d) {

	//double x = number of call option we bought/ sell short.
	putd_1 = BlackS.BS_put(strike_d, interest_d, maturity_d - t_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
	double dv;

	if (interval_used_d != 0) {
		if (stockvalue_d < strike_d) {
			//if the stock price is below strike price, and not at the maturity date.
			if (hedged == true) {
				//if we own an option, we leave it
				putd_2 = x * BlackS.BS_call(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
				hedged = true;
			}
			else {
				x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
				accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				putd_2 = x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);

				hedged = true; 
			}
			dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d);
		}
		else {
			if (hedged == true) {
				accountvalue_d += (x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				x = 0.0;
				putd_2 = 0.0;
				hedged = false;
			}
			else {
				x = 0.0;
				putd_2 = 0.0;
				hedged = false;
			}
		}
	}

	if (interval_used_d == 0) {
		if (i_d != step_d) {
			//exercise date but not the final maturity
			if (stockvalue_d < strike_d) {
				//when stockvalue_d < strike_d2, and we have put options at hand, we can exercise them, and hedge again 
				if (hedged == true) {
					accountvalue_d += x * (strike_d - stockvalue_d)* exp(-interest_d * t_d);
					x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
					putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					hedged = true;
				}
				else {
					x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
					putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
					dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
					hedged = true;
				}
			}
			if (stockvalue_d >= strike_d) {
				if (hedged == true) {
					// stock >= strike at the exercise date, the put option we have expires worthless
					x = 0.0;
					hedged = false;
					putd_2 = 0.0;

				}
				else {
					x = 0.0;
					putd_2 = 0.0;
					hedged = false;
				}
			}
		}
		else {
			// i == step_d at final maturity date
			dv = 1 + 0 * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
			putd_2 = 0.0;
			if (stockvalue_d < strike_d) {
				if (hedged == true) {
					accountvalue_d += (x - 1.0)*(strike_d - stockvalue_d) *exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
				else {
					accountvalue_d -= (strike_d - stockvalue_d)*exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
			}
			else {
				//if stockvalue >= strike price. 
				x = 0.0;
				hedged = false;
			}
		}
	}

	//cout << dv << endl;
}

//*****************************************************************************************************************************************
//different boundary than delta6

void DELTA::delta7(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
	double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d) {

	//double x = number of call option we bought/ sell short.
	putd_1 = BlackS.BS_put(strike_d, interest_d, maturity_d - t_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
	double dv;

	if (interval_used_d != 0) {
		if (stockvalue_d < (strike_d*0.8)) {
			//if the stock price is below strike price, and not at the maturity date.
			if (hedged == true) {
				//if we own an option, we leave it
				double new_x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
				accountvalue_d -= ((new_x - x) * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
				x = new_x;
				putd_2 = new_x * BlackS.BS_call(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);
				hedged = true;
			}
			else {
				x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) - 1);
				accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				putd_2 = x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d)* exp(-interest_d * t_d);

				hedged = true;
			}
			dv = 1 + x * BlackS.N_d_plus(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d);
		}
		if (stockvalue_d > strike_d) {
			if (hedged == true) {
				accountvalue_d += (x * BlackS.BS_put(strike_d, interest_d, time_left_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
				x = 0.0;
				putd_2 = 0.0;
				hedged = false;
			}
			else {
				x = 0.0;
				putd_2 = 0.0;
				hedged = false;
			}
		}
		else {
			
		}
	}

	if (interval_used_d == 0) {
		if (i_d != step_d) {
			//exercise date but not the final maturity
			if (stockvalue_d < strike_d) {
				//when stockvalue_d < strike_d2*0.9, and we have put options at hand, we can exercise them, and hedge again 
				if (hedged == true) {
					accountvalue_d += x * (strike_d - stockvalue_d)* exp(-interest_d * t_d);

					if (stockvalue_d < strike_d *0.9) {
						x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
						accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
						putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
						dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
						hedged = true;
					}
					else{
						x = 0.0;
						putd_2 = 0.0;
						hedged = false;
					}
				}
				else {
					if (stockvalue_d < strike_d * 0.9){
						x = -1.0 / (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
						accountvalue_d -= (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) * exp(-interest_d * t_d));
						putd_2 = (x* BlackS.BS_put(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d))* exp(-interest_d * t_d);
						dv = 1 + x * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
						hedged = true;
					}
					else{
						x = 0.0;
						putd_2 = 0.0;
						hedged = false;
					}
				}
			}
			if (stockvalue_d >= strike_d) {
					x = 0.0;
					putd_2 = 0.0;
					hedged = false;
			}
		}
		else {
			// i == step_d at final maturity date
			dv = 1 + 0 * (BlackS.N_d_plus(strike_d, interest_d, T_e_d, volatility_d, stockvalue_d) - 1);
			putd_2 = 0.0;
			if (stockvalue_d < strike_d) {
				if (hedged == true) {
					accountvalue_d += (x - 1.0)*(strike_d - stockvalue_d) *exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
				else {
					accountvalue_d -= (strike_d - stockvalue_d)*exp(-interest_d * t_d);
					x = 0.0;
					hedged = false;
				}
			}
			else {
				//if stockvalue >= strike price. 
				x = 0.0;
				hedged = false;
			}
		}
	}

	//cout << dv << endl;
}

