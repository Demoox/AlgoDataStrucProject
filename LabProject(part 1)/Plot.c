#include <stdio.h>
#include <stdlib.h>

void plot(double *x, double *y, int title, int desc)
{

    char strtitle[57];

    switch (title)
    {
    case 1:
        strcat(strtitle, "set title \"PeriodNaive");
        break;
    case 2:
        strcat(strtitle, "set title \"PeriodSmart");
        break;
    }

    switch (desc)
    {
    case 1:
        strcat(strtitle, " con metodo creazione stringhe 1\"");
        break;
    case 2:
        strcat(strtitle, " con metodo creazione stringhe 2\"");
        break;
    case 3:
        strcat(strtitle, " con metodo creazione stringhe 3\"");
        break;
    }

    printf("%s", strtitle);

    char *commands[] = {
        strtitle,
        "set xlabel \"j\"",
        "set ylabel \"time\"",
        "set autoscale",
        //"set logscale",
        "plot 'data' with lines"
        /*"plot 'data' with linespoints pointtype 7"*/};

    FILE *temp = fopen("data", "w");
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    for (int i = 0; i < 99; i++)
    {
        if (y[i] < 2)
            fprintf(temp, "%lf %lf \n", x[i], y[i]); //Write the data to a temporary file
    }

    for (int i = 0; i < 5; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}

void plotDeviazione(double *x, double *y, double mean, double deviation)
{

    char *commands[] = {
        "set xlabel \"j\"",
        "set ylabel \"time\"",
        "set autoscale",
        //"set logscale",
        "plot 'data' with points pointtype 7, 'mean' with lines, '+σ' with lines, '-σ' with lines",
        };

    FILE *temp = fopen("data", "w");
    FILE *temp1 = fopen("mean", "w");
    FILE *temp2 = fopen("+σ", "w");
    FILE *temp3 = fopen("-σ", "w");

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    for (int i = 0; i < 99; i++)
    {
        fprintf(temp, "%lf %lf \n", x[i], y[i]); //Write the data to a temporary file
    }
    for (int i = 0; i < 99; i++)
    {
        fprintf(temp1, "%lf %lf \n", x[i], mean);
    }
    for (int i = 0; i < 99; i++)
    {
        fprintf(temp2, "%lf %lf \n", x[i], mean + deviation);
    }
    for (int i = 0; i < 99; i++)
    {
        fprintf(temp3, "%lf %lf \n", x[i], mean - deviation);
    }

    //------------------------------------------
    for (int i = 0; i < 4; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}