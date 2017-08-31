/*************************************************************************
	> File Name: 8-29_2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月29日 01时02分30秒 PDT
 ************************************************************************/

#include<stdio.h>
int a;
static int b = 100;//只限定在本文件有用。
extern int c;
//extern int d;
extern void print();
extern void s_print();

int main()
{
    print();

    printf("a = %d\n b = %d\n c = %d\n", a, b , c);
  //  printf("%d\n", d);

   // s_print();
    return 0;
}
