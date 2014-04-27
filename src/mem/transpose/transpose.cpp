#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static const int B=128;

static void swp(double *restrict a, double *restrict b)
{
	//*b = *b ^ *a;
	//*a = *b ^ *a;
	//*b = *b ^ *a;
	const double c=*a;
	*a=*b;
	*b=c;
}

void trans_easy(const int n, double *restrict a)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			swp(a+j+i*n,a+i+j*n);
}

static void transB_offdiag(const int lda, double *restrict a, double *restrict b)
{
	for (int i = 0; i < B; i++)
		for (int j = 0; j < B; j++)
			swp(a+j+i*lda,b+i+j*lda);
}

static void transB_diag(const int lda, double *restrict a)
{
	for (int i = 0; i < B; i++)
		for (int j = 0; j < i; j++)
			swp(a+j+i*lda,a+i+j*lda);
}

// matrix dimension must divide the block size B
void trans_block0(const int n, double *restrict a)
{
	assert(n%B==0);
	const int nB=n/B;

	for (int i = 0; i < nB; i++)
		transB_diag(n,a+i*B+i*B*n);
		//transB_diag(n,a+i*B*(n+1));

	for (int i = 0; i < nB; i++)
		for (int j = i+1; j < nB; j++)
			transB_offdiag(n,a+i*B+j*B*n,a+j*B+i*B*n);
			//transB_offdiag(n,a+(i+j*n)*B,a+(j+i*n)*B);
}

// m=margin,  a=bottom panel,  b=right panel
static void transB_side(const int m, const int lda, double *restrict a, double *restrict b)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < B; j++)
			swp(a+i+j*lda,b+j+i*lda);
}

// m=margin
static void transB_conner(const int m, const int lda, double *restrict a)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < i; j++)
			swp(a+i+j*lda,a+j+i*lda);
}

// matrix dimension does not have to divide the block size B
void trans_block(const int n, double *restrict a)
{
	const int nB=n/B; // num of blocks
	const int m=n-nB*B; // margin

	for (int i = 0; i < nB; i++)
		transB_diag(n,a+i*B+i*B*n);

	for (int i = 0; i < nB; i++)
		for (int j = i+1; j < nB; j++)
			transB_offdiag(n,a+i*B+j*B*n,a+j*B+i*B*n);

	for (int i = 0; i < nB; i++)
		transB_side(m,n,a+nB*B+i*B*n,a+i*B+nB*B*n);

	transB_conner(m,n,a+nB*B+nB*B*n);
}

void omp_trans_block(const int n, double *restrict a, const int num_threads)
{
	fprintf(stderr,"omp_trans_block not implemented yet... good luck\n");
}
