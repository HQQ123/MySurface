// 接收消息
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#define MSGMAX 8194
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
	int flag = 0;
	int type = 0;
	int opt;
	while(1)
	{
		opt = getopt(argc, argv, "nt:");
		if(opt == '?') //解析到不认识的参数
			exit(EXIT_FAILURE);
		if(opt == -1)
			break;
		switch(opt)
		{
			case 'n':
				/*printf("AAAA\n");*/
				flag |= IPC_NOWAIT;    //或等,如果指定-n选项,则flag=IPC_NOWAIT
				break;
			case 't':
				/*
				printf("BBBB\n");
				int n = atoi(optarg);
				printf("n=%d\n", n);*/
				type = atoi(optarg);
				break;
		}
	}

	int msgid;
	msgid = msgget(1234, 0);  // 打开消息队列,第二个参数用0
	if(msgid == -1)
		ERR_EXIT("msgget");

	struct msgbuf * ptr;
	ptr = (struct msgbuf *)malloc(sizeof(long)+MSGMAX);
	ptr->mtype = type;
	int n = 0;
	// if(msgsnd(msgid, ptr, len, 0)<0)  //阻塞
	if((n = msgrcv(msgid, ptr, MSGMAX, type, flag))<0)  //不阻塞,提示资源不可用
		ERR_EXIT("msgsnd");

	printf("read %d bytes type=%ld\n", n, ptr->mtype);
	return 0;
}


