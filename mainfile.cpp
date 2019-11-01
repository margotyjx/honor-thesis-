#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iomanip>


#include "BSmodel.h"
#include "check.h"
#include"hedge1.h"
#include"hedge2.h"
#include"inbank.h"
#include "bull.h"
#include"delta.h"
using namespace std;


int main() {

	ofstream stockprice;
	ofstream accountvalue;
	ofstream accountvalue1_1;
	ofstream accountvalue1_2;
	ofstream accountvalue1_3;
	ofstream accountvalue2_1;
	ofstream accountvalue2_2;
	ofstream accountvalue2_3;
	ofstream bullvalue;
	ofstream deltavalue5;
	ofstream deltavalue7;

	stockprice.open("stock.txt");
	accountvalue.open("account.txt");
	accountvalue1_1.open("account1_1.txt");
	accountvalue1_2.open("account1_2.txt");
	accountvalue1_3.open("account1_3.txt");
	accountvalue2_1.open("account2_1.txt");
	accountvalue2_2.open("account2_2.txt");
	accountvalue2_3.open("account2_3.txt");
	bullvalue.open("bull.txt");
	deltavalue5.open("delta5.txt");
	deltavalue7.open("delta7.txt");


	ofstream company_profit_bank;
	ofstream company_profit_hedge1;
	ofstream company_profit_hedge2;
	ofstream company_profit_bull1;
	ofstream company_profit_delta1;
	

	/*ofstream average_bank;
	ofstream average_hedge1;
	ofstream average_hedge2;
	ofstream average_hedge_b;*/
	ofstream average_delta;

	/*ofstream var_hedge_b;
	ofstream var_bank;
	ofstream var_hedge1;
	ofstream var_hedge2;*/
	ofstream var_delta;
	

	company_profit_bank.open("bank.txt");
	company_profit_hedge1.open("hedge1.txt");
	company_profit_hedge2.open("hedge2.txt");
	company_profit_bull1.open("bull1.txt");
	company_profit_delta1.open("delta1.txt");

	/*average_bank.open("bankA.txt");
	average_hedge1.open("hedge1A.txt");
	average_hedge2.open("hedge2A.txt");
	average_hedge_b.open("bull1A.txt");*/
	average_delta.open("deltaA.txt");

	/*var_bank.open("bankV.txt");
	var_hedge1.open("hedge1V.txt");
	var_hedge2.open("hedge2V.txt");
	var_hedge_b.open("bull1V.txt");*/
	var_delta.open("deltaV.txt");


	company_profit_bank << "profit" << endl;
	company_profit_hedge1 << " profit1 " << setw(13) << " profit2 " << setw(13) << " profit3 " << endl;
	company_profit_hedge2 << " profit1" << setw(13) << " profit2 " << setw(13) << "profit3" << endl;
	company_profit_bull1 << "profit" << endl;
	company_profit_delta1 << "profit" << endl;

	/*average_bank << "average " << endl;
	average_hedge1 << "average " << endl;
	average_hedge2 << "average" << endl;
	average_hedge_b << "average" << endl;*/
	average_delta << "average" << endl;

	/*var_bank << "var " << endl;
	var_hedge1 << "var " << endl;
	var_hedge2 << "var " << endl;
	var_hedge_b << "var" << endl;*/
	var_delta << "var" << endl;

	BS put;
	CHECK test;
	HEDGE version1;
	HEDGE2 version2;
	BANK bank;
	Bull_spread version_b;
	DELTA version_d;

	double const S_0 = 100.0;
	double const K = 100.0;
	double const T = 20;
	double const sigma = 0.19;
	double const r = 0.0478;

	double const K2 = 90;

	double const T_e = 2; //in years, for each period, we buy put option that mature in T_e years. usually setting it less than 2 
						  //is more reasonable.

	int const N = 40;  //time steps 

	test.check(T_e, N, T);

	int interval_e = double((1.0* N / T)) * T_e; // total steps between two maturity dates, should be an integer
	double interval = (1.0*T) / N;// the interval that the company check the account to take action of protecting themselves 
	

	
	double* stock = NULL;
	stock = new double[N];


	int n = 100000;
	struct company {
		double A;
		double P_1;
		double P_2;
		double C_1;
	};

	company* account = NULL;
	account = new company[n];

	company* account1_1 = NULL;
	account1_1 = new company[n];
	company* account1_2 = NULL; 
	account1_2 = new company[n];
	company* account1_3 = NULL;
	account1_3 = new company[n];

	company* account2_1 = NULL;
	account2_1 = new company[n];
	company* account2_2 = NULL;
	account2_2 = new company[n];
	company* account2_3 = NULL;
	account2_3 = new company[n];

	company* account_b_1 = NULL;
	account_b_1 = new company[n];

	company* account_d_1 = NULL;
	account_d_1 = new company[n];
	company* account_d_5 = NULL;
	account_d_5 = new company[n];
	company* account_d_7 = NULL;
	account_d_7 = new company[n];

	/*for (int j = 0; j < 50; j++) {
		double sum = 0.0;
		double sum1 = 0.0;
		double sum2 = 0.0;
		double sum_b = 0.0;
		double sum_d = 0.0;*/

	for (int k = 0; k < n; k++) {
		double t = 0.0; //passed time 

		stock[0] = S_0;
		account1_1[k] = account1_2[k] = account1_3[k] = account2_1[k] = account2_2[k] = account2_3[k] = account_b_1[k] = account_d_1[k] = account[k] = 
		account_d_5[k] = account_d_7[k] ={ put.BS_put(K, r, (T - 0), sigma, S_0), put.BS_put(K, r, (T - 0), sigma, S_0), 0.0 , 0.0 }; //set the account as up-front fee

		//account_d[k] = { put.BS_put(K, r, (T - 0), sigma, S_0), put.BS_put(K, r, (T - 0), sigma, S_0), 0.0 , - 1.0 / put.N_d_plus(K, r, T_e, sigma, S_0)};
		double x5 , x7 = 0.0;



		bool put_C1, put_C2, put_C3 = false; // check whether the account owns a put option, starting with no option at hand at the begining. 
		bool C1, C2, C3 = false;
		bool putb_C = false;
		bool hedged_5, hedged_7 = false;
		double call = 0.0;

		for (int i = 1; i <= N; i++) {
			random_device rd;   // non-deterministic generator
			//mt19937 gen(5);
			mt19937 gen(rd());  // to seed mersenne twister.
			normal_distribution<double> distribution(0.0, 1.0);
			double normal = distribution(gen);
			stock[i] = stock[i - 1] * exp(interval*(r - sigma * sigma*0.5) + sqrt(interval* sigma*sigma)* normal);
		

			double stock_at_t = stock[i];// generate stock price at time t.


			t = t + interval;

			//double stock_at_t = S_0 - 5* interval*t;



			int interval_used = i % interval_e;
			double time_left = (interval_e - interval_used)* interval;

			stockprice << stock_at_t << endl;

			//double delta_call = put.N_d_plus(K, r, T - t, sigma, stock_at_t);
			//double delta_put = put.N_d_plus(K, r, T - t, sigma, stock_at_t) - 1;
			//cout << "  stock   " << stock_at_t << "    T-t    " << T - t << "  call   " << delta_call << "   put   " << delta_put << endl;


//**********************************************************************************************************************************************************************
			version1.hedge1_1(stock_at_t, K, i, C1, r, sigma, t, T, N, account1_1[k].A, account1_1[k].P_1, account1_1[k].P_2);
			version1.hedge1_2(stock_at_t, K, i, C2, r, sigma, t, T, N, account1_2[k].A, account1_2[k].P_1, account1_2[k].P_2);
			version1.hedge1_3(stock_at_t, K, i, C3, r, sigma, t, T, N, account1_3[k].A, account1_3[k].P_1, account1_3[k].P_2);

			accountvalue1_1 << account1_1[k].A << setw(13) << account1_1[k].P_1 << setw(13) << account1_1[k].P_2 << setw(13) << endl;
			accountvalue1_2 << account1_2[k].A << setw(13) << account1_2[k].P_1 << setw(13) << account1_2[k].P_2 << setw(13) << endl;
			accountvalue1_3 << account1_3[k].A << setw(13) << account1_3[k].P_1 << setw(13) << account1_3[k].P_2 << setw(13) << endl;


			version2.hedge2_1(stock_at_t, K, put_C1, i, r, sigma, T, N, account2_1[k].A, account2_1[k].P_1, account2_1[k].P_2, interval_used, time_left, T_e, t);
			version2.hedge2_2(stock_at_t, K, put_C2, i, r, sigma, T, N, account2_2[k].A, account2_2[k].P_1, account2_2[k].P_2, interval_used, time_left, T_e, t);
			version2.hedge2_3(stock_at_t, K, put_C3, i, r, sigma, T, N, account2_3[k].A, account2_3[k].P_1, account2_3[k].P_2, interval_used, time_left, T_e, t);

			accountvalue2_1 << account2_1[k].A << setw(13) << account2_1[k].P_1 << setw(13) << account2_1[k].P_2 << setw(13) << endl;
			accountvalue2_2 << account2_2[k].A << setw(13) << account2_2[k].P_1 << setw(13) << account2_2[k].P_2 << setw(13) << endl;
			accountvalue2_3 << account2_3[k].A << setw(13) << account2_3[k].P_1 << setw(13) << account2_3[k].P_2 << setw(13) << endl;


			//version_b.BULL(stock_at_t, K, K2, i, putb_C, r, sigma, t, T, N, account_b[k].A,account_b[k].S, account_b[k].P_1, account_b[k].P_2, interval_used, time_left, T_e, S_0);
			//bullvalue << account_b[k].A << setw(13) << account_b[k].P_1 << setw(13) << account_b[k].P_2 << setw(13) <<  endl;

			//version_d.delta5(stock_at_t, K, i, hedged_5, r, sigma, t, T, N, account_d_5[k].A, account_d_5[k].P_1, x5, account_d_5[k].P_2, interval_used, time_left, T_e);
			//version_d.delta7(stock_at_t, K, i, hedged_7, r, sigma, t, T, N, account_d_7[k].A, account_d_7[k].P_1, x7, account_d_7[k].P_2, interval_used, time_left, T_e);
			//deltavalue5 << account_d_5[k].A << setw(13) << account_d_5[k].P_2 << setw(13) << x5 << endl;
			//deltavalue7 << account_d_7[k].A << setw(13) << account_d_7[k].P_2 << setw(13) << x7 << endl;
			//deltavalue << stock_at_t << setw(13) << account_d_1[k].A << setw(13) << account_d_1[k].P_2 << setw(13) << x << endl;

		}
		//bank.inbank(stock[N], S_0, r, T, K, sigma, t, account[k].A, account[k].S, account[k].P_1);
		//accountvalue << account[k] << endl;

		company_profit_hedge1 << account1_1[k].A << setw(13) << account1_2[k].A << setw(13) << account1_3[k].A<< endl;
		company_profit_hedge2 << account2_1[k].A << setw(13) << account2_2[k].A << setw(13) << account2_3[k].A << endl;
		//company_profit_bank << account[k].A << endl;
		//company_profit_bull1 << account_b[k].A << endl;
		//company_profit_delta1 << account_d_1[k].A << endl;


		/*sum += account[k];
		sum1 += account1[k];
		sum2 += account2[k];
		sum_b += account_b[k];*/
		//sum_d += account_d_1[k].A;

	/*}
	/*double average = sum / n;
	double average1 = sum1 / n;
	double average2 = sum2 / n;
	double average_b = sum_b / n;

	sort(account, account + n);
	sort(account1, account1 + n);
	sort(account2, account2 + n);
	sort(account_b, account_b + n);
	double average_d = sum_d / n;
	average_delta << average_d << endl;


	sort(account_d, account_d + n, [](company a, company b) { return a.A < b.A; });

	int VaR = 0.05*n;

	/*var_bank << account[VaR] << endl;
	var_hedge1 << account1[VaR] << endl;
	var_hedge2 << account2[VaR] << endl;
	var_hedge_b << account_b[VaR] << endl;

	average_bank << average << endl;
	average_hedge1 << average1 << endl;
	average_hedge2 << average2 << endl;
	average_hedge_b << average_b << endl;
	var_delta << account_d[VaR].A << endl;
	//cout << account_d[VaR].A << endl;

	/*cout << account[VaR] << endl;
	cout << account1[VaR] << endl;
	cout << account2[VaR] << endl;*/
	}

	system("pause");
	return 0;
}