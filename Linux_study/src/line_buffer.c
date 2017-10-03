/*************************************************************************
	> File Name: ./src/line_buffer.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月17日 12时51分22秒 PDT
 ************************************************************************/

#include<stdio.h>
/*行缓冲只有遇到换行符、程序结束或者行缓冲区满才会输出，这是证明*/
int main()
{
    printf("hello iotek");
 //   putchar(10);
    while(1)
    {
//        putchar(10);//这里不加换行符，hello iotek不会输出 
        
        sleep(2);
    };
}
