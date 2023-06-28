#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

struct P {
    int AT, BT, ST[20], WT, FT, TAT, pos;
};

int quant;

void printGanttChart(struct P p[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("+");
        for (int j = 0; j < p[i].BT; j++) {
            printf("-");
        }
    }
    printf("+\n");

    for (int i = 0; i < n; i++) {
        printf("|");
        for (int j = 0; j < p[i].BT; j++) {
            printf("P%d", p[i].pos);
        }
    }
    printf("|\n");

    printf("+");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].BT; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

int main() {
    int n, i, j;
    // Taking Input
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct P p[n];
    printf("Enter the quantum: ");
    scanf("%d", &quant);
    printf("Enter the process numbers:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &(p[i].pos));
    printf("Enter the Arrival time of processes:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &(p[i].AT));
    printf("Enter the Burst time of processes:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &(p[i].BT));
    // Declaring variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];
    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++) {
        b[i] = p[i].BT;
        a[i] = p[i].AT;
        for (j = 0; j < 20; j++)
            s[i][j] = -1;
    }
    int tot_wt, tot_tat;
    tot_wt = 0;
    tot_tat = 0;
    bool flag = false;
    while (c != 0) {
        mini = INT_MAX;
        flag = false;
        for (i = 0; i < n; i++) {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0) {
                index = i;
                mini = a[i];
                flag = true;
            }
        }
        // if at =1 then loop gets out hence set flag to false
        if (!flag) {
            time++;
            continue;
        }
        // calculating start time
        j = 0;
        while (s[index][j] != -1)
            j++;
        if (s[index][j] == -1) {
            s[index][j] = time;
            p[index].ST[j] = time;
        }
        if (b[index] <= quant) {
            time += b[index];
            b[index] = 0;
        } else {
            time += quant;
            b[index] -= quant;
        }
        if (b[index] > 0) {
            a[index] = time + 0.1;
        }
        // calculating arrival, burst, final times
        if (b[index] == 0) {
            c--;
            p[index].FT = time;
            p[index].WT = p[index].FT - p[index].AT - p[index].BT;
            tot_wt += p[index].WT;
            p[index].TAT = p[index].BT + p[index].WT;
            tot_tat += p[index].TAT;
        }
    } // end of while loop
    // Printing output
    printf("\nProcess number \tArrival time \tBurst time \tStart time \tFinal time \tWait Time \tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d \t\t%d \t\t%d \t\t", p[i].pos, p[i].AT, p[i].BT);
        j = 0;
        while (s[i][j] != -1) {
            printf("%d ", p[i].ST[j]);
            j++;
        }
        printf("\t\t%d \t\t%d \t\t%d\n", p[i].FT, p[i].WT, p[i].TAT);
    }
    // Calculating average wait time and turnaround time
    double avg_wt, avg_tat;
    avg_wt = tot_wt / (float) n;
    avg_tat = tot_tat / (float) n;
    // Printing average wait time and turnaround time
    printf("\nThe average wait time is: %lf\n", avg_wt);
    printf("The average Turnaround time is: %lf\n", avg_tat);

    printGanttChart(p, n);

    return 0;
}
