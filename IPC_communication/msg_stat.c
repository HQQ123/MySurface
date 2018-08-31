// 获取消息队列状态
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
	printf("mode=%o\n",buf.msg_perm.mode);  //打印出消息队列的权限
	printf("bytes=%ld\n", buf.__msg_cbytes);
	printf("number=%d\n", (int)buf.msg_qnum);
	printf("msgmnb=%d\n", (int)buf.msg_qbytes);
	return 0;
}


