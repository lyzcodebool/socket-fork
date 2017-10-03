/*************************************************************************
	> File Name: hole_file.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月20日 11时11分37秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

char *buf = "12345555533212l";
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "error: %s [file]", argv[0]);
        exit(1);
    }
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0777);
    if(fd < 0)
    {
        fprintf(stderr, "-usage %s open failed", argv[1]);
        exit(1);
    }
    size_t size = strlen(buf)*sizeof(char);
    //将字符写如空洞文件
    if(write(fd, buf, size)!= size)
    {
        fprintf(stderr, "-usage %s open failed!", argv[1]);
        exit(1);
    }
    //定位文件尾部10个字节处
    if(lseek(fd, 10L, SEEK_END)<0)
    {
        perror("lseek error");
        exit(1);
    }  
    //从文件尾部10个字节出写入
    if(write(fd, buf, size) != size)
    {
        perror("lseek error");
        exit(1);
    }
    close(fd);
   return 0; 
}
