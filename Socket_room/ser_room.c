/*************************************************************************
	> File Name: ser_room.c
	> Author: mZ	> Mail: 
	> Created Time: 2017年08月21日 20时29分18秒 PDT
 ************************************************************************/

#include "clientmsg.h"
void *func(void *arg);
 void communicate_process(int index);
struct Entity
{
    int sockfd;
    char username[20];
    char buf[CMSGLEN];
    struct sockaddr_in cli_address;
    int stat;
};

struct Entity ent[5];
int main()
{
    struct sockaddr_in ser_address;
    struct sockaddr_in cli_address;
    char ip[20];
    int port;
    struct CLIENTMSG clientMSG;
    pthread_t tid;
    int *arg;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock != -1);

    /*输入服务器ip地址和端口号*/
    printf("Please input the ip address:\n");
    scanf("%s",ip);
    printf("Please input the port:\n");
    scanf("%d", &port);

    bzero(&ser_address, sizeof(ser_address));
    ser_address.sin_port = htons(port);
    ser_address.sin_family = AF_INET;
    inet_aton(ip, &ser_address.sin_addr);

    int bindfd = bind(sock, (struct sockaddr*)&ser_address, sizeof(ser_address));
    assert(bindfd != -1);

    int len = listen(sock, 5);
    assert(len != -1);
    
    for(int i = 0; i < 5; ++i)
    {
        ent[i].stat = 0;//初始化用户状态
    }

    while(1)
    {
        int addrlen = sizeof(cli_address);
        int con = accept(sock, (struct sockaddr*)&cli_address, &addrlen);
        assert(con != -1);

        int index = 5;
        for(int i = 0; i 
            < 5; ++i)
        {
            if(ent[i].stat == 0)
            {
                index = i;
            }
        }

        if(index <= 4)
        {
            printf("connetfd: %d\n", con);
            ent[index].cli_address = cli_address;
            ent[index].sockfd = con;
            ent[index].stat = 1;
            arg = malloc(sizeof(int));
            *arg = index;
            pthread_create(&tid, NULL, func, (void*)arg);
        }
        else
        {
            bzero(&clientMSG,sizeof(clientMSG));
            clientMSG.OP = EXIT;
            send(con, &clientMSG, sizeof(clientMSG), 0);
            close(con);
        }
    }
    close(sock);
}
void *func(void *arg)
{
    int *info ;
    info = (int *)arg;
    communicate_process( *info);
    pthread_exit(NULL);
 }
 void communicate_process(int index)
 {
    struct CLIENTMSG sendMsg;
    struct CLIENTMSG recvMsg;
    printf("sockfd:%d\n",ent[index].sockfd );
    sendMsg.OP = OK;
    send(ent[index].sockfd,&sendMsg,sizeof(sendMsg),0);
 
    while(1){
         bzero(&sendMsg,sizeof(sendMsg));
         bzero(&recvMsg,sizeof(recvMsg));
         int len =recv(ent[index].sockfd,&recvMsg,sizeof(recvMsg),0);
        if(len > 0)
        {
            if(recvMsg.OP == USER)
            {
 printf("user %s login from ip:%s,port:%d\n",recvMsg.username,inet_ntoa(ent[index].cli_address.sin_addr),ntohs(ent[index].cli_address.sin_port) );
               bcopy(recvMsg.username,ent[index].username,strlen(recvMsg.username));  
                sendMsg.OP = USER;
             }
             else if(recvMsg.OP == EXIT)
            {
                printf("user %s is logout\n",recvMsg.username );
                sendMsg.OP = EXIT;
                ent[index].stat = 0;
                int i;
                for(i=0;i<5;i++)
                {
                    if(ent[i].stat == 1)
                    {
                         
                          send(ent[i].sockfd,&sendMsg,sizeof(sendMsg),0);
                    }
                }
                break;
            }
             else if(recvMsg.OP == MSG)
            {
                sendMsg.OP = MSG;
            }
            bcopy(recvMsg.username,sendMsg.username,strlen(recvMsg.username));
            bcopy(recvMsg.buf,sendMsg.buf,strlen(recvMsg.buf));
            int i;
            for(i=0;i<5;i++)
            {
                if(ent[i].stat == 1)
                {
                    printf("stat 1...\n");
                    send(ent[i].sockfd,&sendMsg,sizeof(sendMsg),0);
                }
            }
        }
         else
        {
             continue;
        }
    }
 }

