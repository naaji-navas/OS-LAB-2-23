#include <stdio.h>
#include <unistd.h> // this is for pipe
#include <sys/types.h> // this is for pid_t
#include <string.h>
#include <stdbool.h>

bool isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return true;
    }
    return false;
}


int main() {
    int fd1[2], fd2[2], n;
    pid_t pid;

    if (pipe(fd1) == -1 ) {
        perror("pipe");
        return 1;
    }

    if (pipe(fd2) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // child process
        close(fd1[1]);
        close(fd2[0]);

        char buffer[100];
        read(fd1[0], buffer, sizeof(buffer));

        int i = 0;
        int j = 0;
        int vowelscount = 0;
        while (buffer[i] != '\0') {
            if (isVowel(buffer[i])) {
                vowelscount++;
            }
            i++;
        }

        char vowels[vowelscount + 1];
        i = 0; // Reset i to 0
        while (buffer[i] != '\0') {
            if (isVowel(buffer[i])) {
                vowels[j] = buffer[i];
                j++;
            }
            i++;
        }
        vowels[j] = '\0';

        write(fd2[1], vowels, sizeof(vowels));

        close(fd1[0]);
        close(fd2[1]);
        return 0;
    }

    if (pid > 0) {
        // parent process
        close(fd1[0]);
        close(fd2[1]);
        char buffer[100];
        printf("Enter the string: ");
        fgets(buffer, sizeof(buffer), stdin);

        write(fd1[1], buffer, sizeof(buffer));



        read(fd2[0], buffer, sizeof(buffer));

        printf("The vowels in the string are: %s\n", buffer);

        close(fd1[1]);
        close(fd2[0]);
        return 0;
    }
}
