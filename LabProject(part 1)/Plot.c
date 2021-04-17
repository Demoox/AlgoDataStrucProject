#include <stdio.h>
#include <stdlib.h>

void plot(double *x, double *y, char *title)
{

    char *strtemp;

    if(strcmp(title, "PeriodNaive")==0)
        strtemp = "set title \"PeriodNaive\"";
    else
        strtemp = "set title \"PeriodSmart\"";

    char *commands[] = {
        strtemp,
        "set xlabel \"j\"",
        "set ylabel \"time\"",
        "set autoscale",
        /*"set logscale",*/
        "plot 'data' with lines"};

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