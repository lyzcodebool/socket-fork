/*************************************************************************
	> File Name: signal_sigchld.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月02日 03时57分18秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
void sig_handler(int signo)
{

    printf("child process  %d stop\n", signo);
    wait(0);
}
void out(int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%d out %d\n", getpid(), i);
        sleep(1);
    }
}
int main(void)
{
    if(signal(SIGCHLD, sig_handler) == SIG_ERR)
    {
        perror("sigchld error");
        exit(1);
    }
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid > 0)
    {
        out(100);
    }
    else
    {
        out(20);
    }
    return 0;
}
