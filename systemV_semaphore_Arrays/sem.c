// systemV信号量集Demo
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

typedef struct stu
{
	char name[32];
	int age;
}STU;

//创建信号量集合
int sem_create(key_t key)
{
	int semid;
	semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);  // IPC_EXCL表示不允许创建同名信号量集, 1表示信号量集合中信号量的个数
	if(semid == -1)
		ERR_EXIT("semget");
	return semid;
}

// 打开信号量集合
int sem_open(key_t key)
{
	int semid;
	semid = semget(key, 0, 0);    //第一个0表示只是打开,第二个0表示不关心权限
	if(semid == -1)
		ERR_EXIT("semget");
	return semid;
}

// 对信号量集进行设置
int sem_setval(int semid, int val)
{
	union semun su;
	su.val = val;
	int ret = semctl(semid, 0, SETVAL, su);  //对第0个信号量进行设置
	if(ret == -1)
		ERR_EXIT("sem_setval");
	return 0;
}

// 获取信号量的值
int sem_getval(int semid)
{
    int ret = semctl(semid, 0, GETVAL, 0);  //获取第0个信号量的值, GetVAL第四个参数忽略,所以填0
    if(ret == -1) 
        ERR_EXIT("sem_getval");
    return ret;
}

// 只能删除整个信号量集,不能只删除特定信号量
int sem_delete(int semid)
{
	int ret = semctl(semid, 0, IPC_RMID, 0);  // 不知道信号量个数,第1个参数默认填0, IPC_RMID第四个参数忽略
	if(ret == -1)
		ERR_EXIT("sem_delete");
	return 0;
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

int main(int argc, char * argv[])
{
	int semid = sem_create(1234);  //创建信号量集
	sleep(5);
	sem_delete(semid);    // 删除信号量集



	return 0;
}
