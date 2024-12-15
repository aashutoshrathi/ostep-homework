#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        return 1;
    } else if (rc == 0) {
        // it returns -1 if we wait here, since child has no children
        // int wc = wait(NULL);
        // printf("hello, I am child of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    } else {
        int wc = wait(NULL);
        // wait returns the process id of the child process
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
}