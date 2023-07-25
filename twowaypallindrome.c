#include <stdio.h>
#include <unistd.h>

int main(){
  int pc[2];
  int cp[2];

  if(pipe(pc) ==-1 || pipe(cp) == -1){
    perror("pipe failure");
    return 1;
  }

  pid_t pid = fork();

  if(pid<0){
    perror("fork Failed");

  }else if(pid > 0 ){
    // this is the parent process
    close(pc[0]);
    close(cp[1]);

    char original_string [100];
    printf("Enter the string : ");
    gets(original_string);
    write(pc[1],original_string,strlen(original_string)+1);
    close(pc[1]);
    wait(NULL);

    char reversed_string[100];
    read(cp[0],reversed_string,100);
    printf("The reversed string is : %s\n",reversed_string);
    close(cp[0]);
    if (strcmp(original_string,reversed_string) == 0){
      printf("The string is a pallindrome\n");
    }else{
      printf("The string is not a pallindrome\n");
    }
    return 0;

  }else if (pid==0){
    // this is the child process
    close(pc[1]);
    close(cp[0]);

    char original_string[100];
    read(pc[0],original_string,100);
    close(pc[0]);

    int i,j;
    char reversed_string[100];
    for(i=strlen(original_string)-1,j=0;i>=0;i--,j++){
      reversed_string[j] = original_string[i];
    }
    reversed_string[j] = '\0';
    write(cp[1],reversed_string,strlen(reversed_string)+1);
    close(cp[1]);
    return 0;
  }

}