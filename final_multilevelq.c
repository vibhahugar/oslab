#include<stdio.h>
void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void main()
{
    int n,pid[10],burst[10],type[10],arr[10],wt[10],ta[10],ct[10],i,j;
    float avgwt=0,avgta=0;
    int sum = 0;
    printf("Enter the total number of processes\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the process id, type of process(user-0 and system-1), arrival time and burst time\n");
        scanf("%d",&pid[i]);
        scanf("%d",&type[i]);
        scanf("%d",&arr[i]);
        scanf("%d",&burst[i]);
    }
    //sorting the processes according to arrival time
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
                swap(&pid[j],&pid[j+1]);
                swap(&burst[j],&burst[j+1]);
                swap(&type[j],&type[j+1]);

            }
        }
    }
    //assuming only two process can have same arrival time and different priority 
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(arr[j]==arr[j+1] && type[j]<type[j+1])
            {
                swap(&arr[j],&arr[j+1]);
                swap(&pid[j],&pid[j+1]);
                swap(&burst[j],&burst[j+1]);
                swap(&type[j],&type[j+1]);
            }
        }
    }
    //calculating completion time, arrival time and waiting time
    sum = sum + arr[0];
    for(i = 0;i<n;i++){
        sum = sum + burst[i];
        ct[i] = sum;
        ta[i] = ct[i] - arr[i];
        wt[i] = ta[i] - burst[i]; 
        if(sum<arr[i+1]){
            int t = arr[i+1]-sum;
            sum = sum+t;
        }
    }

    printf("Process id\tType\tarrival time\tburst time\twaiting time\tturnaround time\n");
    for(i=0;i<n;i++)
    {
        avgta+=ta[i];
        avgwt+=wt[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",pid[i],type[i],arr[i],burst[i],wt[i],ta[i]);
    }
    printf("average waiting time =%f\n",avgwt/n);
    printf("average turnaround time =%f",avgta/n);

}
