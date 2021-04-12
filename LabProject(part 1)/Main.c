#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "StringCreator.c"
#include "PeriodSmart.c"

#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima
#define Emax 0.001       //Errore relativo massimo

int main()
{
    int scelta;
    printf("Opzioni per la creazione della stringa:\n");
    printf("1- Le lettere s(i) della stringa, per ogni i=1,…,n, vengono generate in modo pseudo-casuale e indipendentemente una dall'altra;\n");
    printf("2- Un parametro q compreso fra 1 ed n viene generato in modo pseudo-causale; in seguito vengono generate le lettere s(i) per ogni i=1,…,q, seguendo il medoto 1.; infine la parte rimanente di s viene generata seguendo la formula s(i)=s((i−1) mod q+1) per ogni i=q+1,…,n;\n");
    printf("3- una variante del metodo 2. viene applcata, con l'eccezione che ad s(q) viene assegnata una lettera special (ad esempio, 'c') differente da tutte quelle generate in modo pseudo-casuale;\n");
    printf("Metodo da utilizzare: ");
    scanf("%d", &scelta);

    //-----------------------------------------------

    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;

    char *S = NULL;

    double y[100];

    for (int j = 0; j < 99; j++)
    {
        n = A * pow(B, j);

        struct timespec start, end;

        long R = getResolution();

        int k = 0;

        int tempo = 0;

        do
        {
            S = malloc((int)floor(n) + 1); //TODO: controlla uso memoria

            switch (scelta)
            {
            case 1:
                firstMethod((int)floor(n), S);
                break;
            case 2:
                secondMethod((int)floor(n), S);
                break;
            case 3:
                thirdMethod((int)floor(n), S);
                break;
            default:
                printf("Valore non valido.\n");
                break;
            }

            clock_gettime(CLOCK_MONOTONIC, &start);

            periodSmart(S);

            clock_gettime(CLOCK_MONOTONIC, &end);

            free(S);

            k++;

            tempo += end.tv_nsec - start.tv_nsec;

            printf("%d\n", tempo);

        } while (tempo < ((R / Emax) + R));

        long tn = tempo / k;

        y[j] = tn;
    }
    //-----------------------------------------------

    plot(y);

    return 0;
}