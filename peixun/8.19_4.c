/*************************************************************************
	> File Name: 8.19_4.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月19日 14时20分17秒 PDT
 ************************************************************************/

#include<stdio.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    int a = 12, b = 13;
    swap(&a, &b);

    printf("a = %d  b = %d\n", a, b);

    return 0;
