/*************************************************************************
	> File Name: ser_fork.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月16日 18时58分09秒 PDT
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include<string.h>
#include<unistd.h>
int main(int argc, char *argv[])  
{  
    int server_sockfd;//服务器端套接字  
    int client_sockfd;//客户端套接字  
    int len;  
    struct sockaddr_in my_addr;   //服务器网络地址结构体  
    struct sockaddr_in remote_addr; //客户端网络地址结构体  
    int sin_size;  
    char buf[BUFSIZ];  //数据传送的缓冲区  
    memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零  
    my_addr.sin_family=AF_INET; //设置为IP通信  
    my_addr.sin_addr.s_addr=INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上  
    my_addr.sin_port=htons(8001); //服务器端口号  
      
    /*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/  
    if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)  
    {    
        perror("socket");  
        return 1;  
    }  
   
        /*将套接字绑定到服务器的网络地址上*/  
    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)  
    {  
        perror("bind");  
        return 1;  
    }  
      
    /*监听连接请求--监听队列长度为5*/  
    listen(server_sockfd,5);  
      
    sin_size=sizeof(struct sockaddr_in);  

    pid_t pid, ppid;
    while(1)
    {
        if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0)  
        {  
        perror("accept");  
        return 1;  
        }
        else
        {
            send(client_sockfd,"You have connect server!", strlen("You have connect server!"), 0);
        }
        
        //输出连接的客户端信息
        printf("\n%s: %d Login server!\n\n",inet_ntoa(remote_addr.sin_addr),ntohs(remote_addr.sin_port));
        pid = fork();
        int recvbytes;
        if(pid == -1)
        {
            printf("fork failed!");
        }
        else if(pid == 0)
        {
            while(1)
            {
                bzero(buf, 100);
                if((recvbytes = recv(client_sockfd, buf, 100,0)) == -1)
                {
                    perror("read client_sockfd failed!");
                }
                else if(recvbytes != 0)
                {
                    buf[recvbytes] = '\0';
                    usleep(1000);
       printf("%s: %d said: %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), buf);
                    //将客户端发送过来的消息发送回去。
                    if(send(client_sockfd, buf, sizeof(buf), 0) == -1)
                    {
                        perror("send error!");
                        break;
                    }
                }

            }
        }
        else if(pid > 0){}
    }
      
    /*等待客户端连接请求到达*/  
   /* printf("accept client %s\n",inet_ntoa(remote_addr.sin_addr));  
    len=send(client_sockfd,"Welcome to my server\n",21,0);*/
    //发送欢迎信息  /*接收客户端的数据并将其发送给客户端--recv返回接收到的字节数，send返回发送的字节数*/

    close(client_sockfd);  
    close(server_sockfd);  
    return 0;  
}
