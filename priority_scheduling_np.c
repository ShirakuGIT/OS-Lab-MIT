#include <stdio.h>

#define MAX 5  // Number of processes

typedef struct {
    int pid;    // Process ID
    int bt;     // Burst Time
    int priority;  // Priority (lower value means higher priority)
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
} Process;

int main() {
    Process p[MAX] = {
        {1, 10, 3, 0, 0},
        {2, 1, 1, 0, 0},
        {3, 2, 4, 0, 0},
        {4, 1, 5, 0, 0},
        {5, 5, 2, 0, 0}
    };

    // Sort processes based on priority (lower number means higher priority)
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = i + 1; j < MAX; j++) {
            if (p[i].priority > p[j].priority) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate waiting time
    p[0].wt = 0;  // First process has no waiting time
    for (int i = 1; i < MAX; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    // Calculate turnaround time
    for (int i = 0; i < MAX; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }

    // Calculate total waiting time and total turnaround time
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < MAX; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Calculate average waiting time and turnaround time
    float avg_wt = (float) total_wt / MAX;
    float avg_tat = (float) total_tat / MAX;

    // Print results
    printf("PID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
