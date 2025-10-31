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
    int completed;
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

// Use the sjf process scheduling algorithm
// Print the processes as they are completed
void sjf(Process *procs, int n)
{
    // Keep track of the current time, starting from the time of arrival of the first process
    int time = procs[0].at;

    // Keep track of execution of processes using the gantt chart
    int gantt[100][2], gn = 0;

    printf("PID | AT | BT | CT | TAT | WT\n");
    printf("-----------------------------\n");

    for (int i = 0; i < n; i++)
    {
        // Loop through all the processes and find the
        // shortest , non completed, arrived process
        Process *shortest_proc = NULL;
        int shortest_bt = 9999;

        for (int j = 0; j < n; j++)
        {
            if (procs[j].at <= time && !procs[j].completed && procs[j].bt < shortest_bt)
            {
                // shortest_proc should be a pointer because otherwise changes
                // will not be made to the pracs inside array
                shortest_proc = &procs[j];
                shortest_bt = shortest_proc->bt;
            }
        }

        // Mark the found process as completed
        shortest_proc->completed = 1;

        // Time is passed till the burst time of the process
        time += shortest_proc->bt;

        // The unfilled values for each process can be filled out in one go
        shortest_proc->ct = time;
        shortest_proc->tat = shortest_proc->ct - shortest_proc->at;
        shortest_proc->wt = shortest_proc->tat - shortest_proc->bt;

        // Add the process to the gantt chart
        gantt[gn][0] = shortest_proc->pid;
        gantt[gn][1] = shortest_proc->ct;
        gn++;

        // Print out the processes immediately after they are executed
        printf("P%02d | %02d | %02d | %02d |  %02d | %02d\n", shortest_proc->pid, shortest_proc->at, shortest_proc->bt, shortest_proc->ct, shortest_proc->tat, shortest_proc->wt);
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
        {1, 2, 6, 0, 0, 0, 0},
        {2, 5, 2, 0, 0, 0, 0},
        {3, 1, 8, 0, 0, 0, 0},
        {4, 0, 3, 0, 0, 0, 0},
        {5, 4, 4, 0, 0, 0, 0},
    };

    sortProcesses(procs, n);
    sjf(procs, n);
}