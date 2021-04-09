#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima

void firstMethod();
void secondMethod();
void thirdMethod();

int main()
{
    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;

    for (int j = 0; j < 99; j++)
    {
        n = A * pow(B, j);
        //printf("%f\n", n);      test
    }

    char S[(int)floor(n)];

    //firstMethod((int) floor(n),S);
    //secondMethod((int) floor(n),S);
    //thirdMethod((int) floor(n),S);

    printf("%s\n\n\n", S);

    return 0;
}

void firstMethod(int length, char *S)
{

    for (int i = 0; i < length; i++)
    {
        if (rand() % 2 == 0)
            S[i] = 'a';
        else
            S[i] = 'b';
    }

    S[length] = '\0';
}

void secondMethod(int n, char *S)
{

    int q = (rand() % n + 1);

    for (int i = 0; i < q; i++)
    {
        S[i] = ((rand() % 2) + 'a');
    }

    for (int i = q; i < n; i++)
    {
        S[i] = S[(i - 1) % q + 1];
    }

    S[n] = '\0';
}

void thirdMethod(int n, char *S)
{

    int q = (rand() % n + 1);

    for (int i = 0; i < q-1; i++)
    {
        S[i] = ((rand() % 2) + 'a');
    }

    S[q - 1] = 'c';

    for (int i = q; i < n; i++)
    {
        S[i] = S[(i - 1) % q + 1];
    }

    S[n] = '\0';
}

//ctrl + shift + i auto-indent