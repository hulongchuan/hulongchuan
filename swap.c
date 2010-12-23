#include <stdio.h>
#include <string.h>
struct stu{
    int id;
    int chinese;
    char name[256];
};
struct stu stu1={1111, 100, "hulong"};
struct stu stu2={2222, 200, "longchuan"};
void swap(struct stu *a, struct stu *b)
{
    int x, y ;char c[100];
    x = a->id; 
    a->id = b->id;
    b->id = x;
    y = a->chinese;
    a->chinese = b->chinese;
    b->chinese = y;
    strcpy(c, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, c);
    
}
int main(int argc, const char *argv[])
{
    int i;
    swap(&stu1, &stu2);
    printf("id:%d chinese:%d name:%s\n",stu1.id,stu1.chinese,stu1.name);
    printf("id:%d chinese:%d name:%s\n",stu2.id,stu2.chinese,stu2.name);
    return 0;
}
