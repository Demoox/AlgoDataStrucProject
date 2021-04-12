#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "PeriodSmart.c"
#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima
#define Emax 0.001       //Errore relativo massimo

void firstMethod();
void secondMethod();
void thirdMethod();
long getResolution();
void plot();

/*int mainoriginale()//nel calcolo del tempo viene incluso anche il tempo di creazione della stringa
{
    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;

    char *S = NULL;

    double y[100];

    for (int j = 0; j < 99; j++)
    {
        n = A * pow(B, j);

        struct timespec start, end;

        long R = getResolution();

        clock_gettime(CLOCK_MONOTONIC, &start);

        int k = 0;

        do
        {
            S = malloc((int)floor(n) + 1); //TODO: controlla uso memoria

            //firstMethod((int)floor(n), S);
            secondMethod((int) floor(n),S);
            //thirdMethod((int) floor(n),S);

            //printf("%s\n\n\n", S);    //Stampa stringhe generate

            periodSmart(S);

            free(S);

            clock_gettime(CLOCK_MONOTONIC, &end);

            k++;

        } while ((end.tv_nsec - start.tv_nsec) < ((R / Emax) + R));

        long tn = (end.tv_nsec - start.tv_nsec) / k; //tempo medio per lunghezza n

        //printf("%lu\n", tn);
        y[j]=tn;
    }

    plot(y);

    return 0;
}*/

int main()
{
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

            firstMethod((int)floor(n), S);
            //secondMethod((int) floor(n),S);
            //thirdMethod((int) floor(n),S);

            //printf("%s\n\n\n", S);    //Stampa stringhe generate

            clock_gettime(CLOCK_MONOTONIC, &start);

            periodSmart(S);

            clock_gettime(CLOCK_MONOTONIC, &end);

            free(S);

            k++;

            tempo += end.tv_nsec - start.tv_nsec;

            printf("%d\n", tempo);

        } while (tempo < ((R / Emax) + R));

        long tn = tempo / k; //tempo medio per lunghezza n

        //printf("%lu\n", tn);
        y[j] = tn;
    }

    plot(y);

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

void plot(double *y)
{

    char *commandsForGnuplot[] = {"set title \"Metodo 1\"", "set xlabel \"j\"", "set ylabel \"time\"", "set style line 1 \\ linecolor rgb '#0060ad' \\ linetype 1 linewidth 2 \\ pointtype 7 pointsize 1.5", "plot 'data' with linespoints linestyle 1"};

    char *commands[] = {
        "set title \"Period Smart\"",
        "set xlabel \"j\"",
        "set ylabel \"time\"",
        "set autoscale",
        /*"set logscale",*/
        "plot 'data' with lines"};

    FILE *temp = fopen("data", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    int i;
    for (i = 0; i < 99; i++)
    {
        fprintf(temp, "%d %lf \n", i + 1, y[i]); //Write the data to a temporary file
    }

    for (i = 0; i < 5; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}

//ctrl + shift + i auto-indent