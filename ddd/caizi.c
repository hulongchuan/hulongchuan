#include <stdio.h>

int main(int argc, const char *argv[])
{
    int num = 0;
    unsigned int cai = 0;
    int n = 0, i = 0, j = 0;
    char a[4]={11};
    char b[4];
    int sum = 0;
    char aa;

    srand(time(NULL));
    while(n < 4)
    {
        lp: num = rand()%10;
            for(i = 0; i < 4; i++)
            {
                if(num == a[i])
                    goto lp;
            }
        a[n++] = num;
    }
    lp1:scanf("%d", &cai);
    if(cai > 9999 &&  cai < 1000)
    {   
        printf("your input is wrong ,please input again!\n");
        goto lp1; 
    }
    else
    {
        b[0] = cai/1000;
        b[1] = cai%1000/100;
        b[2] = cai%100/10;
        b[3] = cai%10;
    }
    if(b[0] == b[1] || b[0] == b[2] || b[0] == b[3] || b[1] == b[2] || b[1] == b[3] || b[2] == b[3])
    {
        printf("your input is wrong ,please input again!\n");
        goto lp1;
    }
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
        {
            if(a[i] == b[j])
            {
                if(i == j)
                    sum = sum + 10;
                else
                    sum = sum + 1;
            }
        }
    switch(sum)
    {
        case 0: printf("All your answer is wrong! come on...\n"); sum = 0; break;
        case 1: printf("B\n");sum = 0; break;
        case 2: printf("BB\n");sum = 0;break;
        case 3: printf("BBB\n");sum = 0; break;
        case 4: printf("BBBB\n");sum = 0;break;;
        case 10:printf("A\n");sum = 0; break;
        case 11:printf("AB\n");sum = 0;break;
        case 12:printf("ABB\n");sum = 0; break;
        case 13:printf("ABBB\n");sum = 0; break;
        case 20:printf("AA\n");sum = 0; break;
        case 21:printf("AAB\n");sum = 0; break;
        case 22:printf("AABB\n");sum = 0; break;
        case 30:printf("AAA\n");sum = 0; break;
        case 40:printf("AAAA,you won!!!\n");sum = 0; goto lp2;
        default:break;
    }
    goto lp1;
   /* printf("Do you want to paly it again ?(y/n)");
    scanf("%c", &aa);
    if(aa == '\n' || aa == 'y')
    {
        sum = 0;
        n = 0;
        for (i = 0; i < 4; i++) 
        {
            a[i] = 11;
        }
        goto lp2;
    }*/
        
    lp2: return 0;
}
