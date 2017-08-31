/*************************************************************************
	> File Name: 8.15_4.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月14日 20时19分49秒 PDT
 ************************************************************************/

#include<stdio.h>
//指针数组
/*int main()
{
    int a = 1, b = 2, c = 3;
    int *p[3] = {&a, &b, &c};
    
    for(int i= 0; i < 3; ++i)
    {
        printf("%d %p\n", *p[i], p[i]);
    }
    putchar(10);
    return 0;
}*/

//数组指针
int main()
{
    int a[2][3]= {1, 2, 3, 4, 5, 6};
    int (*p)[3];
    p = a;

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 3; ++j)
          {
              printf("%d ", p[i][j]);
              printf("%d\t", *(*(p + i)+j));
          }
    }
    return 0;
}
