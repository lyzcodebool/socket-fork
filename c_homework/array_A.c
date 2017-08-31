/*************************************************************************
	> File Name: array_A.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月20日 18时19分18秒 PDT
 ************************************************************************/

#include<stdio.h>
//homework3 数组A中的0移至末尾，非零整数有序排列I
/*感觉把数组元素降序排列就好了*/
//#define nSIZE 10
int Func(int *A, int nSIZE);
void swap(int *a, int *b);
int main()
{
    int A[] = {1, [3] = 3, [6] = 8}; 
    int nSIZE = sizeof(A) / sizeof(int);
    
    printf("排序前：\n");
    for(int i = 0; i < nSIZE; ++i)
    {
        printf("%d ", A[i]);
    }
    putchar(10);

    int count = Func(A, nSIZE);
    
    for(int i = 0; i < nSIZE; ++i)
    {
        printf("%d ", A[i]);
    }
    
    putchar(10);

    printf("数组的第一个0直对应的下标为： %d\n", count);

    return 0;
}

int Func(int *A, int nSIZE)
{
   for(int i = 0; i < nSIZE - 1; ++i)
    {
        for(int j = 0; j < nSIZE - i - 1; ++j)
        {
            if(A[j] < A[j+1])
            {
              swap(&A[j], &A[j+1]);  
            }
        }
    }
    for(int i = 0; i < nSIZE; ++i)
    {
        if(A[i] == 0)
        return i;
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
