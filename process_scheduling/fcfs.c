#include <stdio.h>

// Define a struct for the process
typedef struct
{
    int pid;
    int at;
    int bt;
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

// Use the fcfs process scheduling algorithm
// Print the processes as they are completed
void fcfs(Process *procs, int n)
{
    // Keep track of the current time, starting from the time of arrival of the first process
    int time = procs[0].at;

    // Keep track of execution of processes using the gantt chart
    int gantt[100][2], gn = 0;

    printf("PID | AT | BT | CT | TAT | WT\n");
    printf("-----------------------------\n");

    for (int i = 0; i < n; i++)
    {
        // Time passed until the bt of the each process
        // (remember that we have sorted the processes by their arrival time)
        time += procs[i].bt;

        // The unfilled values for each process can be filled out in one go
        procs[i].ct = time;
        procs[i].tat = procs[i].ct - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;

        // Add the process to the gantt chart
        gantt[gn][0] = procs[i].pid;
        gantt[gn][1] = procs[i].ct;
        gn++;

        // Print out the processes immediately after they are executed
        printf("P%02d | %02d | %02d | %02d |  %02d | %02d\n", procs[i].pid, procs[i].at, procs[i].bt, procs[i].ct, procs[i].tat, procs[i].wt);

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
        {1, 2, 6},
        {2, 5, 2},
        {3, 1, 8},
        {4, 0, 3},
        {5, 4, 4},
    };

    sortProcesses(procs, n);
    fcfs(procs, n);
}