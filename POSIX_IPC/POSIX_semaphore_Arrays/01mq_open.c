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

void ERR_EXIT(char *  message)
{
	perror(message);
	exit(EXIT_FAILURE);
}


int main(int argc, char * argv[])
{
	// 创建消息队列
	mqd_t mqid = mq_open("/abc", O_CREAT | O_RDWR, 0666, NULL);
	if(mqid == (mqd_t)-1)
		ERR_EXIT("mq_open");
	printf("mq_open successful!\n");
	struct mq_attr attr;
	mq_getattr(mqid, &attr);  //mq_getattr获取消息队列的个数, 并存储到结构体attr中
	printf("max_#msg=%ld max_#bytes/msg=%ld #currently on queue=%ld\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

	// 关闭消息队列
	mq_close(mqid);
	return 0;
}
