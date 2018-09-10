// POSIX共享内存
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
	int shmid;
	// 创建共享内存
	shmid = shm_open("/xyz", O_CREAT | O_RDWR, 0666);
	if(shmid == -1)
		ERR_EXIT("shm_open");
	
	printf("shm_open succ\n");
	// 将共享内存大小修改为36字节
	if(ftruncate(shmid, sizeof(STU))==-1)
		ERR_EXIT("ftruncate");
	
	struct stat buf;
	// 获取共享内存信息
	if(fstat(shmid, &buf) == -1)
		ERR_EXIT("fstate");
	printf("size=%ld mode=%o\n", buf.st_size, buf.st_mode & 07777);
	close(shmid);
	return 0;
}
