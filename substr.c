#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>

bool isPresent(char arr[]){
  int size = strlen(arr);
  char str[] = "cat";
  for(int i = 0;i<size;i++){
      int count = 0;
    if(arr[i] == str[0]){
      int k = i;
      for(int j = 0;j<strlen(str);j++){
        if(str[j]!=arr[k]){
          break;
        }
        k++;
        count++;
        if(count == strlen(str))
          return true;
      }
    }
  }
  return false;
}

int main(){
  pid_t pid;
  int fd1[2],fd2[2];

  if(pipe(fd1) == -1 || pipe(fd2) == -1){
    perror("pipe");
    return 1;
  }

  pid = fork();

  if(pid<0){
    perror("fork");
    return 1;
  }
  if(pid == 0){
      close(fd1[1]);
      close(fd2[0]);

      char str[100];
      int present[1];
      read(fd1[0],str,sizeof(str));
      if(isPresent(str)){
        present[0] = 1;
      }
      write(fd2[1],present,sizeof(present));

      close(fd1[0]);
      close(fd2[1]);
  }

  if(pid>0){
    close(fd1[0]);
    close(fd2[1]);

    char arr[100];
    scanf("%s",arr);

    write(fd1[1],arr,sizeof(arr));
    int pre[1];
    read(fd2[0],pre,sizeof(pre));
    if(pre[0] == 1){
      printf("Present\n");
    }
    else{
      printf("Not Present\n");
    }

    close(fd1[1]);
    close(fd2[0]);
  }
}