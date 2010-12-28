#include <stdio.h>

int main(int argc, const char *argv[])
{
    FILE * txt, *dd;int a;char b[1024];char *c;
    txt = fopen(argv[1],"r");
    dd = fopen(argv[2], "w");
    while(1)
    { 
        a = fgetc(txt);
        if(a == EOF) break;
        fputc(a,dd);
        printf("%c",a);
    }
    while(1)
    {
        c = fgets(b, 1024, txt);
        if(feof(txt)) break;
        fputs(a,dd);
        printf("%s",c);
    }
    return 0;
}
