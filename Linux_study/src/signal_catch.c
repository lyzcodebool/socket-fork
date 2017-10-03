/*************************************************************************
	> File Name: signal_catch.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月02日 01时36分51秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<pthread.h>

//定义信号处理函数
void sig_handler(int signo)
{
    printf("%d, %d occured\n", getpid(), signo);
}
int main(void)
{
    //向内核登记信号处理函数以及信号值
    if(signal(SIGTSTP, sig_handler) == SIG_ERR)
    {
        perror("SIGTSTP error\n");
    }
    if(signal(SIGINT, SIG_IGN) == SIG_ERR)
    {
        //忽略信号
        perror("SIGINT error\n");
    }
    int i = 0 ;
    while(i < 30)
    {
        printf("%d out %d\n", getpid(), i++);
        sleep(1);
    }
    return 0;
}
