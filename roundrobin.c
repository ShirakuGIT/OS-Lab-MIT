#include <stdio.h>

#define MAX 5   // Number of processes
#define TIME_QUANTUM 3   // Time Quantum

typedef struct {
    int pid;    // Process ID
    int bt;     // Burst Time
    int rem_bt; // Remaining Burst Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
} Process;

int main() {
    Process p[MAX] = {
        {1, 10, 10, 0, 0},
        {2, 5, 5, 0, 0},
        {3, 8, 8, 0, 0},
        {4, 4, 4, 0, 0},
        {5, 6, 6, 0, 0}
    };

    int time = 0;  // Current time
    int total_wt = 0, total_tat = 0;
    int done = 0;  // Number of completed processes

    // Round Robin Scheduling Logic
    while (done < MAX) {
        for (int i = 0; i < MAX; i++) {
            if (p[i].rem_bt > 0) {
                if (p[i].rem_bt > TIME_QUANTUM) {
                    time += TIME_QUANTUM;
                    p[i].rem_bt -= TIME_QUANTUM;
                } else {
                    time += p[i].rem_bt;
                    p[i].rem_bt = 0;
                    p[i].tat = time;  // Completion time = turnaround time for RR
                    p[i].wt = p[i].tat - p[i].bt;  // Waiting time = TAT - Burst time
                    done++;
                }
            }
        }
    }

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < MAX; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Calculate average waiting time and turnaround time
    float avg_wt = (float) total_wt / MAX;
    float avg_tat = (float) total_tat / MAX;

    // Print results
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
