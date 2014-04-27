#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024


int main(int argc, char const* argv[])
{
	const char fname[200]="howareyou.txt";
	int fd=open(fname,O_WRONLY|O_CREAT,0755);
	printf("fd=%d\n",fd);

	char buf[BUF_SIZE] = "-How are you?\n-I'm fine. Thank you. And you?\n";
	int status=write(fd,buf,BUF_SIZE);
	printf("wrote %d bytes\n",status);

	close(fd);
	return 0;
}
