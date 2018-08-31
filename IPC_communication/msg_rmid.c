// 删除消息队列
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

int main(int argc, int * argv[])
{
	int msgid;
	msgid = msgget(1234, 0);  // 打开消息队列,第二个参数用0
	if(msgid == -1)
		ERR_EXIT("msgget");
	printf("消息队列创建成功, 请指示\n");
	printf("msgid=%d\n", msgid);
	
	// 删除消息队列
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}


