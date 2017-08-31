/*************************************************************************
	> File Name: 8.15_7.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月14日 23时24分20秒 PDT
 ************************************************************************/

#include<stdio.h>
int main()
{
    int a[5] = {1, 2, 3, 4, 5};

    printf("sizeof(unsigned long): %lu\n", sizeof(unsigned long));
    printf("sizeof(int): %lu\nsizeof(a): %lu\nszieof(&a): %lu\nsizeof(&a[0]): %lu\n",sizeof(int), sizeof(a), sizeof(&a), sizeof(&a[0]));

    printf("sizeof(&a[4]): %lu\n", sizeof(&a[4]));

    printf("a: %p\n&a : %p\n&a[0]: %p\na+1 : %p\n&a+1 : %p\n&a[0]+1: %p\n",a, &a, &a[0], a+1, &a+1, &a[0] + 1);

    printf("a[-1] : %d\n",a[-1]);
    return 0;
}
