#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima

void firstMethod();

int main()
{

    double B = exp((log(MAXLENGTH) - log(A)) / 99);

    for (int j = 0; j < 99; j++)
    {

        double n = A * pow(B, j);
        //printf("%f\n", n);      test

    }

    return 0;
}

void firstMethod(){

}

//ctrl + shift + i