#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2],n;   
    pid_t pid;     
    
    // Create the pipe
    if (pipe(fd) == -1) { 
        perror("pipe");
        return 1;
    }

    // Fork a child process
    pid = fork(); // pid store the process id of the child process

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if(pid == 0 ){
        // this is a child process.
        close(fd[1]); // close the write end of the pipe in the child side

        // now we want to read the data from the pipe
        int buffer[100];
        int size = read(fd[0],buffer,sizeof(buffer));
        n = size/sizeof(int);
        printf("number of elements : %d\n",n );
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += buffer[i];
        }
        printf("Child process recieved the data from the parent. the sum is : %d\n" , sum );
        close(fd[0]) ;// read end is also closed after reading from the pipe
        return 0;    
    }else if (pid > 0) // this is a parent process
    {

        close(fd[0]); // this close the read end of the pipe in the parent  side . 
        printf("Enter the number of terms : \n");
        scanf("%d",&n);
        int message[n];
        printf("Enter the numbers : \n");
        for (int i = 0; i < n; i++)
        {
            scanf("%d",&message[i]);
        }
        printf("Passing value to the child...\n");
        write(fd[1],message,sizeof(message));
        
        close(fd[1]);// this closes the write end of the file after the data has been written.
        
        
        
        return 0;
    }

    
}

