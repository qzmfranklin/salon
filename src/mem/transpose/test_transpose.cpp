#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "transpose.h"

static void init_array(const int n, double *restrict a)
{
	for (int i = 0; i < n; i++)
			a[i] = (10.0*rand())/RAND_MAX;
}

static void print_matrix(const int n, const double *restrict a)
{
	printf("    | ");
	for (int i = 0; i < n; i++)
		printf("%7d ",i);
	printf("\n");
	printf("------");
	for (int i = 0; i < n; i++)
		printf("--------");
	printf("\n");

	for (int i = 0; i < n; i++) {
		printf("%3d | ",i);
		for (int j = 0; j < n; j++)
			printf("%7.3f ",a[i+j*n]);
		printf("\n");
	}
	printf("\n");
}

static void copy_matrix(const int n, const double *restrict in, double *restrict out)
{
	for (int i = 0; i < n*n; i++)
		out[i] = in[i];
}

int test01(void)
{
	int err=0; 
        printf("TEST01\n");
        printf("	|Test trans_easy\n");

	const int n=5;
	double a[n*n], b[n*n];
	init_array(n*n,a);

	printf("a=\n");
	print_matrix(n,a);

	printf("b=trans_easy(a)=\n");
	copy_matrix(n,a,b);
	trans_easy(n,b);
	print_matrix(n,b);
	
        printf("END OF TEST01\n");
        printf("\n");
	return err;
}

double max_diff(const int n, const double *restrict a, const double *restrict b)
{
	double t=0.0;
	for (int i = 0; i < n*n; i++) {
		double x = fabs(a[i]-b[i]);
		if (x>t) t=x;
	}
	return t;
}

int test02(void)
{
	int err=0; 
        printf("TEST02\n");
        printf("	|Test trans_block\n");

	printf("\n");

	const int n=523;
	double a[n*n], b[n*n], c[n*n];
	init_array(n*n,a);

	printf("matrix size = %d\n",n);

	printf("b=trans_easy(a)\n");
	copy_matrix(n,a,b);
	trans_easy(n,b);

	printf("c=trans_block(a)\n");
	copy_matrix(n,a,c);
	trans_block(n,c);

	printf("max|b-c|=%f\n",max_diff(n,b,c));
	printf("\n");

        printf("END OF TEST02\n");
        printf("\n");
	return err;
}

int main(int argc, char const* argv[])
{
	test01();

	test02();

	return 0;
}
