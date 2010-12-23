#include <stdio.h>
#include <string.h>
 struct max_t{
    char *fun;
    char *len_max;
 };
 struct max_t fff; 
char * get_maxstr(char *a,char *b)
{
    int i = 0,count = 0;
    for(i = 0; ; i++)
    {  
        while(*(a+i) == *(a+i+1))
        {
            count++;
            i++;
            if(i == strlen(a)-1)break;
        }
        if(count > *b)
        {
            *b = count;
            fff.fun = a + i;
        }
        if(i == strlen(a)-1)break;
        
        count = 0;
     } 
    return (fff.fun - *b );
}
int main(int argc, const char *argv[])
{
    char *a="abaaaddcccffffffcsda";
    char *p;
    int  i;char b=0;
    fff.len_max = &b;
    fff.fun = a;
    p = get_maxstr(a, fff.len_max);
    for (i = 0; i < *(fff.len_max)+1; i++) 
    {
        printf("%c",*(p+i));
    }
    printf("\n");
    return 0;
}
