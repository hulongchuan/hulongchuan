#include <stdio.h>
int cmp_int(void *a, void *b)
{
    return (*((int*)a)-*((int*)b));
}
int cmp_char(void *a, void *b)
{
    return (*((char*)a)-*((char*)b));
}
void * get_max(int (*fun)(void *, void *), void *a, int len, int size)
{
    int i;
    void * max;
    max = a;
    for (i = 0; i < len-1; i++) 
    {
        if((* fun)(max, a + size * (i+1)) < 0)
            max = a + size * (i+1);
        
    }
    return max;
}
int main(int argc, const char *argv[])
{
    int a[10] = {10000, 112, 2, 41, 22, 46, 5, 1, 8, 9};
    char b[10]={1, 2, 10, 14, 45, 55, 110, 22, 11, 0};
    void * ret;
    void *re ;
    ret = get_max(cmp_char, b, 10, 1);
    re = get_max(cmp_int, a, 10, 4);
    printf("%d\n",*((char*)ret));
    printf("%d\n",*((int*)re));
    return 0;
}
