#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void fcfs(int requests[], int n, int start) {
    int totalSeek = 0, current = start;

    printf("FCFS Disk Scheduling:\n");

    for (int i = 0; i < n; i++) {
        totalSeek += abs(current - requests[i]);
        printf("Move from %d to %d\n", current, requests[i]);
        current = requests[i];
    }

    printf("Total Seek Distance: %d\n", totalSeek);
}

void scan(int requests[], int n, int start, int maxCylinder) {
    int totalSeek = 0, current = start;

    printf("SCAN Disk Scheduling:\n");

    int direction = 1; // 1 for right, -1 for left
    int maxIndex = (direction == 1) ? maxCylinder : 0;

    for (int i = 0; i < n; i++) {
        totalSeek += abs(current - requests[i]);
        printf("Move from %d to %d\n", current, requests[i]);
        current = requests[i];
    }

    totalSeek += abs(current - maxIndex);
    printf("Move from %d to %d\n", current, maxIndex);

    for (int i = n - 1; i >= 0; i--) {
        totalSeek += abs(maxIndex - requests[i]);
        printf("Move from %d to %d\n", maxIndex, requests[i]);
        maxIndex = requests[i];
    }

    printf("Total Seek Distance: %d\n", totalSeek);
}

void cScan(int requests[], int n, int start, int maxCylinder) {
    int totalSeek = 0, current = start;

    printf("C-SCAN Disk Scheduling:\n");

    int maxIndex = maxCylinder;

    for (int i = 0; i < n; i++) {
        totalSeek += abs(current - requests[i]);
        printf("Move from %d to %d\n", current, requests[i]);
        current = requests[i];
    }

    totalSeek += abs(current - maxIndex);
    printf("Move from %d to %d\n", current, maxIndex);

    current = 0;
    for (int i = 0; i < n; i++) {
        totalSeek += abs(current - requests[i]);
        printf("Move from %d to %d\n", current, requests[i]);
        current = requests[i];
    }

    printf("Total Seek Distance: %d\n", totalSeek);
}

int main() {
    int requests[MAX_REQUESTS], n, start, maxCylinder;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    if (n > MAX_REQUESTS) {
        printf("Maximum number of requests exceeded.\n");
        return 1;
    }

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the starting position: ");
    scanf("%d", &start);

    printf("Enter the maximum cylinder value: ");
    scanf("%d", &maxCylinder);

    fcfs(requests, n, start);
    scan(requests, n, start, maxCylinder);
    cScan(requests, n, start, maxCylinder);

    return 0;
}
