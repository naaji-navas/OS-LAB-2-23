#include<stdio.h>
int main(){
    int p[10],at[10],ct[10],bt[10],wt[10],i,j,temp=0,n;
    float awt=0,atat=0;

    printf("Enter the numberof processes");
    scanf("%d",&n);
    printf("Enter %d  processes :",n);
    for (int i = 0; i < n; i++)
    {
      scanf("d",&p[i]);
    }
    for (int i = 0; i < n; i++)
    printf("Enter p%d  arrival time :",p[i]);
    {
      scanf("d",&at[i]);
    }
    for (int i = 0; i < n; i++)
    printf("Enter p%d  burst time time :",p[i]);
    {
      scanf("d",&at[i]);
    }

    // sorting the processes according to the at
    for (int i = 0; i < n; i++)
    {
      for (int  j = 0; i < n-1; i++)
      {
        if(at[j]>at[j+1]){
          temp =  p[j+1];
          p[j+1] = p[j];
          p[j] = temp;

          temp =  at[j+1];
          at[j+1] = at[j];
          at[j] = temp;

          temp =  bt[j+1];
          bt[j+1] = bt[j];
          bt[j] = temp;

        }
      }
      
    }


    // calculating the first completion time

     ct[0]=at[0]+bt[0];

     for(i=1;i<n;i++){
      temp=0;
      if(ct[i-1]<at[i]){

      }
     }
    
    
    


}