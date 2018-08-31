// 创建消息队列
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
	//创建一个消息队列, 指定key为1234,0666表示权限:第一个6表示拥有者拥有读和写的权限,第二个6表示主用户具有读和写的权限,第三个6表示其他用户也具有读和写的权限
	// 必须显式指定IPC的创建者为IPC_CREAT或IPC_EXCL,若同一个创建者多次调用msgget(key相同),则会打开消息队列,而不会创建它,若不同的创建者调用相同key的msgget,结果创建失败提示文件存在
	// 显式指定IPC_PRIVATE(实际上宏定义为0), 只要指定IPC_private,则总是可重复创建消息队列,这样创建的消息队列不能被其他进程中共享,此时不需指定消息队列创建者
	int msgid;
	msgid = msgget(1234, 0666 | IPC_CREAT);
	//msgid = msgget(1234, 0666 | IPC_CREAT | IPC_EXCL);
	//msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT | IPC_EXCL);
	//msgid = msgget(IPC_PRIVATE, 0666);
	//msgid = msgget(1234, 0);  // 打开消息队列,第二个参数用0
	if(msgid == -1)
		ERR_EXIT("msgget");
	printf("消息队列创建成功, 请指示\n");
	printf("msgid=%d\n", msgid);
	return 0;
}


