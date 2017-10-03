/*************************************************************************
	> File Name: process_mark.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 19时52分40秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
//进程标识
int main()
{
    printf("pid = %d\n",getpid());//当前进程id
    printf("ppid = %d\n",getppid());//父进程id
    printf("uid = %d\n",getuid());//实际用户id
    printf("euid = %d\n",geteuid());//有效用户id
    printf("user gid = %d\n", getgid());//用户的组id
    printf("gid = %d\n", getpgrp());//当前进程组id
    printf("pgid = %d\n",getpgid(getpid()));//当前进程所在进程族的id
    printf("ppgid = %d\n", getpgid(getppid()));//父进程所在的进程组id

    return 0;
}
