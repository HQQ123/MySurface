// 发送消息
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

#define ERR_EXIT(m) \
	do \
	{ \
			perror(m); \
			exit(EXIT_FAILURE); \
	}while(0)

struct msgbuf{
	long mtype;  //消息类型
	char mtext[1]; //消息长度
};

int main(int argc, char * argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <bytes> <type>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int len = atoi(argv[1]); //保存消息长度
	int type = atoi(argv[2]);  //保存消息类型

	int msgid;
	msgid = msgget(1234, 0);  // 打开消息队列,第二个参数用0
	if(msgid == -1)
		ERR_EXIT("msgget");
	
	struct msgbuf * ptr;
	ptr = (struct msgbuf *)malloc(sizeof(long)+len);
	ptr->mtype = type;
	// if(msgsnd(msgid, ptr, len, 0)<0)  //阻塞
	if(msgsnd(msgid, ptr, len, IPC_NOWAIT)<0)  //不阻塞,提示资源不可用
		ERR_EXIT("msgsnd");
	return 0;
}


