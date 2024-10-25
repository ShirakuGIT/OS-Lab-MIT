# include <stdio.h>

int main(void) 
{
    int n=5;
    int m=3;
    int alloc[5][3] = {{0, 1, 0},  // P0
                       {2, 0, 0},  // P1
                       {3, 0, 2},  // P2
                       {2, 1, 1},  // P3
                       {0, 0, 2}}; // P4

    // Maximum Matrix
    int max[5][3] = {{7, 5, 3},  // P0
                     {3, 2, 2},  // P1
                     {9, 0, 2},  // P2
                     {2, 2, 2},  // P3
                     {4, 3, 3}}; // P4
    int finish[n];
    int need[n][m];
    int avail[3] = {3, 3, 2};
    int index = 0;
    int answer[n];
    int completed = 0;

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            need[i][j] = max[i][j]-alloc[i][j];
        }
    }
    while (completed != n)
    {
        int process_completed = 0;
        for (int i=0; i<n; i++)
        {
            
            if (finish[i]==0)
            {
                int flag = 0;

                for (int j=0; j<m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    answer[index++] = i;
                    finish[i] = 1;
                    completed++;

                    for (int y=0; y<m; y++)
                    {
                        avail[y] += alloc[i][y];
                    }

                    process_completed = 1;
                }

            }
        }

        if (process_completed == 0)
        {
            printf("Not safe\n");
            return 0;
        }
    }

    printf("Following is the SAFE Sequence:\n");
    for (int i = 0; i < n - 1; i++)
        printf(" P%d ->", answer[i]);
    printf(" P%d\n", answer[n - 1]);

    return 0;
}