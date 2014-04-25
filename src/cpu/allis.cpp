#include <stdio.h>

int fun(int *n)
{
#pragma forceinline
	return n[0] + n[1] * n[2];
}

int funx(const int *n)
{
#pragma noinline
	return n[0] + n[1] * n[2];
}

int main(int argc, char const* argv[])
{
	int n[3]={1,3,5};
	const int nx[3]={1,3,5};
	printf("%d\n",fun(n));
	printf("%d\n",funx(nx));
	return 0;
}
