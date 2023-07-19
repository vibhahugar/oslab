
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int deadline;
    int execution;
    int execution_copy;
} Task;

int min(Task *tasks, int n);
void update_execution_copy(Task *tasks, int n);
void execute_task(Task *tasks, int task_id, int timer);

int main() {
    int n, timer = 0;
    float cpu_utilization;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task *tasks = malloc(n * sizeof(Task));

    // Input task parameters
    for (int i = 0; i < n; i++) {
        printf("Enter Task %d parameters:\n", i + 1);
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution);
        printf("Deadline time: ");
        scanf("%d", &tasks[i].deadline);
        tasks[i].execution_copy = 0;
    }

    // Calculate CPU utilization
    cpu_utilization = 0;
    for (int i = 0; i < n; i++) {
        cpu_utilization += (float)tasks[i].execution / (float)tasks[i].deadline;
    }

    printf("CPU Utilization: %f\n", cpu_utilization);

    if (cpu_utilization < 1)
        printf("Tasks can be scheduled.\n");
    else
        printf("Schedule is not feasible.\n");

    while (1) {
        int active_task_id = min(tasks, n);

        if (active_task_id == -1) {
            printf("%d Idle\n", timer);
        } else {
            execute_task(tasks, active_task_id, timer);
            if (tasks[active_task_id].execution_copy == 0) {
                update_execution_copy(tasks, active_task_id);
            }
        }

        timer++;

        // Exit condition: All tasks have completed execution
        int all_completed = 1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].execution_copy > 0) {
                all_completed = 0;
                break;
            }
        }
        if (all_completed) {
            break;
        }
    }

    free(tasks);
    return 0;
}

int min(Task *tasks, int n) {
    int min_deadline = __INT_MAX__;
    int task_id = -1;

    for (int i = 0; i < n; i++) {
        if (tasks[i].execution_copy > 0 && tasks[i].deadline < min_deadline) {
            min_deadline = tasks[i].deadline;
            task_id = i;
        }
    }

    return task_id;
}

void update_execution_copy(Task *tasks, int n) {
    tasks[n].execution_copy = tasks[n].execution;
}

void execute_task(Task *tasks, int task_id, int timer) {
    tasks[task_id].execution_copy--;
    printf("%d Task %d\n", timer, task_id + 1);
}
