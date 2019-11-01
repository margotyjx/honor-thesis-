#ifndef INBANK_INCLUDED
#define INBANK_INCLUDED

class BANK {
public:
	void inbank(double stockprice, double S_0, double interest, double maturity, double strike, double volatility, double t, double& accountvalue, double &stock, double &put_1);
};


#endif
