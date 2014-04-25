#include <stdio.h>
#include "utils/TimeStat.h"
#include "magic3.h"

int main(int argc, char const* argv[])
{
	const int base[3]={2,3,5};
	const int num=1500;

	TimeStat clock(num+1);
	struct magic3_t *m = magic3_create(base);
	for (int i = 0; i < num; i++) {
		clock.tic();
		int mag = magic3_next(m);
		double cyc = clock.toc();
		printf("[%6d] [%.0f cycles] %15d \n",i+1,cyc,mag);
	}
	magic3_destroy(m);

	printf("num=\t%d\n",num);
	printf("cycles/magic number:\n");
	printf("\tmedian\tmax\tmin\n");
	printf("\t%.0f\t%.0f\t%.0f\n",clock.median(),clock.max(),clock.min()); 

	return 0;
}
