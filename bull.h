#ifndef BULL_INCLUDED
#define BULL_INCLUDED

class Bull_spread
{
public:
	double BULL1(double stockvalue_b, double strike_b1, double strike_b2, double i_b, bool& C, double interest_b, double volatility_b, double t_b, double maturity_b,
		double step_b, double accountvalue_b);
	double BULL2(double stockvalue_b, double strike_b1, double strike_b2, double i_b, bool& putb_C, double interest_b, double volatility_b, double t_b, double maturity_b,
		double step_b, double accountvalue_b);

	void BULL3(double stockvalue_b, double strike_b1, double strike_b2, double i_b, bool& putb_C, double interest_b, double volatility_b, double t_b, double maturity_b,
		double step_b, double& accountvalue_b, double& stock_b, double& putb_1, double& putb_2, int interval_used_b, double time_left_b, double T_e_b, double S_0);

};

#endif // !BULL_INCLUDED

