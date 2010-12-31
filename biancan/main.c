#include <stdio.h>
void myprint(char *format, ...)
{
    char *p =(char *)&format;
    p = p + 4;
    printf("%s %s %s\n",*(int*)p,*(int *)(p+4),*(int *)(p+8));
}
int main(int argc, const char *argv[])
{
    myprint(" ","how ","are ","you !");
    return 0;
}
