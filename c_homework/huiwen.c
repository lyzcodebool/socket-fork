/*************************************************************************
	> File Name: huiwen.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月20日 18时03分25秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int fun(char *src);
#define MAX 100
//判断字符串是否回文
int main()
{
    char str[MAX];

    printf("请输入字符串:\n");
    scanf("%s", str);

    int a = fun(str);
    if(a == 1)
    {
        printf("是回文字符串！");
    }
    if(a == 0)
    {
        printf("不是回文字符串！");
    }

    return 0;
}

int fun(char *src)
{
    int len = strlen(src);
    char temp[len];
    for(int i = 0; i < len; ++i)
    {
        temp[i] = src[len-i-1];
    }
    int count = strcmp(temp, src);

    if(count == 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }

}
