/*************************************************************************
	> File Name: 8.19_6.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月19日 15时17分30秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdarg.h>

int sum(int num , ...);
int main()
{
    printf("%d \n", sum(6, 2.0, 3.1, 4, 5.9, 0.9, 1));
}

int sum(int num, ...)
{
    va_list ap;
    va_start(ap , num);
    double total = 0;
    for(int i= 0; i < num; ++i)
    {
        int temp = va_arg(ap, int);
        printf("%d \n", temp);
        total += temp;
    }

    va_end(ap);
    return total;
}
