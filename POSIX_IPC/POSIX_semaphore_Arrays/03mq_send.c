// POSIX消息队列
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
	if(argc!=2){
		fprintf(stderr, "Usage: %s <prio>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// 创建消息队列
	mqd_t mqid = mq_open("/abc", O_CREAT | O_RDWR, 0666, NULL);
	if(mqid == (mqd_t)-1)
		ERR_EXIT("mq_open");
	
	STU stu;
	strcpy(stu.name, "xiaoming");
	stu.age = 20;

	unsigned prio = atoi(argv[1]);
	mq_send(mqid, (const char *)&stu, sizeof(stu), prio);

	mq_close(mqid);
	return 0;
}
