#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int pipefd[2];  // we initialize it like this, as pipe function fills it with file descriptors

    // inspired form how god created ears, eyes and let's not go down below, programmers chose to create file descriptor in pair when you call pipe();
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    printf("pipefd[0] = %d\n", pipefd[0]);
    printf("pipefd[1] = %d\n", pipefd[1]);

    int alice = fork();
    if (alice == 0) {
        close(pipefd[0]);  // because we aren't going to read from the pipe
        printf("I am the first child\n");
        const char msg[] = "What is tiny spec of dust suspended in a sunbeam?\n";
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
        return 0;
    }

    int bob = fork();
    if (bob == 0) {
        // now bob here also has two fd, but we just need stdin.
        close(pipefd[1]);  // because we aren't going to write to the pipe
        char receivedMsg[100];
        read(pipefd[0], receivedMsg, sizeof(receivedMsg));
        printf("Received message: %s", receivedMsg);
        printf("I am the second child\n");
        return 0;
    }
    printf("I have two children: %d and %d\n", alice, bob);
}