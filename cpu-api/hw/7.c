#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(STDOUT_FILENO);
        // no buffer to write to, so nothing will be written to the file or terminal
        printf("This should not print out\n");
        exit(0);
    } else {  // Parent process
        printf("Parent process (PID=%d) is waiting for child to finish...\n", getpid());
    }

    return 0;
}