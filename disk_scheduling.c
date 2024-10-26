#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    int total = 0, visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;  // Initialize visited array
    printf("SCAN Order: ");
    
    // Move left from head to 0, servicing requests
    for (int d = head; d <= max; d++) {
        for (int i = 0; i < n; i++) {
            if (req[i] == d && !visited[i]) {
                printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; visited[i] = 1;
            }}}

    printf("%d ", max);
    if (head!=max) {total += abs(head-max); head = max;}
    

    for (int d = max; d >= 0; d--) {
        for (int i = 0; i < n; i++) {
            if (req[i] == d && !visited[i]) {
                printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; visited[i] = 1;
            }}}

    printf("\nTotal Seek Time: %d\n", total);
}


void cscan(int req[], int n, int head, int max) {
    int total = 0, visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;  // Initialize visited array
    printf("C-SCAN Order: ");

    // Move right from head to max, servicing requests
    for (int d = head; d <= max; d++) {
        for (int i = 0; i < n; i++) {
            if (req[i] == d && !visited[i]) {
                printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; visited[i] = 1;
            }}}

    // Jump to 0 and continue servicing requests
    printf("0 ");
    total += abs(max - head); 
    total += max;
    head = 0;

    // Move from 0 to max, servicing remaining requests
    for (int d = 0; d <= max; d++) {
        for (int i = 0; i < n; i++) {
            if (req[i] == d && !visited[i]) {
                printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; visited[i] = 1;
            }}}

    printf("\nTotal Seek Time: %d\n", total);
}


void clook(int req[], int n, int head) {
    int total = 0, visited[n], min = __INT_MAX__, max = -1;
    for (int i = 0; i < n; i++) visited[i] = 0;  // Initialize visited array
    for (int i = 0; i < n; i++) { if (req[i] > max) max = req[i]; if (req[i] < min) min = req[i]; }
    printf("C-LOOK Order: ");

    // Move right from head to max, servicing requests
    for (int d = head; d <= max; d++) {
        for (int i = 0; i < n; i++) {
            if (req[i] == d && !visited[i]) {
                printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; visited[i] = 1;
            }}}

    // Jump to min and continue servicing requests
    for (int d = min; d < head; d++) {
        for (int i = 0; i < n; i++) {
            if (req[i] == d && !visited[i]) {
                printf("%d ", req[i]); total += abs(head - req[i]); head = req[i]; visited[i] = 1;
            }}}

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
