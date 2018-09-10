// POSIX消息队列 接收程序
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

typedef struct stu
{
	char name[32];
	int age;
} STU;

void ERR_EXIT(char *  message)
{
	perror(message);
	exit(EXIT_FAILURE);
}


int main(int argc, char * argv[])
{
	// 打开消息队列
	mqd_t mqid = mq_open("/abc", O_RDONLY);
	if(mqid == (mqd_t)-1)
		ERR_EXIT("mq_open");
	
	// 获取每条消息的最大长度
	struct mq_attr attr;
	mq_getattr(mqid, &attr);
	size_t size = attr.mq_msgsize;
	STU stu;

	unsigned prio;
	if(mq_receive(mqid, (char *)&stu, size, &prio) == (mqd_t)-1)
		ERR_EXIT("mq_receive");

	printf("name=%s, age=%d, prio=%u\n", stu.name, stu.age, prio);

	// 关闭消息队列
	mq_close(mqid);
	return 0;
}
