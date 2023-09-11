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
  pid_t pid;
  int fd1[2],fd2[2];

  if(pipe(fd1) == -1 || pipe(fd2) == -1){
    perror("pipe");
    return 1;
  }

  pid = fork();

  if(pid < 0){
    perror("fork");
    return 1;
  }

  if(pid == 0){

    close(fd1[1]);
    close(fd2[0]);

    int j = 0;
    int fib[100];
    int size = read(fd1[0],fib,sizeof(fib));
    int num = size/4;
    //printf("%d",num);
    for(int i = 0; i< num;i++){
      if(isFib(fib[i]))
          j++;
    }
    int ans[j];
    j = 0;
    for(int i = 0; i< num;i++){
      if(isFib(fib[i])){
          ans[j]=fib[i];
          //printf("%d",fib[i]);
          j++;
      }
    }
    // for(int i = 0;i<num;i++){
    //   printf("%d",ans[i]);
    // }


    write(fd2[1],ans,sizeof(ans));

    close(fd1[0]);
    close(fd2[1]);
  }

  if(pid > 0){

    close(fd1[0]);
    close(fd2[1]);
    int n;
    printf("Enter the number of terms\n");
    scanf("%d",&n);

    int arr[n];
    for(int i = 0;i<n;i++){
      scanf("%d",&arr[i]);
    }

    write(fd1[1],arr,sizeof(arr));

    int size = read(fd2[0],arr,sizeof(arr));
    int count = size/4;
    for(int i = 0;i<count;i++){
      printf("%d",arr[i]);
    }

    close(fd1[1]);
    close(fd2[0]);

  }

}