/*************************************************************************
	> File Name: clientmsg.h
	> Author: 
	> Mail: 
	> Created Time: 2017年08月21日 03时01分10秒 PDT
 ************************************************************************/

#ifndef _CLIENTMSG_H
//防止重复引用。 跨平台。
#define _CLIENTMSG_H
#include<stdio.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<signal.h>
#define EXIT -1
#define USER 1
#define MSG 2
#define OK 3
#ifndef CMSGLEN
#define CMSGLEN 100

#endif
struct CLIENTMSG
{
    int OP;//用于标记状态
    char username[20];//存放用户名
    char buf[CMSGLEN];//接收用户输入的信息缓冲区
};
#endif
