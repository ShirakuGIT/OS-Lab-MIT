#include <stdio.h>

int main() {
    int n, m;  // n = number of processes, m = number of resource types
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    int max[n][m], alloc[n][m], need[n][m], avail[m], safe[n], finish[n];

    // Input max resources required by each process
    printf("Enter max resources for each process:\n");
    for (int i = 0; i < n; i++) {
        finish[i] = 0;  // Initially, no process is finished
        for (int j = 0; j < m; j++) scanf("%d", &max[i][j]);
    }

    // Input allocated resources for each process
    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];  // Calculate need
        }
    }

    // Input available resources
    printf("Enter available resources: ");
    for (int i = 0; i < m; i++) scanf("%d", &avail[i]);

    // Check for safe sequence
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j]) break;  // If need exceeds available, break
                if (j == m) {  // All resources can be allocated to this process
                    for (int k = 0; k < m; k++) avail[k] += alloc[i][k];  // Free resources
                    safe[count++] = i;  // Add process to safe sequence
                    finish[i] = 1;  // Mark process as finished
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state!\n");
            return 0;
        }
    }

    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) printf("P%d ", safe[i]);
    printf("\n");

    return 0;
}
