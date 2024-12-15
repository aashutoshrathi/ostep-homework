#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/wait.h>

/*
    If you wait in the parent process, the child process will be executed first and then the parent process will be executed. Otherwise, the parent process will be executed.
*/
int main(int argc, char *argv[]) {
    int x = 42;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I am child (pid:%d) and x is: %d\n", (int)getpid(), x);
        x++;
        printf("hello, I am child (pid:%d) and x is now: %d\n", (int)getpid(), x);
    } else {
        // wait(NULL);
        printf("hello, I am parent of %d (pid:%d) and x is: %d\n", rc, (int)getpid(), x);
        x--;
        printf("hello, I am parent of %d (pid:%d) and x is now: %d\n", rc, (int)getpid(), x);
    }
    return 0;
}