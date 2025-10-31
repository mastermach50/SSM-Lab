#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TRACKS 200

int calculateSeekTime(int *requests, int n)
{
    int total_seek_time = 0;
    int head_pos = 0;

    // Loop through all the requests and calculate seek time for each
    for (int  i = 0; i < n; i++)
    {
        total_seek_time += abs(requests[i] - head_pos);
        head_pos = requests[i];
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