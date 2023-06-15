#include <stdio.h>
void addition(int a[10][10],int b[10][10],int m1, int n1,int m2,int n2)
{
    int i,j;
    int c[m1][n1];
    if(m1!=n1 || m2!=n2)
    {
        printf("addition not possible\n");
        return;
    }
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            c[i][j]=a[i][j]+b[i][j];
        }
    }
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            printf("%d\t",c[i][j]);
        }
        printf("\n");
    }
}
void subraction(int a[10][10],int b[10][10],int m1, int n1,int m2,int n2)
{
    int i,j;
    int c[m1][n1];
    if(m1!=n1 || m2!=n2)
    {
        printf("subraction not possible\n");
        return;
    }
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            c[i][j]=a[i][j]-b[i][j];
        }
    }
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            printf("%d\t",c[i][j]);
        }
        printf("\n");
    }
}
void multiplication(int a[10][10],int b[10][10],int m1, int n1,int m2,int n2)
{ int i,j,k;
int c[m1][n1];
    if(n1!=m2)
    {
        printf("multiplication is not possible");
    }
    for(i=0;i<m1;i++)
    {
        for(int j=0;j<n2;j++)
        {
            c[i][j]=0;
            for(int k=0;k<n1;k++)
            {
                c[i][j]+=a[j][k]*b[k][j];
            }
            
        }
    }
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            printf("%d\t",c[i][j]);
        }
        printf("\n");
    }
}
void transpose(int a[10][10],int b[10][10],int m1, int n1,int m2,int n2)
{
    int c[m1][n1], d[m2][n2],i,j;
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            c[i][j]=a[j][i];
        }
    }
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            printf("%d\t",c[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<m2;i++)
    {
        for(j=0;j<n2;j++)
        {
            d[i][j]=b[j][i];
        }
    }
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            printf("%d\t",d[i][j]);
        }
        printf("\n");
    }
    
}

int main()
{
    int m1,n1,m2,n2,choice,i,j;
    int a[10][10],b[10][10];
    printf("Enter the number of rows and columns of matrix 1:");
    scanf("%d%d",&m1,&n1);
    printf("Enter the elements of matrix 1:\t");
    for(i=0;i<m1;i++)
    {
        for(j=0;j<n1;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    printf("Enter the number of rows and columns of matrix 2:");
    scanf("%d%d",&m2,&n2);
    printf("Enter the elements of matrix 2:\t");
    for(i=0;i<m2;i++)
    {
        for(j=0;j<n2;j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
    printf("1.Addition\t2.Subraction\t3.Multiplication\t4.Transpose\n");
    printf("Enter your choice:\t");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:addition(a,b,m1,n1,m2,n2);
                    break;
        case 2:subraction(a,b,m1,n1,m2,n2);
                    break;
        case 3:multiplication(a,b,m1,n1,m2,n2);
                    break;
        case 4:transpose(a,b,m1,n1,m2,n2);
                    break;
        default:printf("wrong chopice");
        
    }
    return 0;
}
