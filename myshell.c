#include <stdio.h>
#include <string.h>
struct cmd{
    char *command[8];
    char *in;
    char *out;
};
struct cmd cmd1;

char parse(char *a)
{
    char *p = a;int i=0;
    cmd1.in = cmd1.out = NULL;
    while(1)
    {
         if(*p++ == ' ') 
         {
            *(p-1) = '\0';
            if(*p != ' ')
            {
                cmd1.command[i] = p;
                i++;
            }
         }
         if(*p == '<'){cmd1.command[i-1] = NULL;while(*p++ == ' ')*(p - 1 ) = '\0';cmd1.in = p++;}
         if(*p == '>'){cmd1.command[i-1] = NULL;while(*p++ == ' ')*(p - 1 ) = '\0';cmd1.out = p++;}
         if(*p == '\0'){break;}
   }
    return 0;
}


int main(int argc, const char *argv[])
{
    char a[256];int i;char *p;
    fgets(a, 256, stdin);
    char b[256] = " "; 
    parse(strcat(b, a));
    for (i = 0; i < 8; i++) 
    {
        p = cmd1.command[i];
        if(p == NULL)break;
        if(i==0)
           printf("command :%s  ",p);
        else
           printf("argument:%s  ",p);
    }
    if(cmd1.in || cmd1.out)
       printf("in_file:%s   out_file:%s   \n", cmd1.in, cmd1.out);
    return 0;
}
