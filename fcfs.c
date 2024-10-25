#include <stdio.h>

#define MAX 5  // Number of processes

typedef struct {
    int pid;    // Process ID
    int bt;     // Burst Time
    int at;     // Arrival Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
} Process;

int main() {
    Process p[MAX] = {
        {1, 6, 2, 0, 0},  // Process ID, Burst Time, Arrival Time, Waiting Time, Turnaround Time
        {2, 8, 5, 0, 0},
        {3, 7, 1, 0, 0},
        {4, 3, 0, 0, 0},
        {5, 4, 4, 0, 0}
    };

    // Sort processes based on their arrival time (FCFS principle)
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = i + 1; j < MAX; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time for each process
    int total_wt = 0, total_tat = 0;
    int current_time = 0;

    for (int i = 0; i < MAX; i++) {
        // If the process arrives after the current time, wait for the process to arrive
        if (p[i].at > current_time) {
            current_time = p[i].at;
        }

        // Waiting time = time when the process starts - its arrival time
        p[i].wt = current_time - p[i].at;

        // Turnaround time = Waiting time + Burst time
        p[i].tat = p[i].wt + p[i].bt;

        // Update current time (the process finishes after its burst time)
        current_time += p[i].bt;

        // Accumulate total waiting time and turnaround time
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Calculate average waiting time and turnaround time
    float avg_wt = (float)total_wt / MAX;
    float avg_tat = (float)total_tat / MAX;

    // Print results
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
