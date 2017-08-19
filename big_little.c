/*************************************************************************
	> File Name: big_little.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月18日 03时42分25秒 PDT
 ************************************************************************/

#include<stdio.h>
void byteorder();
//测试大小端
int main()
{
    byteorder();

}

void byteorder()
{
    union
    {
        short value;
        char union_bytes[sizeof(short)];
    }test;
    test.value = 0x0102;
    if(test.union_bytes[0] == 1 && test.union_bytes[1] == 2)
    {
        printf("big");
    }
    else if(test.union_bytes[0] == 2 && test.union_bytes[1] == 1)
    {
        printf("little");
    }
    else
    {
        printf("unknow");
    }
}
