#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        return 1;
    } else if (rc == 0) {
        // run ls using execvp
        char *myargs[3];
        myargs[0] = strdup("ls");
        myargs[1] = NULL;
        myargs[2] = NULL;
        // execl("/bin/ls", "ls", NULL, NULL);
        // execle("ls", "ls", NULL);
        // execlp("ls", "ls", NULL);
        // execvp(myargs[0], myargs);
        execv("ls", myargs);
    } else {
        printf("I'm parent, btw\n");
    }
    return 0;
}