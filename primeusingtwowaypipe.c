#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

// program to send the limit from the parent to the child and then the child will print the prime numbers up to that limit
bool isPrime(int n){
  if(n <= 1){
    return false;
  }
  for(int i = 2 ; i < n ; i++){
    if(n % i == 0){
      return false;
    }
  }
  return true;
}

int main(){
  int fd1[2],fd2[2],n;
  pid_t pid;
  if(pipe(fd1) == -1){
    perror("pipe");
    return 1;
  }
  if(pipe(fd2) == -1){
    perror("pipe");
    return 1;
  }
  pid = fork();
  if(pid < 0){
    perror("fork");
    return 1;
  }

  if(pid == 0){
    // this is the child process

    close(fd1[1]);
    close(fd2[0]);

    int arr[5];
    read(fd1[0],arr,sizeof(arr));
    int n = sizeof(arr)/sizeof(arr[0]);
    printf(" n is %d\n",n);
    int primeCount = 0; // Count of prime numbers
    for(int i = 0 ; i < n ; i++){
      if(isPrime(arr[i])){
        primeCount++;
      }
    }
    
    // Declare the prime array with the correct size
    int prime[primeCount];
    int k = 0;
    for(int i = 0 ; i < n ; i++){
      if(isPrime(arr[i])){
        prime[k++] = arr[i];
      }
    }

    write(fd2[1],prime,sizeof(prime));
    close(fd1[0]);
    close(fd2[1]);
    return 0;

  }
  else if(pid > 0){
    close (fd1[0]);
    close (fd2[1]);
    // this is the parent process
    printf("Please enter the number of elements to check :");
    int n;
    scanf("%d",&n);
    int arr[n];
    printf("Please enter the elements : ");
    for(int i = 0 ; i < n ; i++){
      scanf("%d",&arr[i]);
    }
    write(fd1[1],arr,sizeof(arr));




    int primeCount;
    read(fd2[0],&primeCount,sizeof(primeCount)); // Read the count of prime numbers
    int prime[primeCount];
    read(fd2[0],prime,sizeof(prime)); // Read the prime numbers
    printf("The prime numbers are : ");
    for(int i = 0 ; i < primeCount ; i++){
      printf("%d ",prime[i]);
    }
    printf("\n");
    close(fd1[1]);
    close(fd2[0]);
    return 0;
  }
}
