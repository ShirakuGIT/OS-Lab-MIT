#include <stdio.h>
#include <stdlib.h>

// Function for FIFO Page Replacement
void fifo(int pages[], int n, int frames[], int frame_size) {
    int page_faults = 0, index = 0;
    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if page is already in frames
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[index] = pages[i];  // Replace page in FIFO order
            index = (index + 1) % frame_size;
            page_faults++;
        }
        // Print current frame state
        printf("Frame: ");
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == -1) printf(" - ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("FIFO Page Faults: %d\n", page_faults);
}

// Function for Optimal Page Replacement
void optimal(int pages[], int n, int frames[], int frame_size) {
    int page_faults = 0;
    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if page is already in frames
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int farthest = -1, index = -1;
            for (int j = 0; j < frame_size; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) break;
                }
                if (k > farthest) {
                    farthest = k;
                    index = j;
                }
            }
            frames[index] = pages[i];  // Replace page optimally
            page_faults++;
        }
        // Print current frame state
        printf("Frame: ");
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == -1) printf(" - ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Optimal Page Faults: %d\n", page_faults);
}

int main() {
    int n, frame_size;
    
    // Input the number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int *pages = (int*)malloc(n * sizeof(int));

    // Input page reference string
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    // Input the frame size
    printf("Enter frame size: ");
    scanf("%d", &frame_size);
    int *frames = (int*)malloc(frame_size * sizeof(int));
    
    // Initialize frames with -1 (empty)
    for (int i = 0; i < frame_size; i++) frames[i] = -1;
    
    // Perform FIFO page replacement
    printf("\n--- FIFO Page Replacement ---\n");
    fifo(pages, n, frames, frame_size);

    // Re-initialize frames for optimal algorithm
    for (int i = 0; i < frame_size; i++) frames[i] = -1;

    // Perform Optimal page replacement
    printf("\n--- Optimal Page Replacement ---\n");
    optimal(pages, n, frames, frame_size);

    free(pages);
    free(frames);
    return 0;
}
