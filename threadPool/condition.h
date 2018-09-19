#include<pthread.h>
typedef struct condition
{
	pthread_mutex_t pmutex;                 //和条件变量搭配使用的锁
	pthread_cond_t pcond;                   //条件变量本身
} condition_t;

int condition_init(condition_t * cond);     //条件变量初始化
int condition_lock(condition_t * cond);     //条件变量加锁
int condition_unlock(condition_t * cond);    //条件变量解锁
int condition_wait(condition_t * cond);     //等待条件满足
int condition_timewait(condition_t * cond, const struct timespec * abstime);  //等待固定时间
int condition_signal(condition_t * cond);  //向等待进程发送通知
int condition_broadcast(condition_t * cond);  //向所有线程广播
int condition_destroy(condition_t * cond);  //销毁条件变量
