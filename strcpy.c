#include <stdio.h>
char * my_strcpy(char *a,const char *b)
{
    int i;
    for (i = 0; *(b+i) != '\0' ; i++) 
    {
        *(a+i) = *(b+i);
    }
    *(a+i) = '\0';
    return a;
}
int main(int argc, const char *argv[])
{
    char a[10],*b="abcd";

    my_strcpy(a, b);
    printf("%s\n", a);

    return 0;
}
