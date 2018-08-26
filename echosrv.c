// 回射服务器模型
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#define ERR_EXIT(m) \
	do  \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	}while(0)


int main(int argc, char *argv[])
{
	int listenfd;  //唯一标示套接字

	//判断是否创建成功
	if((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
	/*上面显式制定tcp, 也可用下面,参数0表示代码自动选择协议,因为流式对应的必为tcp
	   if((listenfd = socket(PF_INET, SOCK_STREAM, 0))<0)*/
		ERR_EXIT("socket");

	//创建服务器地址结构,并进行初始化
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;  // 地址族为ipv4
	servaddr.sin_port = htons(5188); // 端口号为5188,并转换为网络字节序
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // INADDR_ANY表示本机任意地址,作为该套接字ip地址,s_addr表示转化为32位整数(网络地址)
	/*也可以显式指定地址 
	servaddr.sin_addr.s_addr = htonl("127.0.0.1");
	也可以下面这种方式,将点分10进制转换为网络地址
	inet_aton("127.0.0.1", &servaddr.sin_addr);
	 */

	// 套接字绑定端口号和ip,失败返回-1, 成功0
	// bind函数参数:第一个表示作用以及返回的套接字, 第二个为要绑定的地址结构体, 第三个为地址长度
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
	{
		ERR_EXIT("bind");
	}

	//开启监听, SOMAXCONN表示最大连接数,这里可随便选定数字
	if(listen(listenfd, SOMAXCONN))
	{
		ERR_EXIT("listen");
	}

	// 建立连接过程,从已连接队列选择一个,返回
	// 对方地址
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int conn;  // 新的套接字, 主动套接字
	if((conn = accept(listenfd, (struct sockaddr *)&peeraddr, &peerlen))<0)
	{
		ERR_EXIT("accept");
	}

	char recvbuf[1024];
	while(1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		int ret = read(conn, recvbuf, sizeof(recvbuf));
		fputs(recvbuf, stdout);
		write(conn, recvbuf, ret);
	}
	close(conn);
	close(listenfd);

	return 0;
}
