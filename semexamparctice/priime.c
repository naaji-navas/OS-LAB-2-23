#include<stdio.h>
#include<math.h>
#include <stdbool.h>
bool isPrime( int n){
  int i;
  for (i=2; i*i<= n;i++){
    if(n%i ==0){
      return false;
    }
  }
  return true;

}
int main(){
  printf("Enter the limit up to which the number should print :");
  int limit;
  scanf("%d",&limit);
  for (int i = 2; i <= limit; i++)
  {
    if(isPrime(i)){
      printf("%d ",i);
    }
  }
  

}
