#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima
#define Emax 0.001       //Errore relativo massimo
#define BILLION 1000000000L;

//Questa funzione serve a calcolare il tempo medio di generazione delle stringhe in base al metodo di generazione utilizzato,
//questo per migliorare la misurazione effettuata nel file TimeMeasurement
double *StringsGenerationTime(int generationMethod)
{

    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;

    char *S = NULL;

    static double x[100];

    double tn = 0;

    for (int j = 0; j <= 99; j++)
    {
        n = A * pow(B, j);
        double time_sum =0;
        
        for(int w=0; w<=999; w++)
        {
          struct timespec start, end;
  
          long R = getResolution() / (double)BILLION;

          int k = 0;

          double tempo = 0;

          clock_gettime(CLOCK_MONOTONIC, &start);
          do
          {
            S = malloc((int)floor(n) + 1);

            switch (generationMethod)
            {
            case 1:
                firstMethod((int)floor(n), S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 2:
                secondMethod((int)floor(n), S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 3:
                thirdMethod((int)floor(n), S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            default:
                printf("Valore non valido.\n");
                break;
            }

            free(S);

            k++;
            
            tempo = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double)BILLION;
          } while (tempo < ((R / Emax) + R));
            time_sum += (tempo / k);
        }
        x[j] = time_sum/1000;
    }
    

    return x;
}

//Questa funzione serve a calcolare il tempo medio di generazione di una stringa lunga n e generata con il metodo dato in input,
//questo per migliorare la misurazione effettuata nel file MainDeviazione
double SingleStringGenerationTime(int generationMethod, double n)
{
    char *S = NULL;

    double time_sum =0;

    for (int j = 0; j <= 999; j++)
    {
        struct timespec start, end;

        long R = getResolution() / (double)BILLION;

        int k = 0;

        double tempo = 0;
        
        clock_gettime(CLOCK_MONOTONIC, &start);
        do
        {
            S = malloc((int)floor(n) + 1);

            switch (generationMethod)
            {
            case 1:
                firstMethod((int)floor(n), S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 2:
                secondMethod((int)floor(n), S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 3:
                thirdMethod((int)floor(n), S);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            default:
                printf("Valore non valido.\n");
                break;
            }

            free(S);

            k++;
            tempo = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double)BILLION;

        } while (tempo < ((R / Emax) + R));

        time_sum += (tempo / k);
   }

    return time_sum/1000;
}