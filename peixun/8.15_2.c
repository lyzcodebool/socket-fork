/*************************************************************************
	> File Name: 8.15_2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月14日 18时54分02秒 PDT
 ************************************************************************/

#include<stdio.h>
int main()
{
    int a[3][2] = {(1, 2), (3, 4), (5, 6)};

    int *p = a[0];

    printf("%d\n", p[0]);

    return 0;
}
