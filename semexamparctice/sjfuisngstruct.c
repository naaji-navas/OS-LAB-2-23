#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Function to calculate turnaround time and waiting time for each process
void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int current_time = 0; // Initialize current time to 0

    for (int i = 0; i < n; i++) {
        // Find the next process with the shortest burst time that has arrived
        int shortest_job = -1;
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].burst_time > 0) {
                if (shortest_job == -1 || processes[j].burst_time < processes[shortest_job].burst_time) {
                    shortest_job = j;
                }
            }
        }

        // If no process is found, increment the current time
        if (shortest_job == -1) {
            current_time++;
        } else {
            // Execute the shortest job
            int index = shortest_job;
            current_time += processes[index].burst_time;

            // Update completion time, turnaround time, and waiting time
            processes[index].completion_time = current_time;
            processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
            total_waiting_time += processes[index].waiting_time;

            // Set burst time to 0 to mark the process as completed
            processes[index].burst_time = 0;
        }
    }

    // Calculate average waiting time
    float avg_waiting_time = (float)total_waiting_time / n;

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details including arrival times
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    calculateTimes(processes, n);

    return 0;
}
India is my country.
...........................................................