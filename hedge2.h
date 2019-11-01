#ifndef HEDGE2_INCLUDED
#define HEDGE2_INCLUDED

class HEDGE2
{
public:

	void hedge2_1(double stockvalue2, double strike2, bool& put_C, double k, double interest2, double volatility2, double maturity2,
		double steps, double& accountvalue2, double& put2_1, double& put2_2, int interval_used, double time_left, double T_e, double t);
	void hedge2_2(double stockvalue2, double strike2, bool& put_C, double k, double interest2, double volatility2, double maturity2,
		double steps, double& accountvalue2, double& put2_1, double& put2_2, int interval_used, double time_left, double T_e, double t);
	void hedge2_3(double stockvalue2, double strike2, bool& put_C, double k, double interest2, double volatility2, double maturity2,
		double steps, double& accountvalue2, double& put2_1, double& put2_2, int interval_used, double time_left, double T_e, double t);
};


#endif // !HEDGE2_INCLUDED
#pragma once
