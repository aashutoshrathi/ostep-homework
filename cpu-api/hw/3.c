#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Multiple ways I found when digging for the ways to make the child execute first without wait.
1. wait(NULL) and sleep are great, but they are hacky anyways, like they don't feel like the right way to do it.
2. One good way I read up about was using Shared Memory or Semaphores, but will skip since it's not discussed yet. But the API for semaphores looks simple and intuitive.
3. [FINAL] The thing I'm using here is signals, since we discussed this in this chapter. I learnt that there is a signal SIGCHLD that is sent to the parent when the child process is terminated. And thanks to the signal APIs, we can handle this signal that's usually ignored.
*/

int parent_can_execute = 0;

void handler(int sig) {
    parent_can_execute = 1;
}

int main() {
    int rc = fork();
    signal(SIGCHLD, handler);
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);  // need to exit this.
    } else if (rc == 0) {
        printf("hello\n");
    } else {
        // wait(NULL);
        while (!parent_can_execute) {
            // wait for the signal to be received.
        }
        printf("goodbye\n");
    }
}