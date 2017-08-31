/*************************************************************************
	> File Name: 8-29_3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月29日 02时13分55秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a = 4;
    int *p = &a;
    printf("%p\n", p);
    int *p1 = realloc(p, 10);
    printf("%p\n", p);


    printf("%p\n", p1);
    free(p);

}
