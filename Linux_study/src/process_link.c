/*************************************************************************
	> File Name: process_link.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月26日 00时19分41秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "usage: %s file counter", argv[1]);
    }
    //接收输入，然后字符转换
    int counter = atoi(argv[1]);
    
    pid_t pid;
    for(int i = 0; i < counter; ++i)
    {
        pid = fork();
        if(pid < 0)
        {
            fprintf(stderr, "usage: fork error");
        }
        else if(pid > 0)
        {
            break;
        }
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
    }
    return 0;
}
