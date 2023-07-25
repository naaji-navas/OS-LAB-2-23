#include <stdio.h>
#include <stdbool.h>

// Define the Job struct to hold job details
struct Job {
    int job_id;
    int arrival_time;
    int burst_time;
};

// Function to implement the SJF algorithm
void sjf_scheduler(struct Job jobs[], int n) {
    int completion_time = 0;
    int total_waiting_time = 0;

    // Sort jobs based on burst time (shortest to longest)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[j].burst_time > jobs[j + 1].burst_time) {
                // Swap the jobs
                struct Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }

    printf("SJF Scheduling Order:\n");
    printf("Job ID\tArrival Time\tBurst Time\tWaiting Time\tCompletion Time\n");

    for (int i = 0; i < n; i++) {
        // Execute the job for its burst time
        completion_time += jobs[i].burst_time;

        // Calculate waiting time of the completed job
        int waiting_time = completion_time - jobs[i].arrival_time - jobs[i].burst_time;
        total_waiting_time += waiting_time;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", jobs[i].job_id, jobs[i].arrival_time, jobs[i].burst_time,
               waiting_time, completion_time);
    }

    // Calculate and print average waiting time
    float average_waiting_time = (float)total_waiting_time / n;
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
}

int main() {
    int n;

    printf("Enter the number of jobs: ");
    scanf("%d", &n);

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

    // Call the SJF scheduler
    sjf_scheduler(jobs, n);

    return 0;
}
