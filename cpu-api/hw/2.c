#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// here also without wait the parent writes first.
// and otherwise the child writes first.
int main(int argc, char *argv[]) {
    int fd = open("2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    printf("file descriptor: %d\n", fd);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        dprintf(fd, "hello, I am child (pid:%d)\n", (int)getpid());
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    } else {
        dprintf(fd, "hello, I am parent (pid:%d)\n", (int)getpid());
        // int wc = wait(NULL);
        // printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
}