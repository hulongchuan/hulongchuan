#include <stdio.h>
#define M 3
#define N 10
typedef struct pep{
    int id;
    int out;
}pep_t;

pep_t people[N];

int main(int argc, const char *argv[])
{
    int i,j,k=0,count=0,m=0;
    for (i = 0; i < N; i++) 
    {
        people[i].id = i + 1;
        people[i].out = 0;
    }
    //for (i = 0; i < N; i++) 
    //{
        //for (; ; ) 
        //{   
            //if(people[m].out == 0)
            //{
                //count++;
                //if(count == 3)
                //{
                    //count = 0;
                    //people[m].out = 1;
                    //printf("%d\n",people[m].id);
                    //break;
                //}
            //}   
            //m++;
            //if(m==10)m=0;
        //}
    //}
    
    while(1)
    {
        for (j = 0; j < N; j++) 
        {
            if(people[j].out == 0)
            {
                count++;
                if(count==3)
                {
                    count=0;
                    people[j].out=1;
                    printf("%d\n",people[j].id);
                    k++;if(k == N)goto lp;
                }
            }
        }
        
    }
  lp: return 0;
}
