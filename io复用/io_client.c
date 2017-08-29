/*************************************************************************
	> File Name: io_client.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月24日 22时21分44秒 PDT
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
    printf("Prease input the ip:\n");
    scanf("%s", my.ip);
    printf("Please input the port:\n");
    scanf("%d", &my.port);
    printf("Please input the username\n");
    scanf("%s", my.username); 
    
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(my.port);
    inet_aton(my.ip, &seraddr.sin_addr);

    connectfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(connectfd != -1);
    
    int conn = connect(connectfd, (struct sockaddr*)&seraddr, sizeof(struct sockaddr));
    if(conn == -1)
    {
        perror("connect!");
        return 1;
    }
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
    maxfd = std;
    while(1)
    {
        FD_SET(connectfd, &rset);
        FD_SET(std, &rset);
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
            memset(sendbuff, 0, sizeof(sendbuff));
        }
    }
        close(connectfd);
        return 0;
}
    /*while(1)//服务器和客户端循环通信，互相通信
    {
        while(1)
        {
            printf("Send@:");  
            gets(buff);
           int len=send(connectfd,buff,strlen(buff),0); 
           // bzero(buff, len);
            if(!strcmp(buff,"bye"))  
           // len = recv(connectfd, buff, BUFSIZ, 0);
            //buff[len] = '\0';
           // printf("%s\n", buff);
            break;  
        }

        while(1)
        {
            int len = recv(connectfd, buff, BUFSIZ, 0);
            buff[len] = '\0';
            if(len > 0)
            {
            printf("received@: %s\n", buff);
            }
            if(!strcmp(buff,"bye"))
            {
                break;
            }
            if(len == 0)
            {
                exit(0);
            }
        }
    }*/

    //服务器和客户端通信，服务器把客户端的消息原样返回

    /*while(fgets(sendbuff, sizeof(sendbuff), stdin) != NULL)
    {
        send(connectfd, sendbuff, sizeof(sendbuff), 0);
        if(strcmp(sendbuff, "bye\n") == 0)
        {
            break;
        }
        recv(connectfd, recvbuff, sizeof(recvbuff), 0);
        fputs(recvbuff, stdout);

        memset(sendbuff, 0, sizeof(sendbuff));
        memset(recvbuff, 0, sizeof(recvbuff));
    }*/
