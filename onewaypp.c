#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main() {
    //fd[0] - read end
    // fd[1] - write end
    int fd[2],n; // File descriptors for the pipe
    pid_t pid;     // Process ID of the child process
    
    // Create the pipe
    if (pipe(fd) == -1) { // there is some error in creating the pipe
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
        char buffer[100];
        read(fd[0],buffer,sizeof(buffer));
        // reverse the string
        int i =0;
        int j = strlen(buffer) - 1;
        char temp;
        while(i < j){
            temp = buffer[i];
            buffer[i] = buffer[j];
            buffer[j] = temp;
            i++;
            j--;
        } 
        // now the string is reversed
        
        printf("Child process recieved the data from the parent. the data is : %s\n" , buffer );
        close(fd[0]) ;// read end is also closed after reading from the pipe
        return 0;    
    }
    else if (pid > 0) {
        // this is the parent

        const char message[20];
        close(fd[0]); // this close the read end of the pipe in the parent  side . 
        printf("type the stting   : ");
        scanf("%s",message);
        printf("Passing value to the child...\n");
        write(fd[1],message,sizeof(message));
        
        close(fd[1]);// this closes the write end of the file after the data has been written.
        
        

        return 0;
    }

    
}
