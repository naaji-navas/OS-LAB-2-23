#include <stdio.h>
// structure for representing the process

struct Process{
  int pid;
  int at;
  int bt;
  int wt;
  int ct;
  int tat;
};

void calculateTimes(struct Process p[],int n){
  int tw=0;
  int ttat=0;
  p[0].ct = p[0].at + p[0].bt;
  p[0].tat = p[0].ct - p[0].at;
  p[0].wt =  p[0].tat - p[0].bt;

  for (int i = 0; i < n; i++)
  {
    p[i].ct = p[i-1].ct + p[i].bt;
    p[i].tat =p[i].ct - p[i].at;
    p[i].wt = p[i].tat - p[i].bt;
    tw += p[i].wt;
    ttat+=p[i].tat;
  }

  float avgwt= (float) tw/n;
  float avgtat= (float) ttat/n;
  printf("Average wating time is %d",avgwt);
  printf("Average Turn around time is %d",avgtat);
  
}

int main(){
  int n;
  printf("Enter the number of process");
  scanf("%d", n);
  struct Process p[n];

  //  Inputting the process
  for (int  i = 0; i < n; i++){
      p[i].pid += i+1;
      printf("Enter the arrival time and burst time of p",i+1);
      scanf("%d %d",&p[i].at,p[i].bt);
  }

  // sort the structure based on the arrival time
for (int i = 0; i < n-1; i++)
{
  for (int  j = 0; j < n -i-1; j++)
  {
    if(p[i].at>p[i+1].at){
      struct Process temp = p[j];
      p[j] = p[j+1];
      p[j+1] = temp;
    }
  }
  
}


  calculateTimes(p,n);
  
  

}