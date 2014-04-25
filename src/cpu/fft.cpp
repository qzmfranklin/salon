#include <fftw3.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <mkl.h>
#include "utils/TimeStat.h"
#include "utils/Table.h"

// test the speed of fftw
class tfft {
	private:
		int status;
		int num;
		int fft_type;
		double *data;
		fftw_plan p;
	public:
		tfft() { status=0; }
		~tfft() { if (status==1) reset(); }

		// type = FFTW_FORWARD(-1) | FFTW_BACKWARD(+1)
		void set(const int n, const int type) {
			assert(status==0);
			num = n;
			fft_type=type;
			data = (double*)mkl_malloc(sizeof(fftw_complex)*n,64);
			assert(data);
			p = fftw_plan_dft_1d(n,
					(fftw_complex*)data,
					(fftw_complex*)data,
					type,
					FFTW_MEASURE|FFTW_PATIENT);
			status=1;
		}
		void reset() { 
			assert(status==1);
			fftw_destroy_plan(p); 
			mkl_free(data);
			status=0;
		}

		// n*lg_2(n)
		double nlogn() { return num*log(1.0*num)/log(2.0); }

		// return the median of time in CPU cycles
		double test(const int n) {
			TimeStat clk(n);
			for (int i = 0; i < n; i++) {
				if (fft_type==FFTW_FORWARD) {
					clk.tic();
					fftw_execute(p);
					clk.toc(); 
				} else {
					clk.tic();
					fftw_execute(p);
					bwd_scale();
					//bwd_scale_worse();
					clk.toc(); 
				}
			}
			//const double scale = num*log(1.0*num)/log(2.0);
			//return clk.median()/scale;
			return clk.median();
		}
	private: 
		void bwd_scale() {
			const double x=1.0/num;
			for (int i = 0; i < 2*num; i++)
				data[i] *= x;
		}
		void bwd_scale_worse() {
			for (int i = 0; i < 2*num; i++)
				data[i] /= num;
		}

};

int main(int argc, char const* argv[])
{ 
	const int m = 5;
	const int n = 2;
	const int size[m]={32,128,512,1023,2048};
	const char* rows[m] = {"32","128","512","1023","2048"};
	const char* cols[n] = {"total","normalized"};
	double data[m*n]; // row-major 

	tfft t;
	for(int i=0; i < m; i++) {
		//t.set(size[i],FFTW_BACKWARD);
		t.set(size[i],FFTW_FORWARD);
		data[n*i+0] = t.test(15);
		data[n*i+1] = data[n*i+0]/t.nlogn();
		t.reset();
	} 

	Table table;
	table.dim(m, n);
	table.rows(rows);
	table.cols(cols);
	table.data(data);

	char banner[200]="FFT using fftw, time in CPU cycles";
	strcat(banner,"\n\tnormalized to n*lg_2(n)");
	table.print(banner);

	printf("WARNING: switch to FFTW_BACKWARD and bwd_scale_worse() in lecture\n");

	return 0;
}
