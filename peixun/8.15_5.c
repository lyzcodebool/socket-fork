/*************************************************************************
	> File Name: 8.15_5.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月14日 20时43分17秒 PDT
 ************************************************************************/

#include<stdio.h>
int sum (int a, int b);
int main()
{
    int (*p)(int a, int b);
    p = sum;

    printf("%d %d", p(1,2), sum(1,2));

    return 0;
}

int sum (int a, int b)
{
    return a+b;
}
