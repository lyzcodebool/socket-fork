/*************************************************************************
	> File Name: process_appand.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月28日 14时56分30秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(stderr, "usag: %s file\n", argv[0]);
        exit(1);
    }
    int fd = open(argv[1], O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG);
    if(fd < 2){
        perror("open error");
        exit(1);
    }

    pid_t pid = fork();
    if(pid < 0){
        perror("fork error");
        exit(1);
    }else if(pid > 0){
        //parent process
        //父进程把文件偏移量跳到文件尾步
        if(lseek(fd, 0L, SEEK_END)< 0){
            perror("lseek error");
            exit(1);
        }
    }else{
        //child process
        //子进程从文件末尾写入
        char *str = "hello iotek\n";
        ssize_t size = strlen(str)*sizeof(char);
        sleep(3);
        if(write(fd , str, size)!= size){
            perror("write error");
            exit(1);
        }
    }
    printf("pid: %d finish!\n", getpid());
    sleep(1);

    //父子进程关闭fd
    close(fd);
    return 0;
}
