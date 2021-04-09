#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define A 1000           //lunghezza minima
#define MAXLENGTH 500000 //lunghezza massima

void firstMethod();
void secondMethod();

int main()
{
    double B = exp((log(MAXLENGTH) - log(A)) / 99);
    double n;

    for (int j = 0; j < 99; j++)
    {
        n = A * pow(B, j);
        //printf("%f\n", n);      test
        
    }
    
    
    char S[(int) floor(n)];
    secondMethod((int) floor(n),S);

    S[(int) floor(n)] = '\0';
    printf("%s\n\n\n", S);

    

        return 0;
}

void firstMethod(){

}




void secondMethod(int n, char *S){
    int q = (rand()%n + 1 );

    for(int i = 0; i<q;i++){
        S[i] = ((rand()%2) + 'a');
    }

    for(int i = q; i<n; i++){
        S[i] = S[(i-1)%q + 1];
    }



}

//ctrl + shift + i