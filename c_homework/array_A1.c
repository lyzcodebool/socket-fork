/*************************************************************************
	> File Name: array_A1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月20日 23时31分10秒 PDT
 ************************************************************************/

#include<stdio.h>
//原来忘了考虑数组中存在负数怎么办
void swap(int *a, int *b);
void bubble(int *A, int nSize);
int Func(int *A, int nSize);
int main()
{
    int array[] = {-1, [2] = 0, 4, 9, [8] = -2};
    int arrlen = sizeof(array)/sizeof(int);
    //printf("arrlen: %d\n", arrlen);
    
    printf("处理前：\n");
    for(int i = 0; i < arrlen; ++i)
    {
       printf("%d ", array[i]); 
    }
    putchar(10);
    Func(array, arrlen);
    
    printf("处理后：\n");
    for(int i = 0; i < arrlen; ++i)
    {
       printf("%d ", array[i]); 
    }
    putchar(10);

    return 0;
}
int Func(int *A, int nSize)
{
    int flag = 0;
    for(int i = 0; i < nSize - flag; ++i)
    {
        flag = 0;
        if(A[i] == 0)
        {
            flag++;
            while(A[nSize - flag] == 0)//防止存在0已经在末尾
            {
                flag ++;
            }
            if(i <= nSize - flag)//交换以后的不再交换。
            swap(&A[i], &A[nSize - flag]);
        }
    }
    printf("处理后第一个0位置下标: %d\n", flag - 1);
    bubble(A, nSize - flag + 1);

}
void bubble(int *A, int nSize)
{
    for(int i = 0; i < nSize - 1; ++i)
    {
        for(int j = 0; j < nSize - i -1; ++j)
        {
            if(A[j] < A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
            }
        
        }
    }
}
void swap(int *a, int *b)
{
    int temp =  *a;
    *a = *b;
    *b = temp;
}
