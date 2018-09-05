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
	//打开文件, O_CREAT表示文件不存在则创建, O_RDWR表示可读可写, O_TRUNC表示打开文件时清空文件内容
	fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if(fd == -1)
		ERR_EXIT("open");
	// lseek表示重新定义打开文件的偏移量, sizeof(STU)*5-1=39,表示偏移量为39, SEEK_SET表示从头开始定位.
	lseek(fd, sizeof(STU)*5-1, SEEK_SET);
	// 在文件尾写入一个字节
	write(fd, "", 1);

	// 将文件映射到共享内存区
	STU * ptr;
	ptr = (STU *) mmap(NULL, sizeof(STU)*5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == NULL)
		ERR_EXIT("mmap");

	// 通过指针向共享内存区写入数据
	char ch = 'a';
	int i;
	for(i=0; i<5; i++)
	{
		memcpy((ptr+i)->name, &ch, 1);
		(ptr+i)->age = 20+i;
		ch++;
	}
	printf("初始化结束\n");
	
	//取消mmap建立的映射
	munmap(ptr, sizeof(STU)*5);
	printf("退出\n");
	return 0;
}
