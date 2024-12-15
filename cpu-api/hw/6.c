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
        printf("Child process (PID=%d) is running...\n", getpid());
        sleep(2);  // Simulate some work
        printf("Child process exiting.\n");
        exit(42);  // Exit with status 42
    } else {       // Parent process
        int status;
        printf("Parent waiting for child (PID=%d)...\n", pid);
        pid_t waited_pid = waitpid(pid, &status, 0);

        if (waited_pid == -1) {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Parent: Child %d terminated with exit status %d.\n", waited_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}