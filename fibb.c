#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>


bool isFib(int x){
  int sequence[100];
  if(x==0||x==1){
    return true;
  }
  sequence[0] = 0;
  sequence[1] = 1;
  for(int i = 2;i<100;i++){
    sequence[i] = sequence[i-1] + sequence[i-2];
    if(x == sequence[i]){
      return true;
    }
    else if(x<sequence[i]){
      return false;
    }
}
}
int main(){
  printf("%d",isFib(5));


}