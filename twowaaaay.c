#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
  // 
  int fd1[2],fd2[2];
  pid_t pid;

  if(pipe(fd1) == -1 || pipe(fd2) == -1){
    perror("pipe erropr");
    return 1;
  }
  pid = fork();

  if(pid <0){
    perror("fork error");
  }
  if(pid == 0){
    // child
    close(fd1[1]);
    close(fd2[0]);

    int arr[20];
    int n;
    int size=read(fd1[0],arr,sizeof(arr));
    n = size / sizeof(int);
    int sum =0;
    for (int i = 0; i <n ; i++)
    {
      sum+=arr[i];
    }

    // write sum to parent

    write(fd2[1],&sum,sizeof(sum));
    close(fd1[0]);
    close(fd2[1]);
    return 0;
    
    



  }else if(pid>0){
    //parent
    close(fd1[0]);
    close(fd2[1]);
    int n;
        printf("Enter how many number to pass :");
        scanf("%d",&n);
      int arr[n];

    printf("Enter the number to be passed from parent to child :");
    for (int i = 0; i < n; i++)
    {
      scanf("%d",&arr[i]);
    }

    sleep(10);
    printf("THe elements are sendingg ...");
    write(fd1[1],arr,sizeof(arr));


    int sum =0;
    //read the sum from child

    read(fd2[0],&sum,sizeof(sum));
    printf("The sum is %d",sum);

    close(fd1[1]);
    close(fd2[0]);
    return 0;







    



  }






}