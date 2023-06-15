#include <stdio.h>

int main()
{
    int p,b[10],i,w[10];
    float average;
    printf("Enter the number of processes:");
    scanf("%d",&p);
    printf("Enter the burst lengths\n");
    for(i=0;i<p;i++)
    {
        scanf("%d",&b[i]);
    }
    w[0]=0;
    for(i=0;i<p;i++)
    {
        w[i+1]=b[i]+w[i];
    }
    for(i=0;i<p;i++)
    {
        printf("waiting time of process %d is %d\n",i,w[i]);
        average+=w[i];
    }
    printf("Average waiting time is %f",average/p);
    return 0;
}
