#include <stdio.h>
int my_strlen(const char *a)
{
    int count = 0;

    while(*a++) count++;

    return count;
}
int main(int argc, const char *argv[])
{
    char a[]="abcde";
    printf("%d\n",my_strlen(a));
    return 0;
}
