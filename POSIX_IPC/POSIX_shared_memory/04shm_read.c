// POSIX共享内存读取代码
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

	//实现共享内存与地址空间的映射(以读的方式)
	STU * p;
	p = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, shmid,  0);
	if(p == MAP_FAILED)
		ERR_EXIT("mmap");
	printf("name=%s, age=%d\n", p->name, p->age);
	close(shmid);
	return 0;
}
