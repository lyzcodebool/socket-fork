/*************************************************************************
	> File Name: 8.15_3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月14日 19时05分40秒 PDT
 ************************************************************************/

#include<stdio.h>
int Sum(int m, int n, int a[*][*]);
int main()
{
    int m = 3,n = 2;
    int a[3][2] = {{1,2}, {3,4}, {5,6}};

    int sum = Sum(m,n,a);
    printf("%d\n", sum);
    return 0;
}

int Sum( int m, int n, int a[][n])
{
    int sum = 0;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            sum += a[i][j];
        }
    }
    return sum;
}
