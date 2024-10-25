#include <stdio.h>
#include <limits.h>

#define MAX 5  // Number of processes

typedef struct {
    int pid;    // Process ID
    int bt;     // Burst Time
    int at;     // Arrival Time
    int rem_bt; // Remaining Burst Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
} Process;

int main() {
    Process p[MAX] = {
        {1, 6, 2, 6, 0, 0},  // Process ID, Burst Time, Arrival Time, Remaining Burst Time
        {2, 8, 5, 8, 0, 0},
        {3, 7, 1, 7, 0, 0},
        {4, 3, 0, 3, 0, 0},
        {5, 4, 4, 4, 0, 0}
    };

    int total_time = 0;  // Total elapsed time
    int done = 0;  // Number of completed processes
    int smallest, min_rem_bt;

    // Find total burst time (for total time simulation)
    for (int i = 0; i < MAX; i++) {
        total_time += p[i].bt;
    }

    // Initialize the remaining time and time variables
    int time = 0;

    // SRTF Scheduling Logic
    while (done < MAX) {
        smallest = -1;
        min_rem_bt = INT_MAX;

        // Find the process with the shortest remaining time at current time
        for (int i = 0; i < MAX; i++) {
            if (p[i].at <= time && p[i].rem_bt > 0 && p[i].rem_bt < min_rem_bt) {
                min_rem_bt = p[i].rem_bt;
                smallest = i;
            }
        }

        if (smallest == -1) {
            time++;  // If no process is ready, move time forward
            continue;
        }

        // Process the selected process for one time unit
        time++;
        p[smallest].rem_bt--;

        // If the process is completed
        if (p[smallest].rem_bt == 0) {
            done++;
            p[smallest].tat = time - p[smallest].at;  // Turnaround time = Completion time - Arrival time
            p[smallest].wt = p[smallest].tat - p[smallest].bt;  // Waiting time = Turnaround time - Burst time
        }
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
    printf("PID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].at, p[i].wt, p[i].tat);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
