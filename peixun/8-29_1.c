/*************************************************************************
	> File Name: 8-29_1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月29日 01时00分47秒 PDT
 ************************************************************************/

#include<stdio.h>
int a =6;
static int b = 10;
int c = 5;
void print()
{
    printf("a = %d\n b = %d\n c = %d\n", a, b , c);
}
static void s_print()
{
    printf("a = %d\n b = %d\n c = %d\n", a, b , c);
    
}
