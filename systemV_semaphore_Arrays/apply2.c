// 使用PV操作解决哲学家就餐问题(多信号量)
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/sem.h>
#include<sys/wait.h>
union semun {
      int              val;    /* Value for SETVAL */
	  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
      unsigned short  *array;  /* Array for GETALL, SETALL */
	  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};

void ERR_EXIT(char *  message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

// P操作
int sem_p(int semid)
{
	struct sembuf sb = {0, -1, 0};  //第一个0表示第1个信号量, -1表示P操作, 第二个0表示默认选项
	int ret = semop(semid, &sb, 1);  //表示对semid对应的信号量集, 执行&sb操作, 只对一个信号量操作
	if(ret == -1)
		ERR_EXIT("semop");
	return ret;
}

// V操作
int sem_v(int semid)
{
	   struct sembuf sb = {0, 1, 0};  //第一个0表示从第1个信号量开始, 1表示V操作, 第二个0表示默认选项
	   int ret = semop(semid, &sb, 1);  //表示对semid对应的信号量集, 执行&sb操作, 只对一个信号量操作
	   if(ret == -1)
		   ERR_EXIT("semop");
	   return ret;
}

int semid;
#define DELAY (rand()%5+1)

//获取刀叉, 刀叉同时P操作
void wait_for_2fork(int no)
{
	int left = no;
	int right = (no+1)%5;
	struct sembuf buf[2] = {
		{left, -1, 0},
		{right, -1, 0}
	};
	semop(semid, buf, 2);  //对两个信号量进行操作
}

//释放刀叉, 刀叉同时V操作
void free_2fork(int no)
{
	int left = no;
    int right = (no+1)%5;
    struct sembuf buf[2] = {
        {left, 1, 0}, 
		{right, 1, 0}
    };  
    semop(semid, buf, 2);  //对两个信号量进行操作
}

void philosophere(int no)  //模拟哲学家的行为:思考, 拿叉子, 用餐, 放叉子
{
	for(;;)
	{
		printf("%d is thinking\n", no);
		sleep(DELAY);
		printf("%d is hungry\n", no);
		wait_for_2fork(no); 
		printf("%d is eating\n", no);
		sleep(DELAY);
		free_2fork(no);
	}
}
int main(int argc, char * argv[])
{
	semid = semget(IPC_PRIVATE, 5, IPC_CREAT | 0666); //IPC_PRIVATE表示key值为0,参数2表示有5个信号量(5把刀叉)
	if(semid == -1)
		ERR_EXIT("semget");

	union semun su;
	su.val = 1;
	int i;
	//5个信号量都设置为1
	for(i=0; i<5; i++)
		semctl(semid, i, SETVAL, su);
	int no = 0;
	pid_t pid;
	for(i=1; i<5; i++)
	{
		pid = fork();    // 4个子进程
		if(pid == -1)
			ERR_EXIT("fork");
		if(pid == 0)    // 子进程
		{
			no = i;  //设置编号
			break;
		}
	}	
	philosophere(no);  //哲学家进程
	return 0;
}
