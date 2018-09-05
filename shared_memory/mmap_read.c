// 读取共享内存
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/mman.h>

#include<string.h>

void ERR_EXIT(char *  message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

typedef struct stu
{
	char name[4];
	int age;
}STU;

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd;
	//打开文件
	fd = open(argv[1],  O_RDWR );
	if(fd == -1)
		ERR_EXIT("open");

	// 将文件映射到共享内存区,返回一个指向起始地址的指针
	STU * ptr;
	ptr = (STU *) mmap(NULL, sizeof(STU)*5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == NULL)
		ERR_EXIT("mmap");

	// 读取共享内存
	int i;
	for(i=0; i<5; i++)
	{
		printf("name = %s, age = %d\n", (ptr+i)->name, (ptr+i)->age);
	}	
	//取消mmap建立的映射
	munmap(ptr, sizeof(STU)*5);
	printf("退出\n");
	return 0;
}
