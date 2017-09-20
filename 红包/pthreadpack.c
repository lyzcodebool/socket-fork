/*************************************************************************
	> File Name: pthreadpack.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月20日 04时23分59秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>

#define MAXNUM 10
#define _RAND(max, min) (rand()%((max)- (min)) + min)
static void* _grab(void *args);
static int count = 1;
typedef struct event//线程实例
{
    pthread_attr_t attr;//线程属性
    pthread_mutex_t mutex;//线程锁
    pthread_cond_t cond;//条件变量
}event_t;

typedef struct item
{
    int number; //红包数目
    int total; //红包总额
}item_t;
static item_t item = {0};

int main()
{
    int n = 0; //用来代表线程数
    int number;//红包数目
    int total;//红包总额

    event_t temp = {0};
    pthread_t tid;//线程变量

    /****实例初始化****/
    //assert(ret = pthread_mutex_init(&temp.mutex, NULL));//初始化锁
    //assert(ret = pthread_cond_init(&temp.cond, NULL));//初始化条件变量
    //assert(ret = pthread_attr_init(&temp.attr));//初始化线程属性
    pthread_mutex_init(&temp.mutex, NULL);//初始化锁
    pthread_cond_init(&temp.cond, NULL);//初始化条件变量
    pthread_attr_init(&temp.attr);//初始化线程属性
    
    /****创建线程*******/
    for(int i = 0; i < MAXNUM; ++i)
    {
        pthread_create(&tid, &temp.attr,_grab, &temp);
        count ++;
    }
    
    while(1)
    {
        sleep(0.01);
        printf("请输入红包个数：\n");
        if(fscanf(stdin,"%d", &number) == EOF)break;
        printf("请输入红包总金额：\n");
        if(fscanf(stdin,"%d", &total) == EOF)break;

        if(number > 10||number < 0)
        {
            fprintf(stderr,"error: Package out of rang: only allowed [0, 10]\n");
            exit(1);
        }
        
        pthread_mutex_lock(&temp.mutex);//上锁
        item.number = number;
        item.total = total*100;
        
        printf("初始的红包情况：<个数：%d  金额：%d.%02d>\n",item.number, item.total/100, item.total%100);
        pthread_cond_broadcast(&temp.cond);//红包包好后唤醒所有线程抢红包
        pthread_mutex_unlock(&temp.mutex);//解锁
        
        sleep(1);
    }

    //程序结束时销毁实例成员
    //assert(ret = pthread_attr_destroy(&temp.attr));
    //assert(ret = pthread_cond_destroy(&temp.cond));
    //assert(ret = pthread_mutex_destroy(&temp.mutex));
    pthread_attr_destroy(&temp.attr);
    pthread_cond_destroy(&temp.cond);
    pthread_mutex_destroy(&temp.mutex);

    return 1;
}
static void* _grab(void *args)
{
    int money = 0;
    event_t *ptid = (event_t *)args;
    if(!args)
    {
        return NULL;
    }
    printf("线程#%d : %lu\n", count, (unsigned long)pthread_self());//使用lu防止线程tid超过int范围
    while(1)
    {
        pthread_mutex_lock(&ptid->mutex);//子线程上锁
        pthread_cond_wait(&ptid->cond, &ptid->mutex);//线程挂起等待

        if(item.number <= 0)
        {
            printf("Thread #%lu,the package is empty!\n", (unsigned long)pthread_self());
            pthread_mutex_unlock(&ptid->mutex);
            printf("********************Thread #%lu Stop！\n", (unsigned long)pthread_self());
            continue;
        }
        else if(item.number == 1)//对于最后一个红包，把所有金额都算上
        {
            money = item.total;
        }
        else
        {
            money = item.total * _RAND(199, 1)/100/item.number;
        }
        item.total -= money;
        item.number--;

        printf("Thread  %lu get %d.%02d, left[%d, %d.%02d]\n", (unsigned long)pthread_self(), money/100, money%100, item.number,item.total/100, item.total%100);
        pthread_mutex_unlock(&ptid->mutex);
    }
        //printf("Thread #%lu Stop！\n", (unsigned long)pthread_self());
        return NULL;
}
