#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "StringCreator.c"
#include "PeriodSmart.h"
#include "PeriodNaive.h"
#include "Plot.c"

#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima
#define Emax 0.001       //Errore relativo massimo
#define BILLION 1000000000L;

void plotSueg();

int main()
{
    int firstChoice, secondChoice;
    printf("Scegli un metodo per creare la stringa:\n");
    printf("1- Generazione pseudo-casuale\n");
    printf("2- s(i) = s((i-1) mod q+1)\n");
    printf("3- Variante del metodo 3 con aggiunta di lettera c\n");
    printf("Metodo da usare: ");
    scanf("%d", &firstChoice);

    //-----------------------------------------------

    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;

    char *S = NULL;

    double x[100];
    double y[100];
    double x1[100];
    double y1[100];

    double tn = 0;

    for (int j = 0; j <= 99; j++)
    {
        n = A * pow(B, j);

        struct timespec start, end;

        long R = getResolution() / (double)BILLION;

        int k = 0;

        double tempo = 0;

        clock_gettime(CLOCK_MONOTONIC, &start);
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

            periodSmart(S);
            clock_gettime(CLOCK_MONOTONIC, &end);

            free(S);

            k++;
            tempo += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double)BILLION;

        } while (tempo < ((R / Emax) + R));

        tn = (tempo / k);

        printf("%i   %lf\n", (int)floor(n), tn);
        x[j] = n;
        y[j] = tn;
    }

    //-----------------------------------------------

    tn = 0;

    for (int j = 0; j <= 99; j++)
    {
        n = A * pow(B, j);

        struct timespec start, end;

        long R = getResolution() / (double)BILLION;

        int k = 0;

        double tempo = 0;

        clock_gettime(CLOCK_MONOTONIC, &start);
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

            periodNaiveMethod2(S);
            clock_gettime(CLOCK_MONOTONIC, &end);

            free(S);

            k++;
            tempo += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double)BILLION;

        } while (tempo < ((R / Emax) + R));

        tn = (tempo / k);

        printf("%i   %lf\n", (int)floor(n), tn);
        x1[j] = n;
        y1[j] = tn;
    }

    plotSueg(x, y, x1, y1, firstChoice);

    return 0;
}

void plotSueg(double *x, double *y, double *x1, double *y1, int title)
{

    char strtitle[29];

    switch (title)
    {
    case 1:
        strcat(strtitle, "Metodo creazione stringhe 1\"");
        break;
    case 2:
        strcat(strtitle, "Metodo creazione stringhe 2\"");
        break;
    case 3:
        strcat(strtitle, "Metodo creazione stringhe 3\"");
        break;
    }

    char *commands[] = {
        strtitle,
        "set xlabel \"j\"",
        "set ylabel \"time\"",
        //"set autoscale",
        "set logscale",
        "plot 'PeriodSmart' with lines, 'PeriodNaive' with lines"};

    FILE *temp = fopen("PeriodSmart", "w");
    FILE *temp1 = fopen("PeriodNaive", "w");

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    for (int i = 0; i < 99; i++)
    {
        if (y[i] < 2)
            fprintf(temp, "%lf %lf \n", x[i], y[i]);
    }
    for (int i = 0; i < 99; i++)
    {
        if (y[i] < 2)
            fprintf(temp1, "%lf %lf \n", x1[i], y1[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}