#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "StringCreator.c"
#include "PeriodSmart.c"
#include "PeriodNaive.c"
#include "Plot.c"

#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima
#define Emax 0.001       //Errore relativo massimo

int main()
{
    int firstChoice, secondChoice;
    printf("Scegli un metodo per creare la stringa:\n");
    printf("1- Generazione pseudo-casuale\n");
    printf("2- s(i) = s((i-1) mod q+1)\n");
    printf("3- Variante del metodo 3 con aggiunta di lettera c\n");
    printf("Metodo da usare: ");
    scanf("%d", &firstChoice);
    printf("\nScegi quale funzione usare:\n");
    printf("1- PeriodNaive\n");
    printf("2- PeriodSmart\n");
    printf("Funzione da usare: ");
    scanf("%d", &secondChoice);

    //-----------------------------------------------

    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;

    char *S = NULL;

    double x[100];
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

            switch (firstChoice)
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

            

            switch (secondChoice)
            {
            case 1:
                clock_gettime(CLOCK_MONOTONIC, &start);
                periodNaiveMethod1(S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 2:
                clock_gettime(CLOCK_MONOTONIC, &start);
                periodSmart(S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            default:
                printf("Valore non valido.\n");
                break;
            }

            

            free(S);

            k++;

            tempo += end.tv_nsec - start.tv_nsec;

            printf("%d\n", tempo);

        } while (tempo < ((R / Emax) + R));

        long tn = tempo / k;

        x[j] = n;
        y[j] = tn;
    }
    //-----------------------------------------------

    switch (secondChoice)
    {
    case 1:
        plot(x, y, "PeriodNaive");
        break;
    case 2:
        plot(x, y, "PeriodSmart");
        break;
    }

    return 0;
}