#include <stdio.h>
int add(int a, int b)  // +
{
    return a + b;
}
int sub(int a, int b)  //  -
{
    return a - b;
}
int mul(int a, int b)  //  *
{
    return a * b;
}
int div(int a, int b)  //  /
{
    return a / b;
}
int del(int a, int b)  //   %
{
    return a % b;
}
int main(int argc, const char *argv[])
{
    int (* fun)(int, int);
    char z;int x, y;
    while(1)
    {
        scanf("%c", &z);
        if(z == '+')
        {
            fun = add;
            scanf("%d%d",&x,&y);
            printf("%d\n",(*fun)(x, y));
        }
        if(z == '-')
        {
            fun = sub;
            scanf("%d%d",&x,&y);
            printf("%d\n",(*fun)(x, y));
        }
        if(z == '*')
        {
            fun=mul;
            scanf("%d%d",&x,&y);
            printf("%d\n",(*fun)(x, y));
        }
        if(z == '/')
        {
            fun=div;
            scanf("%d%d",&x,&y);
            printf("%d\n",(*fun)(x, y));
        }
        if(z == '%')
        {
            fun=del;
            scanf("%d%d",&x,&y);
            printf("%d\n",(*fun)(x, y));
        }
        if(z == '#') break;
    }
    return 0;
}
