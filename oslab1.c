#include <stdio.h>

struct Process {
    int id, arrival_time, burst_time, completion_time, turnaround_time, waiting_time, response_time;
};

void calculateTimes(struct Process p[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    int total_turnaround_time = 0, total_waiting_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) current_time = p[i].arrival_time;
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = current_time - p[i].arrival_time;
        current_time += p[i].burst_time;

        // Accumulate turnaround and waiting times
        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    // Calculate averages
    *avg_turnaround_time = (float)total_turnaround_time / n;
    *avg_waiting_time = (float)total_waiting_time / n;
}

void displayResults(struct Process p[], int n, float avg_turnaround_time, float avg_waiting_time) {
    printf("\nProcess ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Response Time\n");
    for (int i = 0; i < n; i++) {
        printf("    %d      |     %d       |     %d     |       %d        |       %d        |      %d      |      %d\n",
            p[i].id,
            p[i].arrival_time,
            p[i].burst_time,
            p[i].completion_time,
            p[i].turnaround_time,
            p[i].waiting_time,
            p[i].response_time);
    }
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    // Variables to store the averages
    float avg_turnaround_time, avg_waiting_time;

    calculateTimes(p, n, &avg_turnaround_time, &avg_waiting_time);
    displayResults(p, n, avg_turnaround_time, avg_waiting_time);

    return 0;
}
