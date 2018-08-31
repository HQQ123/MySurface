// 设置消息队列内容
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
	printf("消息队列打开成功, 请指示\n");
	printf("msgid=%d\n", msgid);
	
	struct msqid_ds buf;
	// 获取消息队列状态,将结果保存进buff里,所有信息可以通过man msgctl获取
	msgctl(msgid, IPC_STAT, &buf);
	// 这里用sscanf,表示数据来源为字符串,即第一个参数; 用scanf表示从标准输入获取输入信息,不需要第一个参数
	sscanf("600", "%o",(unsigned int *) &buf.msg_perm.mode);
	msgctl(msgid, IPC_SET, &buf);  //对消息队列进行设置,mode更改为0600
	return 0;
}


