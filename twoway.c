//TWOWAY PIPE
//Najid Navas
//CS B
//20220064


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 256

int is_prime(int num) {
    if (num <= 1)
        return 0;
    if (num == 2)
        return 1;
    if (num % 2 == 0)
        return 0;

    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

void parent_process(int read_pipe_fd[2], int write_pipe_fd[2], int n) {
    close(read_pipe_fd[0]); // Close the read end of read_pipe_fd since the parent only writes
    close(write_pipe_fd[1]); // Close the write end of write_pipe_fd since the parent only reads

    // Generate n numbers and send them through the write_pipe_fd
    int number;
    for (int i = 1; i <= n; i++) {
        number = i;
        write(write_pipe_fd[1], &number, sizeof(int));
        printf("Parent process sent number: %d\n", number);
    }

    // Read prime numbers from the read_pipe_fd
    printf("Prime numbers received from child process: ");
    while (read(read_pipe_fd[0], &number, sizeof(int)) == sizeof(int)) {
        printf("%d ", number);
    }
    printf("\n");

    close(read_pipe_fd[0]);
    close(write_pipe_fd[1]);
}

void child_process(int read_pipe_fd[2], int write_pipe_fd[2]) {
    close(read_pipe_fd[1]); // Close the write end of read_pipe_fd since the child only reads
    close(write_pipe_fd[0]); // Close the read end of write_pipe_fd since the child only writes

    int number;
    ssize_t bytes_read;

    // Read numbers from the read_pipe_fd, calculate prime numbers, and send them back through write_pipe_fd
    while ((bytes_read = read(read_pipe_fd[0], &number, sizeof(int))) == sizeof(int)) {
        if (is_prime(number)) {
            write(write_pipe_fd[1], &number, sizeof(int));
        }
    }

    if (bytes_read < 0) {
        perror("read");
    }

    close(read_pipe_fd[0]);
    close(write_pipe_fd[1]);
}

int main() {
    int read_pipe_fd[2]; // 0: read end, 1: write end
    int write_pipe_fd[2]; // 0: read end, 1: write end
    pid_t pid;
    int n;

    printf("Enter the number of integers to send from parent to child: ");
    scanf("%d", &n);

    // Create two pipes
    if (pipe(read_pipe_fd) == -1 || pipe(write_pipe_fd) == -1) {
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
        child_process(read_pipe_fd, write_pipe_fd);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        parent_process(read_pipe_fd, write_pipe_fd, n);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

Sample input and Output

Enter the number of integers to send from parent to child: 10
Parent process sent number: 1
Parent process sent number: 2
Parent process sent number: 3
Parent process sent number: 4
Parent process sent number: 5
Parent process sent number: 6
Parent process sent number: 7
Parent process sent number: 8
Parent process sent number: 9
Parent process sent number: 10
Prime numbers received from child process: 2 3 5 7 



