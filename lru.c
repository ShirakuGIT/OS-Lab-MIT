#include <stdio.h>
#include <stdlib.h>

// Function for LRU Page Replacement
void lru(int pages[], int n, int frames[], int frame_size) {
    int page_faults = 0;
    int *time = (int*)malloc(frame_size * sizeof(int));  // Track last used time for each frame
    
    for (int i = 0; i < n; i++) {
        int found = 0, least_recent = 0;
        // Check if page is already in frames
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = i;  // Update time of usage
                break;
            }
        }
        if (!found) {
            // Find least recently used frame
            for (int j = 1; j < frame_size; j++) {
                if (time[j] < time[least_recent]) least_recent = j;
            }
            frames[least_recent] = pages[i];  // Replace the LRU page
            time[least_recent] = i;  // Update time
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
    printf("LRU Page Faults: %d\n", page_faults);
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

    // Perform LRU page replacement
    printf("\n--- LRU Page Replacement ---\n");
    lru(pages, n, frames, frame_size);

    free(pages);
    free(frames);
    return 0;
}
