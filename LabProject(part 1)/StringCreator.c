#include <stdio.h>
#include <stdlib.h>
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
        //printf("%f\n", n);      test per verificare i numeri ottenuti

        char S[(int)floor(n)];
        firstMethod((int)floor(n), S);
        
        printf("%s\n\n\n", S);

    }

    return 0;
}

void firstMethod(int length, char *S){

    for(int i=0; i<length; i++){
        if(rand()%2 == 0)
            S[i]='a';
        else
            S[i]='b';
    }

    S[length]=0;

}

//ctrl + shift + i