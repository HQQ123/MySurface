// POSIX消息队列, unlink消息队列
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/sem.h>
#include<mqueue.h>


void ERR_EXIT(char *  message)
{
	perror(message);
	exit(EXIT_FAILURE);
}


int main(int argc, char * argv[])
{
	// 删除消息队列
	mq_unlink("/abc");
	return 0;
}
