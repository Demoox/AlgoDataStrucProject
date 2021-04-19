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
        strcat(strtitle, "set title \"PeriodNaive");
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
        /*"set autoscale",*/
        "set logscale",
        "plot 'data' with lines"
        /*"plot 'data' with linespoints pointtype 7"*/};

    FILE *temp = fopen("data", "w");
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    int i;
    for (i = 0; i < 99; i++)
    {
        fprintf(temp, "%lf %lf \n", x[i], y[i]); //Write the data to a temporary file
    }

    for (i = 0; i < 5; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}


void plotSimple(double *x, double *y)

{

    char *commands[] = {
        "set xlabel \"j\"",
        "set ylabel \"time\"",
        "set autoscale",
        //"set logscale",

        "plot 'data' with lines"
        /*"plot 'data' with linespoints pointtype 7"*/};

    FILE *temp = fopen("data", "w");
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    int i;
    for (i = 0; i < 99; i++)
    {
        fprintf(temp, "%lf %lf \n", x[i], y[i]); //Write the data to a temporary file
    }

    for (i = 0; i < 4; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
    }
}