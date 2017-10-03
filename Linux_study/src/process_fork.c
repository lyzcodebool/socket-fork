/*************************************************************************
	> File Name: process_fork.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月27日 20时27分58秒 PDT
 ************************************************************************/

#include<stdio.h>
//进程创建
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
//父子进程分别通过标准c和系统调用函数操作文件

int g_v = 30;//数据段

int main(void)
{
    int a_v = 30;//栈
    static int s_v = 30;//数据段

    printf("pid = %d\n", getpid());

    FILE *fp = fopen("s.txt", "w");//标准c的io函数是基于缓存的，这个缓存在堆中
    int fd = open("s_fd.txt",O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG);
//系统调用的io函数不带缓存。末尾文件权限宏有三种

    char *s = "hello iotek";
    ssize_t size = strlen(s)*sizeof(char);

    /*父进程调用*/
    //标准io函数(带缓存-->全缓存)
    fprintf(fp, "s:%s, pid:%d\n", s, getpid());//先写入缓存
    //kernel提供的io系统调用(不带缓存)
    write(fd, s, size);//直接写入文件
    pid_t pid;
    pid = fork();//创建子进程
    //在运行以后运行两个进程
    if(pid < 0){
        perror("fork error");
    }else if(pid == 0){
        //子进程返回0
        //子进程代码...
        printf("I am child process pid is %d\n,ppid is %d,fork return is %d\n",getpid(), getppid(), pid);
        g_v = 50; a_v= 50; s_v = 50;
        printf("g_v: %p, a_v: %p, s_v: %p\n", &g_v, &a_v, &s_v);
    }else{
        //父进程(在父进程中返回的子进程的pid)
        //父进程的代码...
        printf("I am parent process pid is %d\n,ppid is %d,fork return is %d\n",getpid(), getppid(), pid);
        g_v = 40; a_v= 40; s_v = 40;
        printf("g_v: %p, a_v: %p, s_v: %p\n", &g_v, &a_v, &s_v);
    }
    //printf("pid: %d, g_v: %d, a_v: %d, s_v; %d\n", getpid(), g_v, a_v, s_v);
    fprintf(fp, "pid: %d, g_v: %d, a_v: %d, s_v; %d\n", getpid(), g_v, a_v, s_v);

    sleep(1);
    fclose(fp);
    fclose(fd);

    exit(0);
}
