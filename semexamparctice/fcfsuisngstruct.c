#include<stdio.h>

//Structure to represent  a process

struct Process
{
  int process_id;
  int arrival_time;
  int burst_time;
  int completion_time;
  int turn_aroun_time;
  int waiting_time;
};

int calculateTimes(struct Process processes[],int n){
  int total_waiting_time = processes[0].arrival_time;
  processes[0].completion_time=processes[0].arrival_time+processes[0].burst_time;
  processes[0].turn_aroun_time = processes[0].completion_time - processes[0].arrival_time;
  processes[0].waiting_time = processes[0].turn_aroun_time - processes[0].burst_time;

  int total_turn_around_time=processes[0].turn_aroun_time;
  for (int  i = 1; i < n; i++)
  {
  int tempp=0;
    if(processes[i-1].completion_time<processes[i].arrival_time){
      int tempp = processes[i].arrival_time - processes[i-1].completion_time;
    }
    processes[i].completion_time=processes[i-1].completion_time+processes[i].burst_time + tempp;
    processes[i].turn_aroun_time=processes[i].completion_time-processes[i].arrival_time ;
    processes[i].waiting_time = processes[i].turn_aroun_time - processes[i].burst_time ;
    total_waiting_time+=processes[i].waiting_time;
    total_turn_around_time+=processes[i].turn_aroun_time;

  }
      float avg_waiting_time = (float)total_waiting_time / n;
      float avg_trun_around_time = (float)total_turn_around_time / n;
          printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id+1, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_aroun_time, processes[i].waiting_time);
    }
        printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
        printf("\nAverage Turn Around Time: %.2f\n", avg_trun_around_time);


  
}



int main(){
  int n;
  printf("Enter the number of processes : " );
  scanf("%d",&n);
  struct Process processes[n];

  //Input the process details
  for (int i = 0; i < n; i++)
  {
    processes[i].process_id+=i;
    printf("Enter Arrival Time for Process %d: ", i + 1);
    scanf("%d", &processes[i].arrival_time);
    printf("Enter Burst Time for Process %d: ", i + 1);
    scanf("%d", &processes[i].burst_time);

  }

  // sorting the process according the the arrival time

  for(int i =0; i<n-1 ; i++){
      for (int  j = 0; j < n-i-1; j++)
      {
        if(processes[j].arrival_time> processes[j+1].arrival_time){
          // swap the process 
          struct Process temp = processes[j];
          processes[j]=processes[j+1];
          processes[j+1]=temp;
        }
      }
      
  }
  calculateTimes(processes,n);
  
  

}
