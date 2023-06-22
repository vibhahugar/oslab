#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int remaining_time;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortByBurstTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void sortByPriority(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void SJF(struct Process processes[], int n) {
    sortByBurstTime(processes, n);

    int waiting_time = 0;
    int turnaround_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        turnaround_time += processes[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, waiting_time,
               turnaround_time);
        waiting_time += processes[i].burst_time;
    }

    printf("\nAverage waiting time: %.2f\n", (float) waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float) turnaround_time / n);
}

void Priority(struct Process processes[], int n) {
    sortByPriority(processes, n);

    int waiting_time = 0;
    int turnaround_time = 0;

    printf("Process\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        turnaround_time += processes[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].priority, waiting_time,
               turnaround_time);
        waiting_time += processes[i].burst_time;
    }

    printf("\nAverage waiting time: %.2f\n", (float) waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float) turnaround_time / n);
}

void RoundRobin(struct Process processes[], int n, int quantum) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int time = 0;
    int completed = 0;
    int waiting_time = 0;
    int turnaround_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= quantum) {
                    time += remaining_time[i];
                    waiting_time += time - processes[i].burst_time;
                    turnaround_time += time;
                    remaining_time[i] = 0;
                    completed++;
                } else {
                    time += quantum;
                    remaining_time[i] -= quantum;
                }
                printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, waiting_time,
                       turnaround_time);
            }
        }
    }

    printf("\nAverage waiting time: %.2f\n", (float) waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float) turnaround_time / n);
}

int main() {
    int n, choice, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Process ID: ");
        scanf("%d", &processes[i].pid);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        printf("\n");
    }

    printf("Select the scheduling algorithm:\n");
    printf("1. SJF (Non-preemptive)\n");
    printf("2. Priority (Non-preemptive)\n");
    printf("3. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            SJF(processes, n);
            break;
        case 2:
            Priority(processes, n);
            break;
        case 3:
            printf("Enter the time quantum for Round Robin: ");
            scanf("%d", &quantum);
            RoundRobin(processes, n, quantum);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
