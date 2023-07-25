#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(){
  // program to send some random numbers input by the user to the child process using two way pipe
  int fd1[2],fd2[2],n;
  pid_t pid;
  if(pipe(fd1)==-1 || pipe(fd2) ==-1){
    perror("pipe");
    return 1;
  }
  pid = fork();
  if(pid<0){
    perror("fork");
    return 1;
  }else if(pid==0){
    // this is the child process
    close(fd1[1]);
    close(fd2[0]);
    int buffer[100];
  }
}