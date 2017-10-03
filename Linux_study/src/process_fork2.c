/*************************************************************************
	> File Name: process_fork2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 20时58分02秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
//父子进程交替运行
int main(void)
{
    printf("current pid: %d", getpid());
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error");
    }else if(pid > 0){
        int i = 0;
        for(i = 0; i < 10; ++i)
        {
            printf("This is parent process pid is %d\n",getpid());
            sleep(1);
        }
    }else{
        for(int i =0; i < 10; ++i){
            printf("This is child process pid is %d\n", getpid());
            sleep(1);
        }
    }

    return 0;
}
