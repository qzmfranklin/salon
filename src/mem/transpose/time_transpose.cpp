#include <stdio.h>
#include <stdlib.h>
#include <mkl.h>
#include "utils/Table.h"
#include "transpose.h"

static void init_array(const int n, double *restrict a)
{
	for (int i = 0; i < n; i++)
			a[i] = (10.0*rand())/RAND_MAX;
}

enum TRANS_TYPE { EASY=0, BLOCK };
static const int TRANS_TYPE_SIZE=2;

// measure memory bw (in median) in bytes/cycle for (type, dim)
static double membw0(const int type, const int dim, double *restrict a)
{
	const num=10;
	TimeStat clk(num);
	for (int i = 0; i < num; i++) {
		switch ((enum TRANS_TYPE)type) {
			case EASY:
				clk.tic();
				trans_easy(dim,a);
				clk.toc();
				break;
			case BLOCK:
				clk.tic();
				trans_block(dim,a);
				clk.toc();
				break;
			default:
				break;
		}
	}
	return clk.median();
}

static void test_membw(const int dim, double *restrict data)
{
	double *a=(double*)mkl_malloc(sizeof(double)*dim*dim,64);
	assert(a);

	init_array(dim*dim,a);
	for (int i = 0; i < TRANS_TYPE_SIZE; i++)
		data[i] = membw0(i,dim,a);

	mkl_free(a);
}

int main(int argc, char const* argv[])
{ 
	const int m = 10;
	const int n = TRANS_TYPE_SIZE;
	const int dims[m]   = {16,64,128,256,512,1024,2003,2048,4045,4096};
	const char* rows[m] = {"16","64","128","256","512","1024","2003","2048","4045","4096"};
	const char* cols[n] = {"easy","block"};
	double data[m*n];

	#pragma omp parallel for 	\
	num_threads(8)			\
	default(none)			\
	shared(dims,m,n,data)
	for(int i=0; i < m; i++)
		test_membw(dims[i],data+i*n);

	Table table;
	table.dim(m, n);
	table.rows(rows);
	table.cols(cols);
	table.data(data);

	char banner[200]="memory bw of matrix transpose, in bytes/cycle";
	table.print(banner);
	return 0;
}
