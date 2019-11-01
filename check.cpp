#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include <random>
#include "check.h"
using namespace std;

void CHECK::check(double T_e, int N, double T) {
	int check_time_steps_int = N / T;
	double check_time_steps_double = N / T;
	int interval_e_int = double((1.0 * N / T))* T_e;
	double interval_e_double = double((1.0*N / T))*T_e;
	/*if (check_time_steps_int != check_time_steps_double) {
	cout << "please enter the correct time steps so that N/T is an integer" << endl;
	system("pause");
	exit(0);
	}*/
	if (/*check_time_steps_int == check_time_steps_double &&*/ T_e < (1 / check_time_steps_double)) {
		cout << "please enter correct T_e so that the time we check is more than the time we trade " << endl;
		system("pause");
		exit(0);

	}
	if (/*check_time_steps_int == check_time_steps_double &&*/ T_e < (1 / check_time_steps_double) && interval_e_int != interval_e_double) {
		cout << "please enter correct parameters so that the intervals till maturity date is an int" << endl;
		system("pause");
		exit(0);
	}

}