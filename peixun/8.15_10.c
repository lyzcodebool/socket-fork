/*************************************************************************
	> File Name: 8.15_10.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月15日 01时35分37秒 PDT
 ************************************************************************/

#include<stdio.h>
//常量传非常量有问题。
//非常量传给常量没问题
void print_array(const int a[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%d\n", a[i]);
    }
}

void print_array2(int a[], int n)
{
    for(int i= 0; i < n; ++i)
    {
        printf("%d\n", a[i] ++);
    }
}
int main()
{
    const int a[3] = {1,2,3};
    int b[3] = {4, 5, 6};

    print_array(a,3);
    print_array(b,3);
   // print_array2(a,3);
    print_array2(b, 3);

    return 0;
}
