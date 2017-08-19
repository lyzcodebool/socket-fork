/*************************************************************************
	> File Name: clienttest1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月18日 04时04分30秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
int main(int argc, char *argv[])
{
    if(argc <= 2)
    {
        printf("usage: %s ip_address port_number",argv[0]);
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in ser_address;
    struct sockaddr_in cli_address;

    bzero(&ser_address, sizeof(ser_address));
    ser_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &ser_address.sin_addr);
    ser_address.sin_port = htons(port);
    
    int sock = socket(AF_INET, SOCK_STREAM,0);
    assert(sock != -1);
    int ret = bind(sock,(struct sockaddr*)&ser_address,sizeof(ser_address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);
    int sin_size = sizeof(cli_address);
    int con = accept(sock, (struct sockaddr*)&cli_address,&sin_size);
    if(con < 0)
    {
        printf("error！");
        return 1;
    }
    else
    {
        
    }
    


