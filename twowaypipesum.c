#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
  // program to find the sum of n numbers using two way pipe
  int fd1[2],fd2[2],n;
  pid_t pid;
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
    // child process
    close(fd1[1]);
    close(fd2[0]);
    int buffer[100];
    int size = read (fd1[0],buffer,sizeof(buffer));
    n =size/sizeof(int);
    int sum =0;
    for (int i= 0 ; i<n; i++){
      sum+=buffer[i];
    }
    // write the sum to the parent
    write(fd2[1],&sum,sizeof(sum));
    close(fd1[0]);
    close(fd2[1]);
    return 0;

  }else if (pid>1){
    // parent process
    close (fd1[0]);
    close (fd2[1]);
    printf("Enter the number of terms : \n");
    scanf("%d",&n);
    int message[n];
    printf("Enter the numbers : \n");
    for (int i = 0; i < n; i++)
    {
      scanf("%d",&message[i]);
    }
    printf("Passing value to the child...\n");
    write(fd1[1],message,sizeof(message));
    // read the sum from the child
    int sum;
    read(fd2[0],&sum,sizeof(sum));
    printf("The sum is : %d\n (from)",sum );
    close(fd1[1]);
    close(fd2[0]);
    return 0;

  }
}