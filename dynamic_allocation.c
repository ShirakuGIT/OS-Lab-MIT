#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10  // Maximum number of memory blocks

// Structure for Memory Block
typedef struct {
    int size;
    int allocated;  // 0 means free, 1 means allocated
} Block;

// Function for First Fit allocation
void first_fit(Block* blocks, int n, int request_size) {
    for (int i = 0; i < n; i++) {
        if (!blocks[i].allocated && blocks[i].size >= request_size) {
            blocks[i].allocated = 1;  // Allocate the block
            printf("First Fit: Block %d allocated with size %d\n", i, blocks[i].size);
            return;
        }
    }
    printf("First Fit: No suitable block found!\n");
}

// Function for Best Fit allocation
void best_fit(Block* blocks, int n, int req_size)
{
    int least_size_index = -1;
    int least_size_block = __INT_MAX__;

    for (int i=0; i<n; i++)
    {
        if (blocks[i].allocated == 0 && req_size <= blocks[i].size && blocks[i].size < least_size_block)
        {
            least_size_block = blocks[i].size;
            least_size_index = i;
        }
    }

    if (least_size_index == -1)
    {
        printf("No suitable block found.\n");
    }
    else
    {
        printf("Suitable size found at block %d with size %d.\n", least_size_index, least_size_block);
    }
}

int main() {
    int n, request_size;
    
    // Dynamically allocate memory for blocks array
    Block* blocks = (Block*)malloc(MAX_BLOCKS * sizeof(Block));

    // Input number of blocks and their sizes
    printf("Enter number of blocks: ");
    scanf("%d", &n);

    printf("Enter block sizes:\n");
    for (int i = 0; i < n; i++) {
        printf("Block %d size: ", i);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = 0;  // Initially, all blocks are free
    }

    // Input memory request
    printf("Enter request size: ");
    scanf("%d", &request_size);

    // Perform First Fit allocation
    first_fit(blocks, n, request_size);

    // Perform Best Fit allocation
    best_fit(blocks, n, request_size);

    // Free dynamically allocated memory
    free(blocks);

    return 0;
}
