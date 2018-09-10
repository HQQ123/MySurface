// POSIX往共享内存写入对象
#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
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
} STU;

int main(int argc, char * argv[])
{
	int shmid;
	// 打开共享内存
	shmid = shm_open("/xyz", O_RDWR, 0);
	if(shmid == -1)
		ERR_EXIT("shm_open");
	printf("shm_open succ\n");
	
	struct stat buf;
	// 获取共享内存信息
	if(fstat(shmid, &buf) == -1)
		ERR_EXIT("fstate");
	printf("size=%ld mode=%o\n", buf.st_size, buf.st_mode & 07777);

	//实现共享内存与地址空间的映射
	STU * p;
	p = mmap(NULL, buf.st_size, PROT_WRITE, MAP_SHARED, shmid,  0);
	if(p == MAP_FAILED)
		ERR_EXIT("mmap");

	strcpy(p->name, "test");
	p->age = 20;
	
	close(shmid);
	return 0;
}
