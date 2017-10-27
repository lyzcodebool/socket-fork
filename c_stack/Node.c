/*************************************************************************
	> File Name: Node.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月22日 23时41分57秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct node{
    ElementType data;
    struct node *next;
}Node;

typedef Node* List;

//创建新链表
List MakeEmpty(){
    List link_table = (List)malloc(sizeof(struct node));
    link_table->data = 0;
    link_table->next = NULL;
    return link_table;
}
//打印链表
void Print_Table(List L){
    List temp = L;
    while(temp != NULL){
        printf("%d|", temp->data);
        temp = temp->next;
    }
    putchar(10);
}
//向链表中插入数据
void Insert_Node(List L, ElementType e){
    List new_node;
    new_node = (List)malloc(sizeof(struct node));
    new_node->data = e;
    while(L->next != NULL){
        L = L->next;
    }
    new_node->next = L->next;
    L->next = new_node;
}

//头插
void Head_Insert(List *H, ElementType e){
    List new_node;
    new_node = (List)malloc(sizeof(struct node));
    new_node->data = e;
    new_node->next = *H; 
    *H = new_node;
}
//delet ElementType
void Dele_Elem(List L, ElementType e){
    if(L->data == e){
        L->next = NULL;
        free(L);
    }
    while(L->next->data != e){
        L = L->next;
    }
}
int main()
{
    List L = MakeEmpty();
    Insert_Node(L, 10);
    Head_Insert(&L, 11);
    Print_Table(L);
    return 0;
}
