#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int n;
int period[MAX], execution[MAX], deadline[MAX];
int ready[MAX], task[MAX];
int time = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (deadline[i] > deadline[j]) {
                swap(&period[i], &period[j]);
                swap(&execution[i], &execution[j]);
                swap(&deadline[i], &deadline[j]);
            }
        }
    }
}

void schedule() {
    int i, j;
    for (i = 0; i < n; i++) {
        if (time % period[i] == 0) {
            ready[i] = 1;
        }
    }
    for (i = 0; i < n; i++) {
        if (ready[i] == 1) {
            int min_deadline = 1000000000;
            int min_index = -1;
            for (j = 0; j < n; j++) {
                if (ready[j] == 1 && deadline[j] < min_deadline) {
                    min_deadline = deadline[j];
                    min_index = j;
                }
            }
            task[min_index] += execution[min_index];
            deadline[min_index] += period[min_index];
            ready[min_index] = 0;
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the period, execution time and deadline of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &period[i], &execution[i], &deadline[i]);
        ready[i] = task[i] = 0;
    }
    sort();
    printf("\nOrder of execution of processes in CPU timeline:\n");
    while (time < 100) { // assuming total time is 100
        schedule();
        printf("%d ", task[0]);
        time++;
    }
    return 0;
}
