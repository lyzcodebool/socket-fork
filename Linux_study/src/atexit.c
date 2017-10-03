/*************************************************************************
	> File Name: atexit.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月25日 19时43分29秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

void term_fun1()
{
    printf("first term function\n");
}
void term_fun2()
{
    printf("second term function\n");
}
void term_fun3()
{
    printf("third term function\n");
}
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "usage : %s file[exit|return|_exit]", argv[1]);
    }
    //向内核登记终止函数
    atexit(term_fun1);
    atexit(term_fun2);
    atexit(term_fun3);
    FILE *fp = fopen(argv[1], "w");
    fprintf(fp, "hello iotek");//标准c库函数 全缓存

    if(!strcmp(argv[2], "exit"))
    {
        exit(0);
    }
    else if(!strcmp(argv[2], "return"))
    {
        return 0;
    }
    else if(!strcmp(argv[2], "_exit"));
    {
        _exit(0);//系统调用
    }
}
