// 回射服务器
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

#include<string.h>
#define ERR_EXIT(m) \
	do \
	{ \
			perror(m); \
			exit(EXIT_FAILURE); \
	}while(0)

#define MSGMAX 8192
struct msgbuf{
	long mtype;  //消息类型
	char mtext[MSGMAX]; //消息长度
};

void echo_srv(int msgid)
{
	int n;
	struct msgbuf msg;
	memset(&msg, 0, sizeof(msg));
	while(1)
	{
		if((n = msgrcv(msgid, &msg, MSGMAX, 1, 0))<0)
			ERR_EXIT("msgsnd");
		int pid;
		pid = *((int *)msg.mtext);  //前四个字节作为进程号
		fputs(msg.mtext+4, stdout);
		msg.mtype = pid;
		msgsnd(msgid, &msg, n,  0);
	}
}

int main(int argc, char * argv[])
{
	int msgid;
	msgid = msgget(1234, IPC_CREAT | 0666);  //创建消息队列  
	if(msgid == -1)
		ERR_EXIT("msgget");
	echo_srv(msgid);
	return 0;
}


