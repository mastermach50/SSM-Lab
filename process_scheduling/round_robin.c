#include <stdio.h>
#include <stdlib.h>

#define TIME_QUANT 2

// Define a struct for the process
typedef struct
{
    int pid;
    int at;
    int bt;
    int rem_bt;
    int ct;
    int tat;
    int wt;
} Process;

// Sort the processes based on arrival time (using bubble sort)
void sortProcesses(Process *procs, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (procs[j].at > procs[j + 1].at)
            {
                Process temp = procs[j];
                procs[j] = procs[j + 1];
                procs[j + 1] = temp;
            }
        }
    }
}

// A function to print the gantt chart (optional)
void printGanttChart(int gantt[100][2], int gn)
{
    // Print the pids first
    printf("\n\n|");
    for (int i = 0; i < gn; i++)
    {
        printf("  P%02d  |", gantt[i][0]);
    }
    printf("\n");

    // Print the timings in the next line
    printf("00");
    for (int i = 0; i < gn; i++)
    {
        printf("      %02d", gantt[i][1]);
    }
    printf("\n");
}

// Use the round_robin process scheduling algorithm
// Print the processes as they are completed
void round_robin(Process *procs, int n)
{
    // Keep track of the current time, starting from the time of arrival of the first process
    int time = procs[0].at;

    Process rq[1000];
    int front = 0, rear = 0;
    rq[rear] = procs[0];

    int completed = 0;

    // Keep track of execution of processes using the gantt chart
    int gantt[100][2], gn = 0;

    printf("PID | AT | BT | CT | TAT | WT\n");
    printf("-----------------------------\n");

    while (1)
    {

        int prev_time = time;

        Process exec = rq[front++];

        if (exec.rem_bt > TIME_QUANT)
        {
            time += TIME_QUANT;

            gantt[gn][0] = exec.pid;
            gantt[gn][1] = time;
            gn++;

            exec.rem_bt -= TIME_QUANT;
        }
        else
        {
            time += exec.rem_bt;

            gantt[gn][0] = exec.pid;
            gantt[gn][1] = time;
            gn++;

            exec.rem_bt = 0;

            completed++;

            // Print out the processes immediately after they are executed
            exec.ct = time;
            exec.tat = exec.ct - exec.at;
            exec.wt = exec.tat - exec.bt;
            printf("P%02d | %02d | %02d | %02d |  %02d | %02d\n", exec.pid, exec.at, exec.bt, exec.ct, exec.tat, exec.wt);
        }

        for (int i = 0; i < n; i++)
        {
            if (procs[i].at > prev_time && procs[i].at <= time && procs[i].rem_bt > 0)
            {
                rq[++rear] = procs[i];
            }
        }

        if (exec.rem_bt > 0)
        {
            rq[++rear] = exec;
        }

        if (completed == n)
        {
            break;
        }
    }

    // Call the function to print the gantt chart
    printGanttChart(gantt, gn);
}

void main()
{
    // The number of processes
    int n = 5;

    // Fill out the array of processes with the pid, at and bt of each process
    Process procs[] = {
        {1, 2, 6, 6, 0, 0, 0},
        {2, 5, 2, 2, 0, 0, 0},
        {3, 1, 8, 8, 0, 0, 0},
        {4, 0, 3, 3, 0, 0, 0},
        {5, 4, 4, 4, 0, 0, 0},
    };

    sortProcesses(procs, n);
    round_robin(procs, n);
}