#include <stdio.h>
#include <time.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}



long getResolution() {                        // fare attenzione alle divisioni su valori di tipo intero... 
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while(start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}