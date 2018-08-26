#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
int main()
{
	int i;
	if(fork()==0)
	{
		for(i=0; i<100; i++)
			printf("This is child process\n");
	}
	else
	{
		for(i=0; i<100; i++)
			printf("This is Father  process\n");
	}
}
