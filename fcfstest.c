#include <stdio.h>
#include <stdlib.h>

struct Process
{
  int pid;
  int arrival_time;
  int burst_time;
};

void calculateWaitingTime(struct Process processes[],int n,int waiting_time[]) {
    waiting_time[0]=0;
    for (int i = 1; i < n; i++)
    {
      waiting_time[i] = waiting_time[i-1]+processes[i].burst_time;

      if (waiting_time<0)
      {
        waiting_time=0;
      }
      
    }
}

void calculateTurnAroundTime(struct Process processes[],int n, int turn_around_time[],int waiting_time[]){
  for (int i = 0; i < n; i++)
  {
    turn_around_time[i]= processes[i].burst_time+waiting_time[i];
  }
  
}


void calculateAverageTime(struct Process processes[],int n){
  int waiting_time[n],turn_around_time[n];
  double total_waiting_time=0,total_turn_around_time=0;

  calculateWaitingTime(processes,n,waiting_time);
  calculateTurnAroundTime(processes,n,turn_around_time,waiting_time);

  printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++){
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, waiting_time[i], turn_around_time[i]);
    total_waiting_time+=waiting_time[i];
    total_turn_around_time+=turn_around_time[i];
  }

  double average_waiting_time= total_waiting_time/n;
  double average_turn_around_time = total_turn_around_time/n;
  
  printf("\nAverage Waiting Time: %.2f", average_waiting_time);
  printf("\nAverage Turnaround Time: %.2f\n", average_turn_around_time);


}

int main(){
  int n;
  printf("Enter the number of processess:  ");
  scanf("%d",&n);

  struct Process processes[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    for (int i = 0; i < n-1; i++)
    {
      for (int j = 0; i < n-i-1; j++)
      {
        if (processes[j].arrival_time>processes[j+1].arrival_time){
          struct Process temp = processes[j];
          processes[j] = processes[j+1];
          processes[j+1] = temp;
        }
        
      }
      
    }
    calculateAverageTime(processes,n);
    return 0;

}
