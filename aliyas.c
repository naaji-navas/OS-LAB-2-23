#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

bool isVowel(char c){
  if(c == 'a'|| c == 'e'||c == 'i'||c == 'o'||c == 'u'||c == 'A'||c == 'E'||c == 'I'||c == 'O'||c == 'U')
    return true;
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
   
    char buffer[100];
    read(fd1[0],&buffer,sizeof(buffer));
    int i=0;
    int j=0;
    char varr[100];
    while (buffer[i] != '\0') {
            if (isVowel(buffer[i])) {
                varr[j]=buffer[i];
                j++;
            }
            i++;
    }
    varr[j] = '\0';
    write(fd2[1],varr,sizeof(varr));

    close(fd1[0]);
    close(fd2[1]);
  }

  if(pid > 0){
    close(fd1[0]);
    close(fd2[1]);

    char arr[100];
    printf("Enter the string\n");
    fgets(arr,sizeof(arr),stdin);
    write(fd1[1],arr,sizeof(arr));

    read(fd2[0],arr,sizeof(arr));
    printf("%s",arr);

    close(fd1[1]);
    close(fd2[0]);
  }
}