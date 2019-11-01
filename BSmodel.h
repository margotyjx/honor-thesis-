#ifndef BSMODEL_INCLUDED
#define BSMODEL_INCLUDED

class BS {
public:
	double BS_put(double K, double r, double time, double sigma, double stock);
	double BS_call(double K, double r, double time, double sigma, double stock);
	double N_d_plus(double K, double r, double time, double sigma, double stock);
	double N_d_minus(double K, double r, double time, double sigma, double stock);
};


#endif
