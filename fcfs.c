#include <stdio.h>


struct Process
{
    int process_id;
    int arrival_time;
    int burst_time;
};

void calculateWaitingTime(struct Process processes[],int n,int waitingTime[]){
    waitingTime[0]=0;
    for(int i=1;i<n;i++){
        waitingTime[i]=processes[i-1].burst_time+waitingTime[i-1];
    }
}

void calculateTurnAroundTime(struct Process processes[],int n,int waitingTime[],int turnAroundTime[]){
    for(int i=0;i<n;i++){
        turnAroundTime[i]=processes[i].burst_time+waitingTime[i];
    }
}

void calculateAverageTimes(struct Process processes[], int n){
    int waitingTime[n],turnAroundTime[n]; // waiting time and turn around time for each process
    int totalWaitingTime=0,totalTurnAroundTime=0; // total waiting time and total turn around time
    
    calculateWaitingTime(processes,n,waitingTime);
    calculateTurnAroundTime(processes,n,waitingTime,turnAroundTime);

    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurn Around Time\n");

    for(int i = 0; i<n ; i++){
        totalWaitingTime+=waitingTime[i];
        totalTurnAroundTime+=turnAroundTime[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].process_id,processes[i].arrival_time,processes[i].burst_time,waitingTime[i],turnAroundTime[i]);
    }


    double averageWaitingTime=(double)totalWaitingTime/(double)n;
    double averageTurnAroundTime=(double)totalTurnAroundTime/(double)n;

    printf("Average Waiting Time: %lf\n",averageWaitingTime); 
    printf("Average Turn Around Time: %lf\n",averageTurnAroundTime);

}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct Process processes[n];
    for(int i=0;i<n;i++){
        printf("Enter the arrival time and burst time of process %d: ",i+1);
        scanf("%d %d",&processes[i].arrival_time,&processes[i].burst_time);
        processes[i].process_id=i+1;
    }
    calculateAverageTimes(processes,n);
    return 0;
}