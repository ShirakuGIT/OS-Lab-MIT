// Shortest Job First scheduling algorithm in C
// Author: Shivaram Kumar

# include <stdio.h>
# include <string.h>

int main(void)
{
    int process_count = 5;
    int arrival_times[5] = {0, 3, 4, 5, 6};
    int burst_times[5] = {2, 1, 4, 3, 5};
    int remaining_times[5] = {2, 1, 4, 3, 5};
    int current_time = 0;
    int process_queue[20] = {};
    int waiting_time[5] = {0};
    int turnaround_time[5] = {0};
    int completed = 0;
    int queue_size = 0;
    int p = 0;

    while (completed <= process_count - 1) {
        for (int i=0; i < process_count; i++){
            if (arrival_times[i] <= current_time && remaining_times[i] != 0) {
                process_queue[i] = i;
                queue_size++;
            }
        }

        if (queue_size > 1)
        {
            // sort the process queue based on shortest burst time / remaining time
            for (int a = 0; a < queue_size; a++) {
                for (int b = a + 1; b < queue_size; b++) {
                    if (remaining_times[process_queue[a]] > remaining_times[process_queue[b]]) 
                    {
                        int temp = process_queue[a];
                        process_queue[a] = process_queue[b];
                        process_queue[b] = temp;
                    }
                }
            }

            // Execute shortest job for 1 unit of time
            remaining_times[process_queue[0]]--;

            if (remaining_times[process_queue[0]] == 0) 
            {
                waiting_time[process_queue[0]] = current_time - arrival_times[process_queue[0]] - burst_times[process_queue[0]];
                turnaround_time[process_queue[0]] = waiting_time[process_queue[0]] + burst_times[process_queue[0]];
                queue_size--;
                completed++;
                process_queue[0] = -1;
            }

        }

        current_time++;
    }
}

