#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int readZeroBytes() {
    char buf[0];
    read(0, buf, 0);
    return 0;
}

// turns out to be giving 0 or 1 microsecond mostly, so not using this.
int testTime() {
    struct timeval t1, t2;

    gettimeofday(&t1, NULL);
    gettimeofday(&t2, NULL);

    long sec_diff = t2.tv_sec - t1.tv_sec;
    long usec_diff = t2.tv_usec - t1.tv_usec;

    if (usec_diff < 0) {
        sec_diff -= 1;
        usec_diff += 1000000;
    }

    printf("Time taken: %ld seconds, %ld microseconds\n", sec_diff, usec_diff);
    return 0;
}

int main() {
    testTime();
    int numCalls = 1e8;

    struct timespec tsStart, tsEnd;

    // switched to clock_gettime of CLOCK_MONOTONIC as it gives more granular time -> in nano seconds over gettimeofday which gives in micro seconds
    clock_gettime(CLOCK_MONOTONIC, &tsStart);
    for (int i = 0; i < numCalls; i++) {
        readZeroBytes();
    }
    clock_gettime(CLOCK_MONOTONIC, &tsEnd);

    long long start = tsStart.tv_sec * 1e9 + tsStart.tv_nsec;
    long long end = tsEnd.tv_sec * 1e9 + tsEnd.tv_nsec;
    long long diff = end - start;
    printf("Time taken for %d syscalls: %lld ns\n", numCalls, diff);

    long long avg = diff / numCalls;
    printf("Average time per syscall: %lld ns\n", avg);
    // Average time per syscall: 268 ns
}