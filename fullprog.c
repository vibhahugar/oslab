#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
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

void SJF_Preemptive(struct Process processes[], int n) {
    int remaining_time[n];
    int completion_time = 0;
    int total_completion_time = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    bool visited[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        visited[i] = false;
    }

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    while (true) {
        int shortest_job = -1;
        int min_burst_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= completion_time && !visited[i]) {
                if (remaining_time[i] < min_burst_time) {
                    shortest_job = i;
                    min_burst_time = remaining_time[i];
                }
            }
        }

        if (shortest_job == -1) {
            break;
        }

        visited[shortest_job] = true;
        waiting_time += completion_time - processes[shortest_job].arrival_time;
        completion_time++;
        remaining_time[shortest_job]--;

        if (remaining_time[shortest_job] == 0) {
            turnaround_time = completion_time - processes[shortest_job].arrival_time;
            printf("%d\t%d\t\t%d\t\t%d\n", processes[shortest_job].pid, processes[shortest_job].burst_time,
                   waiting_time, turnaround_time);
        }
    }

    printf("\nAverage waiting time: %.2f\n", (float) waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float) turnaround_time / n);
}

void SJF_NonPreemptive(struct Process processes[], int n) {
    sortByBurstTime(processes, n);

    int waiting_time = 0;
    int turnaround_time = 0;
    int completion_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        completion_time += processes[i].burst_time;
        turnaround_time = completion_time - processes[i].arrival_time;
        waiting_time = turnaround_time - processes[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, waiting_time,
               turnaround_time);
    }

    printf("\nAverage waiting time: %.2f\n", (float) waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float) turnaround_time / n);
}

void Priority_Preemptive(struct Process processes[], int n) {
    int remaining_time[n];
    int completion_time = 0;
    int total_completion_time = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    bool visited[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        visited[i] = false;
    }

    printf("Process\tPriority\tWaiting Time\tTurnaround Time\n");

    while (true) {
        int highest_priority = -1;
        int min_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= completion_time && !visited[i]) {
                if (processes[i].priority < min_priority) {
                    highest_priority = i;
                    min_priority = processes[i].priority;
                }
            }
        }

        if (highest_priority == -1) {
            break;
        }

        visited[highest_priority] = true;
        waiting_time += completion_time - processes[highest_priority].arrival_time;
        completion_time++;
        remaining_time[highest_priority]--;

        if (remaining_time[highest_priority] == 0) {
            turnaround_time = completion_time - processes[highest_priority].arrival_time;
            printf("%d\t%d\t\t%d\t\t%d\n", processes[highest_priority].pid, processes[highest_priority].priority,
                   waiting_time, turnaround_time);
        }
    }

    printf("\nAverage waiting time: %.2f\n", (float) waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float) turnaround_time / n);
}

void Priority_NonPreemptive(struct Process processes[], int n) {
    sortByPriority(processes, n);

    int waiting_time = 0;
    int turnaround_time = 0;
    int completion_time = 0;

    printf("Process\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        completion_time += processes[i].burst_time;
        turnaround_time = completion_time - processes[i].arrival_time;
        waiting_time = turnaround_time - processes[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].priority, waiting_time,
               turnaround_time);
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
            if (processes[i].arrival_time <= time && remaining_time[i] > 0) {
                if (remaining_time[i] <= quantum) {
                    time += remaining_time[i];
                    waiting_time += time - processes[i].burst_time;
                    turnaround_time += time - processes[i].arrival_time;
                    remaining_time[i] = 0;
                    completed++;

                    printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time,
                           waiting_time, turnaround_time);
                } else {
                    time += quantum;
                    remaining_time[i] -= quantum;

                    printf("%d\t%d\t\t%d\t\t-\n", processes[i].pid, quantum, waiting_time);
                }
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
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        printf("\n");
    }

    printf("Select the scheduling algorithm:\n");
    printf("1. SJF (Pre-emptive)\n");
    printf("2. SJF (Non-preemptive)\n");
    printf("3. Priority (Pre-emptive)\n");
    printf("4. Priority (Non-preemptive)\n");
    printf("5. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            SJF_Preemptive(processes, n);
            break;
        case 2:
            SJF_NonPreemptive(processes, n);
            break;
        case 3:
            Priority_Preemptive(processes, n);
            break;
        case 4:
            Priority_NonPreemptive(processes, n);
            break;
        case 5:
            printf("Enter the time quantum for Round Robin: ");
            scanf("%d", &quantum);
            RoundRobin(processes, n, quantum);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
