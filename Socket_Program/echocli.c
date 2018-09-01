// 回射客户端模型
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#define ERR_EXIT(m) \
	do \
    { \
		perror(m); \
		exit(EXIT_FAILURE); \
	}while(0)


int main(int argc, char *argv[])
{
	int sock;  //客户端套接字

	//判断是否创建成功
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		ERR_EXIT("socket");

	//创建服务器地址结构,并进行初始化
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;  // 地址族为ipv4
	servaddr.sin_port = htons(5188); // 端口号为5188,并转换为网络字节序
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 指定服务器端地址

	// 客户端无需绑定与监听, 直接执行connect函数
	if(connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
		ERR_EXIT("connect");
	

	//发送缓冲区与接收缓冲区
	char sendbuf[1024] = {0}; 
	char recvbuf[1024] = {0};
	//从标准输入接收一行数据, 若不空, 将其发送给服务器
	while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
	{
		write(sock, sendbuf, strlen(sendbuf));    // 将标准输入写入缓冲区
		read(sock, recvbuf, sizeof(recvbuf));     // 读取
		fputs(recvbuf, stdout);                   // 回射
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}

	// 关闭套接字
	close(sock);

	return 0;
}
