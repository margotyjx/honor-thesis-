#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
#include "BSmodel.h"
#include "inbank.h"
using namespace std;


BS option;



void BANK::inbank(double stockprice, double S_0, double interest, double maturity, double strike, double volatility, double t, double& accountvalue, double &stock, double &put_1) {
	
		if (stockprice >= strike) {
			accountvalue = accountvalue;
		}
		else {
			accountvalue += ((stockprice - strike) * exp(-interest * maturity));
		}
		stock = 0.0;
		put_1 = option.BS_put(strike, interest, maturity-t, volatility, stockprice);
		
}




