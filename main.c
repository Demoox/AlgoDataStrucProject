#include <stdio.h>
#include <time.h>

long getResolution();
void periodNaive();

int main()
{
    printf("%lu\n", getResolution());
    printf("Hello, World!\n");
    return 0;
}

long getResolution()
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do
    {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}


void periodNaive(int* [])
{
    //prova
    //prova signed
    printf();
}