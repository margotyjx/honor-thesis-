#ifndef DEALTA_INCLUDED
#define DEALTA_INCLUDED

class DELTA
{
public:
	void delta1(double stockvalue_d, double strike_d, double interest_d, double volatility_d, double t, double maturity_d,
		double j, double step_d, double& account_d, double& x, double& putd_1, bool& hedged, double interval);

	void delta2(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
		double step_d, double& accountvalue_d, double& putd_1, double& x, double& calld_1, int interval_used_d, double time_left_d, double T_e_d);

	void delta3(double stockvalue_d, double strike_d, double strike_d2, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
		double step_d, double& accountvalue_d, double& putd_1, double& x, double& calld_1, int interval_used_d, double time_left_d, double T_e_d);

	void delta4(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
		double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d);

	void delta5(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
		double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d);

	void delta6(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
		double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d);

	void delta7(double stockvalue_d, double strike_d, double i_d, bool& hedged, double interest_d, double volatility_d, double t_d, double maturity_d,
		double step_d, double& accountvalue_d, double& putd_1, double& x, double& putd_2, int interval_used_d, double time_left_d, double T_e_d);
};






#endif // !DEALTA_H_INCLUDED

