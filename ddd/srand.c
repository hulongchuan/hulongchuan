#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int seed = 0;
    int num = 0;
    int i = 0, n = 0;
    int j = 0;
    char b[52], a[52];
    
    for (i = 0; i < 52; i++) 
    {
        a[i] = i+1;
        b[i] = 0;
    }
    seed = time(NULL);
    srand(seed);
    while(n < 52)
    {
        lp: num = rand()%52;
        for(i = 0; i < n; i++)
        {
            if(a[num] == b[i])
                goto lp;
        }
        b[n++] = a[num];
        switch(a[num]/13)
        {
            case 0:printf("hont%2d  ", a[num]%13+1);break;
            case 1:printf("heit%2d  ", a[num]%13+1);break;
            case 2:printf("meih%2d  ", a[num]%13+1);break;
            case 3:printf("fanp%2d  ", a[num]%13+1);break;
            case 4:printf("fanp13  ");break;
            default:break;
        }
        //printf("%3d", a[num]);
        j++;
        if(j % 13 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}
