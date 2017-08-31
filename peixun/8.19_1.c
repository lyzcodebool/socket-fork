/*************************************************************************
	> File Name: 8.19_1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月19日 09时48分02秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    char *str = "abc";
    int arr[strlen(str)];

    for(int i= 0; i < strlen(str); ++i)
    {
        arr[i] = i;
    }
    for(int i= 0; i < strlen(str); ++i)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
