/*************************************************************************
	> File Name: forktest1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月15日 23时22分06秒 PDT
 ************************************************************************/

#include<stdio.h>
#include  <sys/types.h>
#include<unistd.h>
//自测代码

void  ChildProcess(int count);                /* child process prototype  */
void ParentProcess(int count);

int main()
{
    int memory = 20;
    pid_t pid;
    pid =fork();
    if(0 == pid)
    {
        //得到子进程的pid 和 他的父进程 pid 下同。
        printf("I am child! My pid is %d, My father pid is %d!\n", getpid(), getppid());
        ChildProcess(memory);
    }
    else if(pid < 0) //进程创建失败！
    {
        printf("error：创建失败！");
    }
    
    else
    {
        printf("I am Parent! My pid is %d, My father pid is %d!\n",getpid(), getppid());
        ParentProcess(memory);
    }
    
}

void ChildProcess(int count)
{
    for(int i = 1; i < 21; ++i)
    {
        printf("ChildProcess第%d次: %d .\n",i, count+i);
    }
}

void ParentProcess(int count)
{
    for(int i = 1; i < 21; ++i)
    {
        printf("ParentProcess第%d次: %d .\n", i, count);
        sleep(0.1);
    }
}

