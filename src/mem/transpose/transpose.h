#ifndef _TRANSPOSE_H_
#define _TRANSPOSE_H_

void trans_easy(const int n, double *restrict a);

// matrix dimension must divide the block size B
void trans_block0(const int n, double *restrict a);

// matrix dimension does not have to divide the block size B
void trans_block(const int n, double *restrict a);

// openmp version of trans_block, TODO
void omp_trans_block(const int n, double *restrict a, const int num_threads);

#endif /* end of include guard */
