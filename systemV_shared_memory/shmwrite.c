// systemV共享内存写入函数
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
	shmid = shmget(1234, sizeof(STU), IPC_CREAT | 0666);
	if(shmid==-1)
		ERR_EXIT("shmget");
	
	// 连接共享内存
	STU * ptr;
	ptr = shmat(shmid, NULL, 0);  // 0表示可读可写, NULL表示系统自己找到合理位置

	if(ptr == (void *)-1)
		ERR_EXIT("shmat");

	// 访问共享内存
	strcpy(ptr->name, "list");
	ptr->age = 20;

	//sleep(10);
	// 进程脱离共享内存
	shmdt(ptr);

	// 删除共享内存
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
