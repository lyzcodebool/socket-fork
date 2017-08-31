/*************************************************************************
	> File Name: 8-29.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月29日 00时30分46秒 PDT
 ************************************************************************/

#include<stdio.h>
void fun()
{
    int a = 0;
    static int b;
    int c;
    printf("b = %d c = %d ", b,c);
    a++;
    b++;
}
int main()
{
    int a = 1;
    int *p;
    p = 0;
    p = &a; 
    printf("%d", *p);
}
