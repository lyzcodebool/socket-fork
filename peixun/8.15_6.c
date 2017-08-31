/*************************************************************************
	> File Name: 8.15_6.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月14日 20时53分46秒 PDT
 ************************************************************************/

#include<stdio.h>
int function1(int a);
int function2(int a);
int function3(int a);


int main()
{
    int (*p[3])(int a);
    p[0] = function1;
    p[1] = function2;
    p[2] = function3;
    for(int i = 0; i < 3; ++i)
    {
        p[i](1);
    }

}

int function1(int a)
{
    printf("int function1\n");
    return 0;
}
int function2(int a)
{
    printf("int function2\n");
    return 0;
}

int function3(int a)
{
    printf("int function3\n");
    return 0;
}
