#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void main(){
    int ArrT[20],BurstT[20];
    int WaitT[20],TurnT[20];
    float AvgWaitT=0,AvgTurnT=0;
    int p;
    int pid[20];
    int fid[20];

    WaitT[0]=0; //Waiting time of initial process is 0

    printf("Enter number of processes required: ");
    scanf("%d",&p);
    
    printf("Enter Burst and Arrival Time of %d processes:\n   Burst Time\tArrival time\n",p);
    
    for(int i=0;i<p;i++){
        printf("%d: " ,i+1);
        scanf("%d%d",&BurstT[i],&ArrT[i]);
        pid[i]=i+1;
    }

    for(int i=0;i<p;i++){
        for(int j=0;j<p-i-1;j++){
            if(ArrT[j]>ArrT[j+1]){
                int temp=ArrT[j];
                ArrT[j]=ArrT[j+1];
                ArrT[j+1]=temp;
                temp=pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;
                temp=BurstT[j];
                BurstT[j]=BurstT[j+1];
                BurstT[j+1]=temp;
            }
        }
    }


    //Calculating Waiting Time
    for(int i=1;i<p;i++){
        WaitT[i]=WaitT[i-1]+BurstT[i-1];
    }
    //Calculating TurnAround Time
    for(int i=0;i<p;i++){
        TurnT[i]=BurstT[i]+WaitT[i];
        AvgWaitT+=WaitT[i];
        AvgTurnT+=TurnT[i]; 
    }
   
    printf("Si No:\tArrival Time\tBurst Time\tWaiting time\tTurnAround Time\n");
    
    for(int i=0;i<p;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",pid[i],ArrT[i],BurstT[i],WaitT[i],TurnT[i]);
    }
     printf("Avgerage Waiting Time: %f \n Average Turnaround Time: %f\n",AvgWaitT/p,AvgTurnT/p);


}

