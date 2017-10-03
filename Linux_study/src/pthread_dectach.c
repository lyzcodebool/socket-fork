/*************************************************************************
> File Name: pthread_dectach.c
> Author: 
> Mail: 
> Created Time: 2017年10月02日 22时03分09秒 PDT
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void status_out(pthread_attr_t *attr)
{
    int stat = 0;
    if(pthread_attr_getdetachstate(attr, &stat) != 0)
    {
        perror("getdetachstate error");
        exit(1);
    }
    else
    {
        if(stat == PTHREAD_CREATE_JOINABLE)
        {
            printf("joinable stat\n");
        }
        else if(stat == PTHREAD_CREATE_DETACHED)
        {
            printf("detach stat\n");
        }
        else
        {
            printf("error status_out\n");
        }
    }
}
void*  thfd(void *arg)
{
    int i;
    int sum = 0;
    for(i = 1; i <= 100; ++i)
    {
        sum += i;
    }
    return (void *)sum;
}

int main()
{
    int err; 
    pthread_t default_th, detach_th;
    pthread_attr_t attr;//设置线程属性

    //对线程属性初始化
    pthread_attr_init(&attr);
    //输出分离属性
    status_out(&attr);

    //以分离属性的默认值正常启动子线程
    if((err = pthread_create(&default_th, &attr, thfd, (void*)0)) != 0)
    {
        perror("pthread create error");
        exit(1);
    }
    int res;
    //默认分离属性值启动的线程不会自动回收现成的资源，所以需要调用join回收
    if(pthread_join(default_th, (void *)&res) != 0)
    {
        perror("join error");
        exit(1);
    }
    else
    {
        printf("default_th return %d\n", (int)res);
    }
    printf("*************************************\n");

    //设置分离属性为分离状态启动
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    status_out(&attr);

    if((err = pthread_create(&detach_th, &attr, thfd, (void *)0)) != 0)
    {
        perror("pthread_create error!");
        exit(1);
    }
    //这里再调用join运行成功但是会报错
    /*if((pthread_join(detach_th, (void *)&res)) != 0)
    {
        perror("join error");
        exit(1);
    }
    else
    {
        printf("detach_th return %d\n", (int)res);
}*/
    printf("*************************************\n");

    //销毁线程属性
    pthread_attr_destroy(&attr);
    printf("0x%lx finished!\n", pthread_self());

    sleep(1);
}
