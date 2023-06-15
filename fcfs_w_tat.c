#include <stdio.h>

int main()
{
    int p,b[10],i,w[10],a[10],c[10],z[10];
    float average;
    
    printf("Enter the number of processes:");
    scanf("%d",&p);
    printf("Enter the burst lengths:\n");
    
    for(i=0;i<p;i++)
    {
        scanf("%d",&b[i]);
    }
    printf("Enter the arrival time:\n");
    
    for(i=0;i<p;i++)
    {
        scanf("%d",&a[i]);
    }
    
    w[0]=0;
    
    for(i=0;i<p;i++)
    {
        w[i+1]=b[i]+w[i];
    }
    for(i=0;i<p;i++)
    {
        c[i]=w[i+1]-a[i];
    }
    
    for(i=0;i<p;i++)
    {
        printf("turn around time is %d is %d\n",i,c[i]);
        average+=c[i];
    }
    printf("Average turn around time is: %f\n",average/p);
    average=0;
    
    for(i=0;i<p;i++)
    {
        z[i]=c[i]-b[i];
         printf("waiting time of process %d is %d\n",i,z[i]);
        average+=z[i];
    }
    printf("Average waiting time is: %f",average/p);
    return 0;
}
