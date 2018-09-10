// POSIX删除共享内存对象
#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
void ERR_EXIT(char *  message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

typedef struct stu
{
	char name[32];
	int age;
} STU;

int main(int argc, char * argv[])
{
	shm_unlink("/xyz");
	return 0;
}
