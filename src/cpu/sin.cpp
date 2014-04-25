#include <stdio.h>
#include <math.h>
#include "utils/TimeStat.h"
#include "utils/Table.h"

double sin_easy(const double x)
{
	double s=0.0;
	double a=1.0;
	for (int i = 1; i < 1024; i++) {
		a *= x/i;
		if (i%2) {
			a *= -1;
			s += a;
		}
	}
	return -s;
}

double sin_better(const double x)
{
	double s=x;
	double a=x;
	for (int i = 1; i < 512; i++) {
		//a *= -x*x/(2*i)/(2*i+1); // 2 div, 3 mul, slow
		a *= -x*x/((2*i)*(2*i+1)); // 1 div, 4 mul, fast
		s += a;
	}
	return s;
}

double sin_unroll4(const double x)
{
	double s=x;
	double a=x;
#pragma unroll(4)
	for (int i = 1; i < 512; i++) {
		//a *= -x*x/(2*i)/(2*i+1); // 2 div, 3 mul, slow
		a *= -x*x/((2*i)*(2*i+1)); // 1 div, 4 mul, fast
		s += a;
	}
	return s;
}

double sin_unroll8(const double x)
{
	double s=x;
	double a=x;
#pragma unroll(8)
	for (int i = 1; i < 512; i++) {
		//a *= -x*x/(2*i)/(2*i+1); // 2 div, 3 mul, slow
		a *= -x*x/((2*i)*(2*i+1)); // 1 div, 4 mul, fast
		s += a;
	}
	return s;
}

double sin_unroll16(const double x)
{
	double s=x;
	double a=x;
#pragma unroll(16)
	for (int i = 1; i < 512; i++) {
		//a *= -x*x/(2*i)/(2*i+1); // 2 div, 3 mul, slow
		a *= -x*x/((2*i)*(2*i+1)); // 1 div, 4 mul, fast
		s += a;
	}
	return s;
}

enum SINTYPE {
	EASY = 0,
	BETTER,
	UNROLL4,
	UNROLL8,
	UNROLL16,
	RAW
};

void time_sin(const int id, double *restrict data)
{
	const double x=0.5;
	const int num=100;
	TimeStat clk(num);
	const enum SINTYPE type = (enum SINTYPE) id;
	double s;
	for (int i = 0; i < num; i++) {
		switch (type) {
			case EASY:
				clk.tic();
				s=sin_easy(x);
				clk.toc();
				break;
			case BETTER:
				clk.tic();
				s=sin_better(x);
				clk.toc();
				break;
			case UNROLL4:
				clk.tic();
				s=sin_unroll4(x);
				clk.toc();
				break;
			case UNROLL8:
				clk.tic();
				s=sin_unroll8(x);
				clk.toc();
				break;
			case UNROLL16:
				clk.tic();
				s=sin_unroll16(x);
				clk.toc();
				break;
			case RAW:
				clk.tic();
				s=sin(x);
				clk.toc();
				break;
			default:
				break;
		}
	}
	data[0]=s;
	data[1]=clk.median();
	data[2]=clk.min();
	data[3]=clk.max();
}

void time_vecsin(double *restrict data)
{
	const double x=0.5;
	const int num=256;
	double sinx[num];
	TimeStat clk(1);
	clk.tic();
	// tune the num and the unroll parameters in lecture
#pragma unroll(8)
	for (int i = 0; i < num; i++)
		sinx[i]=sin(x);
	clk.toc();
	data[0]=sin(x);
	data[1]=clk.median()/num;
	data[2]=data[1];
	data[3]=data[1];
}

int main(int argc, char const* argv[])
{
	const int m = 7;
	const int n = 4;
	const char* rows[m] = {"easy","better","unroll4","unroll8","unroll16","raw","vec"};
	const char* cols[n] = {"sin(x)","median","min","max"};
	double data[m*n];
	for(int i=0; i < 6; i++)
		time_sin(i,data+n*i);
	time_vecsin(data+n*(m-1));

	Table table;
	table.dim(m, n);
	table.rows(rows);
	table.cols(cols);
	table.data(data);
	table.print("Compute sin(0.5), time cost in CPU cycles");

	printf("WARNING: Tune the num and the unroll pars in time_vecsin in lecture.\n");
	return 0;
}
