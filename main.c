#include <stdio.h>

void make_bit( unsigned int a)
{
    int m, i ;
    for (i = 0; i < 32; i++) 
    {
        m = a & 1;
        a >>= 1;
        printf("%d", m);
    }
    printf("\n");
}
unsigned int multiply(unsigned int a, unsigned int b)   //made by myself
{
    unsigned int i, m = 0, n = 0;
    for (i = 0; i < 8; i++) 
    {
        m = m + ((a & 0x01)<<i);
        a>>=1;
    }
    for (i = 0; i < 8; i++) 
    {
        n = n + ((b & 0x01)<<i);
        b>>=1;
    }
    return m*n;
}
void low_to_up(char *a)
{
    char *p = a;
    while(*p != '\0')
    {
        if(*p >= 'A' && *p <= 'Z') printf("%c", *p+32);        
        if(*p >= 'a' && *p <= 'z') printf("%c", *p-32);
        p = p++;
    }
    printf("\n");
}
void secret()
{
    char a = '&', b, r;
    scanf("%c",&b);
    r = a ^ b;
    if(r != '\0'&& r != '\n'&& r != ' ')
        printf("resault = %c\n",r);
    else
        printf("The character is not visible\n");
}
unsigned int mul(unsigned int a, unsigned int b)  //made by teacher
{
    unsigned int i, m = 0;
    for (i = 0; i < 32; i++) 
    {
        if(b>>i&0x01)
        {
            m += a<<i;
        }
    }
    return m;
}

int main(int argc, const char *argv[])
{
    unsigned int  a , b , c, i;
    char k[100], j;
    printf("1. decimal to binary\n");
    printf("2. x*y\n");
    printf("3. low or up exchange\n");
    printf("4. encryption\n");
    printf("5. Exist\n");
    printf("please choose [1-5]: ");
    while(1)
    {
        scanf("%d",&i);
        if(i == 5)break;
        switch(i)
        {
            case 1: printf("please input the nummber: ");scanf("%d",&c);make_bit(c); break;
            case 2: printf("please input the value of x: ");
                    scanf("%d", &a);
                    printf("please input the value of y: ");
                    scanf("%d", &b);
                    printf("x * y = %d\n", mul(a, b)); break;
            case 3: printf("please input the string: ");scanf("%s", k);low_to_up(k);break;   
            case 4: printf("please input the character: ");scanf("%c", &j); secret(j);break;
            default: break;
        }
    }
    return 0;
}
