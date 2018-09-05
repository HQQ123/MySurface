// systemV共享内存: 读共享内存的函数
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

void ERR_EXIT(char *  message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

typedef struct stu
{
	char name[32];
	int age;
}STU;

int main(int argc, char * argv[])
{
	// 创建共享内存
	int shmid;
	shmid = shmget(1234, 0, 0);
	if(shmid==-1)
		ERR_EXIT("shmget");
	
	// 连接共享内存
	STU * ptr;
	ptr = shmat(shmid, NULL, 0);  // 0表示可读可写, NULL表示系统自己找到合理位置

	if(ptr == (void *)-1)
		ERR_EXIT("shmat");

	// 访问共享内存(读)
	printf("name = %s,age = %d\n", ptr->name, ptr->age);

	sleep(10);
	// 进程脱离共享内存
	shmdt(ptr);

	return 0;
}
