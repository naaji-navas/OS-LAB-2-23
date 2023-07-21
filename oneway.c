//ONEWAY PIPE
//Najid Navas
//CS B
//20220064


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 256

void parent_process(int pipe_fd[2], int numbers[], int n) {
    close(pipe_fd[0]); // Close the read end since the parent only writes

    for (int i = 0; i < n; i++) {
        write(pipe_fd[1], &numbers[i], sizeof(int));
        printf("Parent process sent number: %d\n", numbers[i]);
    }

    close(pipe_fd[1]);
    wait(NULL); // Wait for the child process to finish
}

void child_process(int pipe_fd[2]) {
    close(pipe_fd[1]); // Close the write end since the child only reads

    int number;
    ssize_t bytes_read;

    while ((bytes_read = read(pipe_fd[0], &number, sizeof(int))) == sizeof(int)) {
        printf("Child process received number: %d\n", number);
    }

    if (bytes_read < 0) {
        perror("read");
    }

    close(pipe_fd[0]);
}

int main() {
    int pipe_fd[2]; // 0: read end, 1: write end
    pid_t pid;
    int n;

    printf("Enter the number of integers to send from parent to child: ");
    scanf("%d", &n);

    int numbers[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        child_process(pipe_fd);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        parent_process(pipe_fd, numbers, n);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

Sample Input

Enter the number of integers to send from parent to child: 5
Enter 5 integers:
10
20
30
40
50

Sample Output

Parent process sent number: 10
Parent process sent number: 20
Parent process sent number: 30
Parent process sent number: 40
Parent process sent number: 50
Child process received number: 10
Child process received number: 20
Child process received number: 30
Child process received number: 40
Child process received number: 50



