#include <stdio.h>
#include<math.h>

int main()
{
    int n, i, j;
    float u, ci, ti;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    float c[n], t[n], p[n];

    for (i = 0; i < n; i++)
    {
        printf("Enter the computation time of process %d: ", i + 1);
        scanf("%f", &ci);

        printf("Enter the period of process %d: ", i + 1);
        scanf("%f", &ti);

        c[i] = ci;
        t[i] = ti;
        p[i] = 1 / ti;
    }

    u = 0;

    for (i = 0; i < n; i++)
    {
        u += c[i] / t[i];
    }

    if (u > n * (pow(2, 1 / n) - 1))
    {
        printf("The given set of processes is not schedulable.\n");
        return 0;
    }

    printf("The given set of processes is schedulable.\n");

    float lcm = t[0];

    for (i = 1; i < n; i++)
    {
        lcm = (lcm * t[i]) / gcd(lcm, t[i]);
    }

    int timeline[lcm];

    for (i = 0; i < lcm; i++)
    {
        timeline[i] = -1;
    }

    int k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < lcm; j += t[i])
        {
            k = j;

            while (timeline[k] != -1)
            {
                k++;
            }

            if (k >= j + c[i])
            {
                break;
            }

            timeline[k] = i + 1;
        }
    }

    printf("\nGantt Chart:\n\n");

    for (i = 0; i < lcm; i++)
    {
        if (timeline[i] == -1)
        {
            printf("-");
        }
        else
        {
            printf("P%d", timeline[i]);
        }
    }

    return 0;
}

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    
    return gcd(b, a % b);
}
