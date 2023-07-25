#include <stdio.h>
#include <stdbool.h>

// Define the Job struct to hold job details
struct Job {
    int job_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

// Function to implement the Round Robin algorithm
void round_robin_scheduler(struct Job jobs[], int n, int time_quantum) {
    int current_time = 0;
    int total_waiting_time = 0;
    int total_completion_time = 0;

    // Initialize remaining time for all jobs to their burst time
    for (int i = 0; i < n; i++) {
        jobs[i].remaining_time = jobs[i].burst_time;
    }

    printf("Round Robin Scheduling Order:\n");
    printf("Job ID\tArrival Time\tBurst Time\tWaiting Time\tCompletion Time\n");

    bool all_jobs_completed = false;

    while (!all_jobs_completed) {
        all_jobs_completed = true;

        for (int i = 0; i < n; i++) {
            if (jobs[i].remaining_time > 0) {
                all_jobs_completed = false;

                // Execute the job for the time quantum or the remaining burst time, whichever is smaller
                int execution_time = (jobs[i].remaining_time < time_quantum) ? jobs[i].remaining_time : time_quantum;

                // Update the remaining time for the job
                jobs[i].remaining_time -= execution_time;

                // Update the current time
                current_time += execution_time;

                // Check if the job is completed
                if (jobs[i].remaining_time == 0) {
                    // Calculate waiting time and completion time of the completed job
                    int waiting_time = current_time - jobs[i].arrival_time - jobs[i].burst_time;
                    total_waiting_time += waiting_time;
                    total_completion_time += current_time;

                    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", jobs[i].job_id, jobs[i].arrival_time, jobs[i].burst_time,
                           waiting_time, current_time);
                }
            }
        }
    }

    // Calculate and print average waiting time and average completion time
    float average_waiting_time = (float)total_waiting_time / n;
    float average_completion_time = (float)total_completion_time / n;
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Completion Time: %.2f\n", average_completion_time);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Define job details (collected from the user)
    struct Job jobs[n];

    // Collect details for each job from the user
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for Job %d: ", i + 1);
        scanf("%d", &jobs[i].arrival_time);

        printf("Enter burst time for Job %d: ", i + 1);
        scanf("%d", &jobs[i].burst_time);

        jobs[i].job_id = i + 1;
    }

    // Call the Round Robin scheduler
    round_robin_scheduler(jobs, n, time_quantum);

    return 0;
}
