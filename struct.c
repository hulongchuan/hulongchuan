#include <stdio.h>
#include <string.h>
typedef struct stu{
    char name[100];
    int id;
    int chinese;
    void (* fun)(void);
}stu_t;
void print_1 (void){printf("mark : *\n");}
void print_2 (void){printf("mark : #\n");}
stu_t arr[5]={
    {"hulong", 1111, 100, print_1},
    {"hu l c", 2222, 110, print_2},
    {"longch", 3333, 120, print_2},
    {"hu lch", 4444, 130, print_1},
    {"hu chu", 5555, 140, print_2},
};
int main(int argc, const char *argv[])
{
    int i;

    for (i = 0; i < 5; i++) {
        printf("name:%s  id=%d chinese= %d ", arr[i].name, arr[i].id, arr[i].chinese);
       (* arr[i].fun)();
    }

    return 0;
}
