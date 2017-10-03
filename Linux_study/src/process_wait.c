/*************************************************************************
	> File Name: process_wait.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月28日 16时11分16秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

void out_status(int status)
{
    //状态返回状态码
    if(WIFEXITED(status)){//正常终止
        printf("normal exit: %d\n", WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){//非正常终止
        printf("abnormal term: %d\n", WTERMSIG(status));
    }else if(WIFSTOPPED(status)){//在终止前是否暂停,只能接受特定的暂停信号
        printf("stopped sig: %d\n", WSTOPSIG(status));
    }else{
        printf("unknow sig\n");
    }
}
int main(void)
{
    int status;
    pid_t pid;
    //正常终止
    if((pid = fork()) < 0){
        fprintf(stderr, "fork error");
        exit(1);
    }else if(pid ==0){
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        exit(3);//子进程终止运行
    }
    //父进程调用wait()阻塞，等待子进程结束并收回
        wait(&status);
        out_status(status);
        printf("--------------------\n");

    //非正常终止
    if((pid = fork())< 0){
        perror("fork error");
    }else if(pid ==0){
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        int i = 3, j = 0;
        int k = i/j;
        printf("k = %d\n", k);
    }
    wait(&status);
    out_status(status);
    printf("--------------------\n");

    //暂停状态信号
    if((pid = fork())< 0){
        perror("fork error");
    }else if(pid ==0){
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        pause();//暂停，等待信号唤醒,实际运行kill该进程显示非正常终止，下同。
        /*int i = 0;
        while(++i>0)
        {
            sleep(3);
        }*/
    }
        pid = waitpid(pid, &status,WUNTRACED);//阻塞状态且监听暂停信号
    /*do{//因为我们设置的非阻塞状态，所以要用一个循环不断检测子进程是否运行完
       //也可以设置成阻塞的
        pid = waitpid(pid, &status, WNOHANG|WUNTRACED);
        if(pid == 0){
            sleep(1);
        }
    }while(pid == 0);*/

    //wait(&status);
    out_status(status);
    printf("--------------------\n");
}

