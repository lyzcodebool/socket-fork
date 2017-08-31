/*************************************************************************
	> File Name: Person.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月29日 20时03分21秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
void save(int m);
typedef void (*Pgedu)();
typedef void (*Psedu)();
#define Per \
    char name[20];\
    bool isfame;\
        int age;

struct Person
{
    Per;
};
struct Student
{
    Per;
    int Edu;
    int number;
    Pgedu pgedu;//函数指针
    Psedu psedu;//函数指针
}S, *p;
enum Edu
{
    primary,
    middle,
    high,
    university
}Select;
void setEdu()
{
    printf("请按照数字提示选择你的学历:\n");
    printf("0: primary\n1: middle\n2: high\n3: university\n");
    printf("请输入你的选择:\n");
    int m;
    scanf("%d", &m);
    switch(m)
    {
        case 0:
            save(m);break;
        case 1:
            save(m);break;
        case 2:
            save(m);break;
        case 3:
            save(m);break;
    }
}
void getEdu()
{
    FILE *fp;
    p = &S;
    if((fp = fopen("student.txt", "rb")) == NULL)
    {
        printf("Connot open the file!\n");
        return;
    }
    rewind(fp);
    printf("\nname(姓名) sex(性别) age(年龄) 学历\n");
    fread(p, sizeof(struct Student), 1, fp);
    printf("%s            %d        %d        %d\n", p->name, p->isfame, p->age, p->Edu);
    
}

void save(int m)
{
    printf("please input students' informations:\n");
    printf("name: ");
    scanf("%s",S.name);
    printf("\nsex(性别)(1.女生 0.男生): ");
    scanf("%d", &S.isfame);
    printf("\nage(年龄): ");
    scanf("%d", &S.age);
        //scanf("%s%d%d",S.name, &S.isfame, &S.age);
    S.Edu = m;
    
    FILE *fp;
    if((fp = fopen("student.txt", "wb"))== NULL)
    {
        printf("open file failed!\n");
        return;
    }
    if(fwrite(&S, sizeof(S), 1, fp) == 0)
    {
        printf("file write error!\n");
    }
}
int main()
{
    struct Student STU;
    
    STU.pgedu = getEdu;//函数指针指向函数体
    STU.psedu = setEdu;
    while(1)
    {
    printf("请选择你要进行的操作：\n");
    printf("\n1: 录入学生信息\n2: 修改信息\n3: 查看信息\n4: 退出\n");
    int m;
    scanf("%d", &m);
        switch(m)
        {
            case 1:
            STU.psedu();break;
            case 2:
            STU.psedu();break;
            case 3:
            STU.pgedu();break;
            case 4:
            return 0;break;
        }
    }
    return 0;
}
