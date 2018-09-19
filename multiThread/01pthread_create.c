#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<pthread.h>

void ERR_EXIT(char * s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void * thread_routine(void * arg)
{
	for(int i=0; i<20; i++)
    {   
        printf("B");
        fflush(stdout);
		usleep(1);
		/*if(i==10)
			pthread_exit("ABC");*/
    }
	return "waL";
}

int main()
{
	pthread_t tid;
	int ret;
	// 第一个参数为线程id,第二个参数为线程属性(NULL表示默认属性), 第三个参数为线程启动执行的函数,第四个参数为传给启动函数的参数
	if((ret = pthread_create(&tid, NULL, thread_routine, NULL))!=0)
	{
		fprintf(stderr, "pthread_create:%s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<20; i++)
	{
		printf("A");
		fflush(stdout);
		usleep(1);
	}
	
	//sleep(1);  //方法1:等待1秒,使得新线程结束
	//方法2, 等待新线程执行完, 这之前主线程执行到这条语句堵塞,不返回
	void * value;
	if((ret=pthread_join(tid, &value))!=0)
	{
		fprintf(stderr, "pthread_join:%s\n", strerror(ret));
        exit(EXIT_FAILURE);
	}
	printf("\n");
	printf("return msg=%s\n", (char *)value);

	return 0;
}
