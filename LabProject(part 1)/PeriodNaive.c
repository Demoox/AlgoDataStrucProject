#include <stdio.h>
#include <string.h>
#include <time.h>

int periodNaiveMethod1();

int main()
{

    char S[1000];
    scanf("%999s", S);
    int p = periodNaive(S);
    printf("%d", p);
    return 0;
}

int periodNaiveMethod1(char *S)
{
    int counter = 0;
    int n = strlen(S);
    for (int p = 0; p < n; p++)
    {
        for (int i = 0; i < n - p; i++)
            if (S[i] != S[i + p])
            {
                return p+i;
            }
    }
    
}