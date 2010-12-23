#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
    int *p,*q;int i=0,k=0;

    p = (int *)malloc(40);
    q = p;
    while(1)
    {
        scanf("%d",q++);
        if(*(q-1) == -1)break;
        k++;      
        if(k == 8)
        {   
            p=(int *)realloc(p, 80);
        }
        
    }
    q = p;
    for (i = 0; i < k; i++) 
    {
        printf("%d ",*q++);
    }
    printf("\n");
    free(p);
    return 0;
}
