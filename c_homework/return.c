/*************************************************************************
	> File Name: return.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月27日 12时03分27秒 PDT
 ************************************************************************/

#include<stdio.h>
//int fun();
int *fun()
{
    int a = 10;
    return a;
}
//char *fun();
int main(){
   // for(int i = 0; i < 2; ++i)
   printf("%d\n", *fun());
    int *b = *fun();
    printf("%d\n", *b);
    return 0;
}
/*int fun()
{
    int a[2] = {1,2};
    return *a;
}*/ 
