/*************************************************************************
	> File Name: io_select.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月24日 21时19分11秒 PDT
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
    
    char buf[IOMAXSIZE];
    char sendbuff[IOMAXSIZE];

    /*------------进程数组-------------------*/
    int sockcount[FD_SETSIZE];
    for(int i = 0; i < FD_SETSIZE; ++i)
    {
        sockcount[i] = -1;//等于-1是因为进程描述符是从0开始的，负数表示没有该进程
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
                if(sockcount[i] < 0)
                {
                    sockcount[i] = connectfd; //将刚刚监听进来的客户端进程唤醒
                    break; 
                }
            }
            if(i == FD_SETSIZE)
            {
                fprintf(stderr ,"达到连接上限，与服务器连接失败！");
                exit(EXIT_FAILURE);
            }
            printf("IP = %s PORT = %d connect successful！\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
            count ++;
            printf("当前连接人数： %d\n", count);
            FD_SET(connectfd, &recset);
            if(connectfd > maxfd)
            {
                maxfd = connectfd;//因为connectfd为新生成的文件描述符，maxfd要始终保持最大范围
            }
            /*if(--nready <= 0)//????
            {
                continue;
            }*/
        }
        for( i = 0; i < FD_SETSIZE; ++i)
        {
            //printf("dhskas");
            connectfd = sockcount[i];//将新进来的连接唤醒
            if(sockcount[i]== -1)
            {
                continue;
            }
            if(FD_ISSET(connectfd, &lisset))
            {
                int recvbytes = recv(connectfd, buf, sizeof(buf), 0);
                if(recvbytes == -1)
                {
                    perror("recv");
                }
                if(recvbytes == 0)
                {
                    printf("client close!\n");
                    FD_CLR(connectfd, &recset);
                    sockcount[i] = -1;
                    count --;
                    printf("当前连接人数：%d\n", count);
                }

                for( i = 0; i < FD_SETSIZE; ++i)
                {
                    if(sockcount[i] > 0 && sockcount[i] != connectfd)
                    {
                        send(sockcount[i], buf, recvbytes-1, 0);
                    }
                }
                printf("recv the data[%d]: %s", recvbytes, buf);
                if(-nready <= 0)
                {
                    break;
                
                }

            }
        }
    }
    return 0;
}

   /* while(1)//服务器与客户端通信，互相发送消息就像两个客户通信一样
    {
        while(1)  
        {  
            int len = recv(connectfd,buf,BUFSIZ,0);  
            buf[len]='\0';  
            if(len > 0)
            {
               printf("received@: %s\n",buf);  
            }
            if(!strcmp(buf,"bye"))
            {
                break;
            }
           // gets(buf);

            //len = send(connectfd,buf,sizeof(buf), 0);

            if(len == 0)
            {
                exit(0);
            }
        }
        while(1)
        {
            printf("send@:");
            gets(buf);
            int len = send(connectfd,buf,sizeof(buf), 0);
            if(!strcmp(buf, "bye"))
            {
                break;
            }
        }
    }*/

    //客户端和服务器通信。服务器把客户端信息原样返回
    /*while(1)
    {
        memset(buf, 0, sizeof(buf));
        int len = recv(connectfd, buf, sizeof(buf), 0);
        if(strcmp(buf, "bye\n") == 0)
        break;

        fputs(buf, stdout);
        send(connectfd, buf, sizeof(buf), 0);
        
    }*/
    //用select处理多客户端与服务器通信上限1024
