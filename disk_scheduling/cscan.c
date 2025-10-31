#include <stdio.h>

#define TOTAL_TRACKS 200

int calculateSeekTime(int *requests, int n)
{
    int total_seek_time = 0;
    int head_pos = 53;

    int completed = 0;

    // Infinitely loop until all requests are completed
    while (head_pos >= 0 && head_pos <= TOTAL_TRACKS - 1)
    {
        // For each position check if any of the requests are for that position
        // If so mark that request as completed
        for (int j = 0; j < n; j++)
        {
            if (requests[j] == head_pos)
            {
                requests[j] = -1;
                completed++;
            }
        }

        // If all requests are compelted then break from the loop
        if (completed == n)
        {
            break;
        }

        // If the head reaches the end then move head to beginning
        // and increment seek time as needed
        if (head_pos == TOTAL_TRACKS - 1)
        {
            head_pos = 0;
            total_seek_time += TOTAL_TRACKS - 1;
            printf("Head back to beginning\n");
        }
        // Otherwise simply move head_pos and increment total_seek_time
        else
        {
            total_seek_time++;
            head_pos++;
        }
    }

    return total_seek_time;
}

void main()
{
    int requests[] = {98, 183, 41, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);

    int total_seek_time = calculateSeekTime(requests, n);
    printf("Total Seek Time: %d", total_seek_time);
}