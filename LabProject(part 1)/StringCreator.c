#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//#include "PeriodSmart.c"
#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima
#define Emax 0.001       //Errore relativo massimo

void firstMethod();
void secondMethod();
void thirdMethod();
long getResolution();
void plot();

//Modo 1:generazione pseudo-casuale della stringa.
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

/*
MOdo 2: generazione pseudo-casuale del periodo frazionario q, poi generazione della sotto-stringa da s[1] a s[q] e infine 
completamento della stringa secondo la regola s[i] = s[(i-1)%q +1].
*/
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
/*
Modo 3: variante del modo 2 con l'inserimento del carattere "c" in s[q].
*/
void thirdMethod(int n, char *S)
{
    int q = (rand() % n + 1);

    for (int i = 0; i < q - 1; i++)
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

//ctrl + shift + i auto-indent