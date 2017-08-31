/*************************************************************************
	> File Name: strcmp.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月20日 17时51分18秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<assert.h>
//比较字符串大小
int strcmp(const char *src, const char *dst);
int main()
{
    char *src = "abcdefgh";
    char *dst = "abcdefghb";

    int count = strcmp(src, dst);

    printf("%d\n", count);

    if(count < 0)
    {
        printf("第一个字符串大！\n");
    }
    else if(count == 0)
    {
        printf("两个字符串一样大！\n");
    }
    else
    {
        printf("第二个字符串大！\n");
    }

    return 0;
}

int strcmp(const char *src, const char *dst)
{
    assert(NULL != src && NULL != dst);

    while(*src && *dst && *src++ == *dst++);
    
    return *src - *dst;
}
