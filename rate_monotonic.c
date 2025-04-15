#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10

typedef struct {
    int processID;
    int burstTime;
    int period;
    int remainingTime;
    int nextArrivalTime;
} Process;

void sortByPeriod(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].period > processes[j].period) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void rateMonotonicScheduling(Process processes[], int n, int totalTime) {
    int currentTime = 0;

    sortByPeriod(processes, n);  // Sort by priority (shortest period = highest priority)

    // Initialize arrival and remaining time
    for (int i = 0; i < n; i++) {
        processes[i].nextArrivalTime = 0;
        processes[i].remainingTime = 0;
    }

    printf("\nRate Monotonic Scheduling (RMS):\n");

    int lastProcessID = -1;
    int startTime = 0;

    while (currentTime < totalTime) {
        // Release jobs at their period
        for (int i = 0; i < n; i++) {
            if (currentTime == processes[i].nextArrivalTime) {
                processes[i].remainingTime = processes[i].burstTime;
                processes[i].nextArrivalTime += processes[i].period;
            }
        }

        int selected = -1;

        // Select the highest priority ready process
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                selected = i;
                break;
            }
        }

        // Start of a new process or preemption
        if (selected != -1 && processes[selected].processID != lastProcessID) {
            if (lastProcessID != -1) {
                printf("Process %d executed from %d to %d\n", lastProcessID, startTime, currentTime);
            }
            lastProcessID = processes[selected].processID;
            startTime = currentTime;
        }

        if (selected != -1) {
            processes[selected].remainingTime--;
        } else {
            // CPU idle (if no process is ready)
            if (lastProcessID != -1) {
                printf("Process %d executed from %d to %d\n", lastProcessID, startTime, currentTime);
                lastProcessID = -1;
            }
        }

        currentTime++;
    }

    // If any process was running at the end, log its final execution
    if (lastProcessID != -1) {
        printf("Process %d executed from %d to %d\n", lastProcessID, startTime, currentTime);
    }
}
