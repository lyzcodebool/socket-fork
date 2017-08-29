/*************************************************************************
	> File Name: io_client2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月27日 23时10分05秒 PDT
 ************************************************************************/

#include "io_select.h"
#include "io.h"
int main(int argc, char *argv[])
{
    int connectfd;
    struct sockaddr_in seraddr;//服务器网络地址结构体
   
    struct Sock my;
    char sendbuff[1024] = {0};
    char recvbuff[1024] = {0};
    int port;
    char ip[20];
    char username[20];
    printf("Prease input the ip:\n");
    scanf("%s", ip);
    printf("Please input the port:\n");
    scanf("%d", &port);
    printf("Please input the username\n");
    scanf("%s", username); 
    
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(port);
    inet_aton(ip, &seraddr.sin_addr);

    connectfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(connectfd != -1);
    
    int conn = connect(connectfd, (struct sockaddr*)&seraddr, sizeof(struct sockaddr));
    if(conn == -1)
    {
        perror("connect!");
        return 1;
    }
    send(connectfd, username, sizeof(username), 0);
    fd_set rset;
    FD_ZERO(&rset);
    int nready = 0;
    int maxfd;
    int std = fileno(stdin);
    if(connectfd > std)
    {
        maxfd = connectfd;
    }
    else
    {
    maxfd = std;
    }
        FD_SET(connectfd, &rset);
        FD_SET(std, &rset);
    while(1)
    {
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if(nready == -1)
        {
            perror("select!");
        }
        if(nready == 0)
        {
            continue;
        }
        if(FD_ISSET(connectfd, &rset))
        {
            int recvbytes = recv(connectfd, recvbuff, sizeof(recvbuff), 0);
            if(recvbytes == -1)
            {
                perror("recv");
            }
            if(recvbytes == 0)
            {
                printf("server close!");
                exit(EXIT_FAILURE);
            }
            fputs(recvbuff ,stdout);
            memset(recvbuff, 0 , sizeof(recvbuff));
        }
        if(FD_ISSET(std, &rset))
        {
            if(fgets(sendbuff, sizeof(sendbuff), stdin) == NULL)
            {
                break;
            }
            send(connectfd, sendbuff, sizeof(sendbuff), 0);
            if(strcmp("bye", sendbuff) == 0)//结束连接
            {
                break;
            }
            memset(sendbuff, 0, sizeof(sendbuff));
        }
    }
        close(connectfd);
        return 0;
}

