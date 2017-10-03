/*************************************************************************
	> File Name: cat.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月21日 19时05分53秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#define MAXLEN 4096
char buffer[MAXLEN];
/*
 * cat功能的代码实现
 */
void copy(int fd_in, int fd_out);
int main(int argc, char *argv[])
{
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;
    for(int i = 1; i < argc; ++i)
    {
        fd_in = open(argv[i], O_RDONLY);
        if(fd_in < 0)
        {
            perror("open error");
            continue;
        }
        copy(fd_in, fd_out);
        close(fd_in);
    }
    if(argc ==1)
    {
        copy(fd_in, fd_out);
    }
    return 0;
}
void copy(int fd_in, int fd_out)
{
    int len = 0;
    while((len = read(fd_in, buffer,MAXLEN)) != 0)
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
