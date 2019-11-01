#ifndef HEDGE1_INCLUDED
#define HEDGE1_INCLUDED

class HEDGE
{
public:

	void hedge1_1(double stockvalue1, double strike1, double i, bool& C, double interest1, double volatility1, double t, double maturity1,
		double step, double& accountvalue1, double& put1_1, double& put1_2);
	void hedge1_2(double stockvalue1, double strike1, double i, bool& C, double interest1, double volatility1, double t, double maturity1,
		double step, double& accountvalue1,  double& put1_1, double& put1_2);
	void hedge1_3(double stockvalue1, double strike1, double i, bool& C, double interest1, double volatility1, double t, double maturity1,
		double step, double& accountvalue1, double& put1_1, double& put1_2);

};

#endif // !HEDGE1_INCLUDED

