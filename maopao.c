#include <stdio.h>
void cmp_int(void *a, void *b)
{
     int x;
     if(*(int*)a - *(int*)b > 0)
     {
          x =  *((int*)a) ;
          *((int*)a ) = *((int*)b);
          *((int*)b) = x;
     }
}
void cmp_char(void *a, void *b)
{
     char x;
     if(*(char*)a - *(char*)b > 0)
     {
          x =  *((char*)a) ;
          *((char*)a ) = *((char*)b);
          *((char*)b) = x;
     }
}
void sort(void *a, int size ,int len,void (* fun)(void *, void *))
{
   int i,j;
   for (i = 0; i < len-1; i++) 
   {
       for (j = 0; j < len - i - 1; j++) 
       {
          (* fun)(a+j*size, a+(j+1)*size);
       }
   }
}
int main(int argc, const char *argv[])
{
    int i;
    int a[10]={0, 1, 2, 8, 9, 4, 6, 3, 7, 5};   
    char b[10]={11, 12, 15, 16, 18, 19, 14, 10, 17, 13};
    sort(b, 1, 10, cmp_char);
    sort(a, 4, 10, cmp_int);
    for (i = 0; i < 10; i++) 
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    for (i = 0; i < 10; i++) 
    {
        printf("%d ",b[i]);
    }
    printf("\n");
    return 0;
}
