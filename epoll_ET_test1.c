/*************************************************************************
	> File Name: epoll_ET_test1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月30日 22时18分41秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<fcntl.h>
//我的第一个epoll程序
//注释掉的代码和现在的效果一样 ，如果没有read()程序无限死循环，因为缓冲区的数据没有读出来
//只要缓冲区有数据，就会触发事件，这是LT模式，epoll的ET模式解决了这个问题 或者加read()。
//可以通过修改缓冲区大小进行测试，注意输入的字符后面有换行符'\n'
int main()
{
    int epfd, nfds;
    //char buf[256];
    struct epoll_event ev, events[5];
    //ev用于注册事件，数组用于返回要处理的事件。
    epfd = epoll_create(1);
    //只需要监听一个描述符--标准输入STDIN_FILENO
    ev.data.fd = STDIN_FILENO;
    ev.events = EPOLLIN|EPOLLET;//ET模式
    //ev.events = EPOLLIN;//LT模式

    //监听读状态，同时设置ET模式
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);
    //注册epoll事件
    while(1)
    {
        nfds = epoll_wait(epfd, events, 5, -1);
        for(int i = 0; i < nfds; ++i)
        {
            if(events[i].data.fd == STDIN_FILENO)
            {
                printf("my first epoll_ET_test1.c\n");
                //read(STDIN_FILENO, buf, sizeof(buf));
            }
        }
    }
    return 0;
}

