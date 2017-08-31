/*************************************************************************
	> File Name: cli_room.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月21日 03时07分58秒 PDT

************************************************************************/
#include"clientmsg.h"
void *func(void *arg);
void process_cli(int sockfd, struct CLIENTMSG clientMSG);

struct ARG{
    int sockfd;
    struct CLIENTMSG clientMSG;
};
int main()
{
    int sockfd;
    char ip[20];//存放ip地址
    int port;//端口变量
    pthread_t tid;
    struct sockaddr_in ser_address;
    struct CLIENTMSG clientmsgSEND;
    struct ARG *arg;
    //******socket***********//
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);
    //*******connect*********//
    printf("Please input a ip address:\n");//读入客户端信息：ip、port、用户名
    scanf("%s", ip);
    printf("Please input the port:\n");
    scanf("%d", &port);
    bzero(&ser_address, sizeof(ser_address));
    ser_address.sin_family = AF_INET;
    ser_address.sin_port = htons(port);
    inet_aton(ip, &ser_address.sin_addr);

    int con = connect(sockfd, (struct sockaddr*)&ser_address, sizeof(ser_address));
    assert(con != -1);
    
    recv(sockfd, &clientmsgSEND, sizeof(clientmsgSEND), 0);
    if(clientmsgSEND.OP == OK)
    {
        //创建一个线程
        arg = (struct ARG*)malloc(sizeof(struct ARG));
        arg->sockfd = sockfd;
        pthread_create(&tid, NULL, func, (void *)arg);
        //主线程
        printf("Please input your username:\n");
        scanf("%s", clientmsgSEND.username);
        clientmsgSEND.OP = USER;//进入房间
        send(sockfd, &clientmsgSEND, sizeof(clientmsgSEND), 0);
        while(1)
        {
            clientmsgSEND.OP = MSG;//标记为发送状态
            scanf("%s", clientmsgSEND.buf);
            if(strcmp("bye", clientmsgSEND.buf) == 0)
            {
                clientmsgSEND.OP = EXIT;//退出聊天室
                send(sockfd, &clientmsgSEND, sizeof(clientmsgSEND), 0);
                break;
            }
                send(sockfd, &clientmsgSEND, sizeof(clientmsgSEND), 0);    
        }
        pthread_cancel(tid);
    }
    else
    {
        printf("警告：达到用户上限！");
    }
    close(sockfd);
    return 0;
}

void *func(void *arg)
{
    struct ARG *info;
    info = (struct ARG*)arg;
    process_cli(info->sockfd, info->clientMSG);
    free(arg);
    pthread_exit(NULL);
}
void process_cli(int sockfd, struct CLIENTMSG clientMSG)
{
    int len;
    while(1)
    {
        bzero(&clientMSG,sizeof(clientMSG));
        len = recv(sockfd, &clientMSG, sizeof(clientMSG), 0);
        if(len > 0)
        {
            if(clientMSG.OP == USER)
            {
                printf("The user %s is login!", clientMSG.username);
            }
            else if(clientMSG.OP == EXIT)
            {
                printf("The user %s is logout!", clientMSG.username);
            }
            else
            {
                printf("%s:%s\n", clientMSG.username, clientMSG.buf);
            }
        }
    }
}

