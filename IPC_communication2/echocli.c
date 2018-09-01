// 回射客户端
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


void echo_cli(int msgid)
{
	struct msgbuf msg;
	memset(&msg, 0, sizeof(msg));
	int n;
	int pid;
	pid = getpid();
	msg.mtype = 1;
	*((int *)msg.mtext) = pid;
	while(fgets(msg.mtext+4, MSGMAX, stdin)!=NULL)
	{
		if(msgsnd(msgid, &msg, 4+strlen(msg.mtext+4), 0)<0)  //不阻塞,提示资源不可用
			ERR_EXIT("msgsnd");

		memset(msg.mtext+4, 0, MSGMAX);
		
		if((n=msgrcv(msgid, &msg, MSGMAX, pid, 0))<0)
			ERR_EXIT("msgsnd");

		fputs(msg.mtext+4, stdout);
		memset(msg.mtext+4, 0, MSGMAX-4);
	}
}
int main(int argc, char * argv[])
{
	int msgid;
	msgid = msgget(1234, 0);  // 打开消息队列,第二个参数用0
	if(msgid == -1)
		ERR_EXIT("msgget");
	echo_cli(msgid);
	return 0;
}


