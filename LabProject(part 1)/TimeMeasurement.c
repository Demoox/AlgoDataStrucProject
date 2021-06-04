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
#include "StringsTime.h"

#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima
#define Emax 0.001       //Errore relativo massimo
#define BILLION 1000000000L;

int main()
{
    int methodChoice, algorithmChoice;
    printf("Scegli un metodo per creare la stringa:\n");
    printf("1- Generazione pseudo-casuale\n");
    printf("2- s(i) = s((i-1) mod q+1)\n");
    printf("3- Variante del metodo 3 con aggiunta di lettera c\n");
    printf("Metodo da usare: ");
    scanf("%d", &methodChoice);

    printf("\nScegi quale funzione usare:\n");
    printf("1- PeriodNaive\n");
    printf("2- PeriodSmart\n");
    printf("Funzione da usare: ");
    scanf("%d", &algorithmChoice);

    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;                                   //lunghezza stringa
    int measurePrec = 100;                       //indice di precisione della misura

    char *S = NULL; //stringa generata

    double x[100];                                  //array contenente le lunghezza della stringa alla j-esima iterazione
    double y[100];                                  //array contenente il tempo impiegato dall'algoritmo alla j-esima iterazione
    double tn = 0;                                  //tempo medio misurato

    double *strGenTime;                                                 //array contenente i tempi medi impiegati per generare le strighe
    strGenTime = StringsGenerationTime(methodChoice);                   //strGenTime[j] = tempo medio misurato per generare la stringa di lunghezza n=floor(A*B^j)

    for (int j = 0; j <= 99; j++)
    {
        n = A * pow(B, j);
        double time_sum = 0; //somma dei tempi medi misurati

        if (tn < (double)2) //cap di tempo massimo di 2 secondi impostato per period naive
        {
            for (int w = 0; w < measurePrec; w++) //ciclo per fare la media dei tempi medi misurati
            {
                struct timespec start, end;

                long R = getResolution() / (double)BILLION;

                int k = 0;

                double tempo = 0;

                clock_gettime(CLOCK_MONOTONIC, &start);

                do
                {
                    S = malloc((int)floor(n) + 1); //allocamento dinamico di memoria per risparmiare risorse

                    switch (methodChoice)
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

                    switch (algorithmChoice)
                    {
                    case 1:
                        //periodNaiveMethod1(S);
                        periodNaiveMethod2(S);
                        clock_gettime(CLOCK_MONOTONIC, &end);
                        break;
                    case 2:
                        periodSmart(S);
                        clock_gettime(CLOCK_MONOTONIC, &end);
                        break;
                    default:
                        printf("Valore non valido.\n");
                        break;
                    }

                    free(S);

                    k++;

                    tempo = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double)BILLION; //tempo in secondi

                } while (tempo < ((R / Emax) + R));

                time_sum += tempo / k; //calcolo del tempo medio per generare la stringa di lunghezza n e di esecuzione dell'algoritmo
            }

            tn = (time_sum / measurePrec) - strGenTime[j]; //tempo medio di esecuzione dell'algoritmo per una stringa du lunghezza n
        }

        printf("%i   %lf\n", (int)floor(n), tn); //stampa a video la combinata della lunghezza della stringa e del tempo impiegato a processarla

        x[j] = n;
        y[j] = tn;
    }

    plot(x, y, algorithmChoice, methodChoice); //funzione che stampa il grafico a fine esecuzione

    return 0;
}