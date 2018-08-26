#include<stdio.h>
#include<arpa/inet.h>

int main()
{
	unsigned long addr = inet_addr("192.168.0.100");
	printf ("addr=%u\n", ntohl(addr));  //将ip地址转化为32位无符号整数

	struct in_addr ipaddr;
	ipaddr.s_addr = addr;
	printf("%s\n", inet_ntoa(ipaddr));  //将无符号整数转换为ip地址

	return 0;
}
