#include <stdio.h>
#include <stdlib.h>

void sstf(int req[], int n, int head) {
    int total = 0, visited[n], min, diff, idx;
    for (int i = 0; i < n; i++) visited[i] = 0;
    printf("SSTF Order: ");
    for (int i = 0; i < n; i++) {
        min = __INT_MAX__;
        for (int j = 0; j < n; j++) {
            diff = abs(req[j] - head);
            if (!visited[j] && diff < min) { min = diff; idx = j; }
        }
        visited[idx] = 1; total += min; head = req[idx];
        printf("%d ", head);
    }
    printf("\nTotal Seek Time: %d\n", total);
}

void scan(int req[], int n, int head, int max) {
    int total = 0;
    printf("SCAN Order: ");
    for (int d = head; d >= 0; d--) {
        for (int i = 0; i < n; i++)
            if (req[i] == d) { printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; }
    }
    total += head; head = 0;
    for (int d = 1; d <= max; d++) {
        for (int i = 0; i < n; i++)
            if (req[i] == d) { printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; }
    }
    printf("\nTotal Seek Time: %d\n", total);
}

void cscan(int req[], int n, int head, int max) {
    int total = 0;
    printf("C-SCAN Order: ");
    for (int d = head; d <= max; d++) {
        for (int i = 0; i < n; i++)
            if (req[i] == d) { printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; }
    }
    total += abs(max - head) + max; head = 0;
    for (int d = 0; d <= max; d++) {
        for (int i = 0; i < n; i++)
            if (req[i] == d) { printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; }
    }
    printf("\nTotal Seek Time: %d\n", total);
}

void clook(int req[], int n, int head) {
    int total = 0, min = __INT_MAX__, max = -1;
    printf("C-LOOK Order: ");
    for (int i = 0; i < n; i++) { if (req[i] > max) max = req[i]; if (req[i] < min) min = req[i]; }
    for (int d = head; d <= max; d++) {
        for (int i = 0; i < n; i++)
            if (req[i] == d) { printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; }
    }
    for (int d = min; d < head; d++) {
        for (int i = 0; i < n; i++)
            if (req[i] == d) { printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; }
    }
    printf("\nTotal Seek Time: %d\n", total);
}

int main() {
    int n, head, max, choice;
    printf("Enter number of requests: "); scanf("%d", &n);
    int req[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: "); scanf("%d", &head);
    printf("Enter maximum disk size: "); scanf("%d", &max);

    while (1) {
        printf("\n1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\nChoose: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: sstf(req, n, head); break;
            case 2: scan(req, n, head, max); break;
            case 3: cscan(req, n, head, max); break;
            case 4: clook(req, n, head); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
