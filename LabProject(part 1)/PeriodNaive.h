#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int periodNaiveMethod1(char *S)
{
    int n = strlen(S);
    for (int p = 1; p <= n; p++)
    {
        int i;
        for (i = 0; i < n - p; i++)
        {
            if (S[i] != S[i + p])
            {
                break;
            }
        }
        if (i == n - p)
            return p;
    }
    return n;
}

//Non essendoci un metodo apposito nel linguaggio C per eseguire un Substring, abbiamo creato questa funzione che, datogli come input un array di char S,
//esegue il substring dall'indice a all'indice b. Abbiamo utilizzato la funzione malloc per allocare dinamicamente la memoria necessaria per contenere
//la stringa di output
char *substring(char *S, int a, int b)
{
    int l = b - a;
    char *s = (char *)malloc((l + 1) * sizeof(char));
    int i = 0;
    while (i < l)
    {
        s[i] = S[a + i];
        i++;
    }
    s[i] = '\0';
    return s;
}

int periodNaiveMethod2(char *S)
{
    int n = strlen(S);
    for (int p = 1; p <= n - 1; p++)
    {
        char *s1 = substring(S, 0, n - p);
        char *s2 = substring(S, p, n);
        if (strcmp(s1, s2) == 0)
        {
            free(s1);
            free(s2);
            return p;
        }
        free(s1);
        free(s2);
    }

    return n;
}