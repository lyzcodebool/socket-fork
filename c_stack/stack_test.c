/*************************************************************************
	> File Name: stack_test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月26日 20时17分13秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int *data;
    int top;
}Stack;

//栈初始化
Stack *stack_init(int stack_size){
    Stack *p;
    p = (Stack *)malloc(sizeof(Stack));
    if((p->data = (int *)malloc(stack_size * sizeof(int))) != 0){
        //printf("comed!\n");
        p->top = 0;
        printf("init top = %d\n", p->top);
        return p;
    }
    printf("申请内存失败！\n");
    return NULL;
}

//数据入栈
int stack_push(Stack *stack, int array_len, int data_arg){
    if(((stack->top) + 1) > array_len){
        printf("栈满\n");
        return 0;
    }else{
        //printf("comed!\n");
        //printf("top = %d\n", stack->top);
        stack->top ++;
        //printf("top ++ = %d\n", stack->top);
        stack->data[stack->top] = data_arg;
        return 1;
    }
}

//数据出栈
int stack_pop(Stack *stack){
    if(stack->top == -1){
        perror("栈空");
        return 0;
    }else{
        return (stack->data[stack->top--]);
    }
}
//获取栈顶元素
int getdata_top(Stack *stack){
    if(stack->top == 0){
        perror("栈空");
        return 0;
    }else{
        return (stack->data[stack->top]);
    }
}

//清空栈
void stack_clear(Stack* stack){
    stack->top = 0;
}
//释放栈空间
void stack_free(
    Stack *stack){
    if(stack){
        free(stack);
    }
}
int main(void)
{
    int array_len;
    printf("请输入你想申请的栈数组大小:\n");
    scanf("%d", &array_len);

    Stack *stack = stack_init(array_len);    
    printf("main top = %d\n", stack->top);
    printf("stack %p\n", stack);
    
    //数据入栈
    int temp;
    //这里我只测试5个数，count作为计数器
    int count1 = 0;
    int count2 = 0;
    do{
        printf("请输入数据：\n");
        scanf("%d", &temp);
        stack_push(stack, array_len, temp);
        count1 ++;
    }while(count1 <= 5);

    do{
        printf("请按任意键进行出栈操作:\n");
        getchar();
        int pop =  stack_pop(stack);
        printf("出栈的数据是%d\n", pop);
        count2++;
    }while(count2 <= 5);


    return 0;
}
