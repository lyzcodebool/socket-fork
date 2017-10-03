/*************************************************************************
	> File Name: fcnyl.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月22日 03时17分55秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define BUF_LEN 4096
void copy(int fd_in, int fd_out)
{
    char buffer[BUF_LEN];
    int len = 0;
    while((len = read(fd_in, buffer ,BUF_LEN)) != 0)
    {
        //printf("len = %d\n", len);
        if(len < 0)
        {
        fprintf(stderr, "error: read error");
        exit(1);
        }
        else
        {
            if(write(fd_out, buffer, len) != len)
            {
                fprintf(stderr, "error: write error");
                exit(1);
            }
        }
    }
}

/*void copy(int fd_in, int fd_out)
{
    char buffer[BUF_LEN];
    int size;
    while((size = read(fd_in, buffer, BUF_LEN)) != 0)
    {
        printf("size = %d\n", size);
        if(write(fd_out, buffer, size)!= size) 
        {
            perror("write error");
            exit(1);
        }
    }
        if(size < 0)
        {
            fprintf(stderr, "read error");
            exit(1);
        }
    close(fd_in);
    close(fd_out);
}*/
void set_fl(int fd, int flag)
{
    //获得原来的文件状态标志
    int val = fcntl(fd , F_GETFL);
    //增加新的文件状态标志
    val |= flag;//按位或
    //重新设置文件状态标志
    if(fcntl(fd, F_SETFL, val)<0)
    {
        perror("fcntl error");
    }
}

void clr_fl(int fd ,int flag)
{
    int val = fcntl(fd, F_GETFL);
    //清除指定的文件状态标志
    val &=~flag; //按位与(置0)
    if(fcntl(fd, F_SETFL, val)< 0)
    {
        perror("fcntl error2");
    }
}
int main(int argc, char *argv[])
{
    
    int fd_in;

    if(argc < 4)
    {
        fprintf(stderr, "usage: sourcefile and distfile\n");
        exit(1);
    }
    fd_in = open(argv[2], O_WRONLY);
    int fd_in2 = open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, 0777);
    //fd_in = open(argv[2],O_WRONLY |O_APPEND);//原子操作，多个线程一起对文件进行读写不会相互覆盖
    if(fd_in < 0)
    {
        perror("open failed ");
        exit(1);
    }
    int len = strlen(argv[1])*sizeof(char);

    write(fd_in, argv[1], len);

    copy(fd_in, STDOUT_FILENO);
    close(fd_in);
}

