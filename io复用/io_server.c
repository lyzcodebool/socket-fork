/*************************************************************************
	> File Name: io_server.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月27日 22时59分29秒 PDT
 ************************************************************************/

#include "io_select.h"
#include "io.h"
#define IOMAXSIZE 1024
//#define MAXCOUNT 10
//io复用select 的使用
//服务器
int main(int argc, char *argv[])
{
    int listenfd;//监听套接字
    int connectfd;//连接以后的套接字，收发消息
    struct sockaddr_in seraddr;//服务器网络地址结构体
    struct sockaddr_in cliaddr;//客户端网络地址结构体

    int port;//端口变量
    char ip[20];//用于接收ip地址
   // char username[20];
    printf("Please input the ip:\n");
    scanf("%s", ip);
    printf("Please input the port:\n");
    scanf("%d", &port);
    /*printf("Please input your username:\n");
    scanf("%s", username);*/
    
    
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;//协议族
    seraddr.sin_port = ntohs(port);//端口，大端转成小端
    inet_pton(AF_INET, ip, &seraddr.sin_addr); //ip地址
    
    
    /*------------------创建套接字-------------*/
    listenfd = socket(AF_INET, SOCK_STREAM, 0);//创建套接字
    assert(listenfd != -1);
    
    /*-------------绑定ip和端口------------------*/
    int optval  = 1;
    if(setsockopt(listenfd, SOCK_STREAM, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {//网络地址复用
       perror("setsockopt");
    }
    int m = bind(listenfd, (struct sockaddr*)&seraddr, sizeof(seraddr));//绑定ip port;
    assert(m != -1);
    
    char buffer[IOMAXSIZE];
  //  char sendbuff[IOMAXSIZE];

    /*------------进程数组-------------------*/
    //int sockcount[FD_SETSIZE];
    for(int i = 0; i < FD_SETSIZE; ++i)
    {
        SERVER[i].OP = -1;//等于-1是因为进程描述符是从0开始的，负数表示没有该进程
    }


    /*------------------监听套接字-----------------*/
    int lis = listen(listenfd, 5);
    printf("listenfd = %d\n", listenfd);
    assert(lis != -1);
    socklen_t cliaddr_len;
     
    fd_set lisset, recset;//相当于声明了两个文件描述符集合
    FD_ZERO(&lisset);//清空lisset描述符集合
    FD_ZERO(&recset);
    int maxfd;//select参数一，当前的最大描述符,集合中所有描述符的范围
    maxfd = listenfd;
    int nready = 0;//select的返回值
    int i = 0;
    int temp;
    int count = 0;
    while(1)
    {
        lisset = recset;
        FD_SET(listenfd, &lisset);//将监听的文件描述符加入到监听集合中
        nready = select(maxfd+1, &lisset, NULL, NULL, NULL);
        if(nready < 0)
        {
            perror("select");
            return 1;
        }
        if(nready == 0)
        {
            continue;
        }
        if(FD_ISSET(listenfd, &lisset))
        {
            cliaddr_len = sizeof(cliaddr);
            connectfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
            printf("connectfd = %d\n", connectfd);
            if(connectfd == -1)
            {
                perror("accept!");
                return 1;
            }
            for(i = 0; i < FD_SETSIZE; ++i)
            {
                if(SERVER[i].OP < 0)
                {
                    recv(connectfd, SERVER[i].buf, sizeof(SERVER[i].buf), 0);//接收username
                    strcpy(SERVER[i].username, SERVER[i].buf);
                    printf("%s LOGIN successful!", SERVER[i].username);
                    SERVER[i].OP = connectfd; //将刚刚监听进来的客户端进程唤醒
                   // memset(SERVER[i].buf, 0, sizeof(SERVER[i].buf));
                    //接收当前用户的username
         //memset(SERVER[i].buf, 0, sizeof(SERVER[i].buf));//清空当前用户的缓冲区
        //SERVER[i].cliport = ntohs(cliaddr.sin_port);
                    break; 
                }
            }
            temp = i;
            if(i == FD_SETSIZE)
            {
                fprintf(stderr ,"达到连接上限，与服务器连接失败！");
                exit(EXIT_FAILURE);
            }
           // printf("IP = %s PORT = %d connect successful！\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
            count ++;
            printf("当前连接人数： %d\n", count);
            FD_SET(connectfd, &recset);
            if(connectfd > maxfd)
            {
                maxfd = connectfd;//因为connectfd为新生成的文件描述符，maxfd要始终保持最大范围
            }
        }
        for( i = 0; i < FD_SETSIZE; ++i)
        {
            //printf("dhskas");
            //connectfd = SERVER[i].OP;//将新进来的连接唤醒
            if(SERVER[i].OP== -1)
            {
                continue;
            }
            if(FD_ISSET(connectfd, &lisset))
            {
                int recvbytes = recv(SERVER[i].OP, buffer, sizeof(buffer), 0);
                if(recvbytes == -1)
                {
                    perror("recv");
                }
                if(strcmp("bye", buffer) == 0)
                {
                    printf("client [%s] close!\n",SERVER[i].username);
                    FD_CLR(SERVER[i].OP, &recset);
                    SERVER[i].OP = -1;
                    count --;
                    printf("当前连接人数：%d\n", count);
                   //这里需要告知用户(); 
                }

                for( i = 0; i < FD_SETSIZE; ++i)
                {
                    if(SERVER[i].OP > 0 && SERVER[i].OP != connectfd)

                    {
                        printf("1");
                        send(SERVER[i].OP, buffer, recvbytes-1, 0);
                    } 
                }
                printf("[%s]@: %s", SERVER[temp].buf, buffer);
                if(-nready <= 0)//剔除标准输入输出
                {
                    break;
                }
            }
        }
    }
    return 0;
}


