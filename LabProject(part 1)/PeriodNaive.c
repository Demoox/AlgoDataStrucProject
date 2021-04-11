#include <stdio.h>
#include <string.h>

int periodNaiveMethod1(char *S)
{
    int counter = 0;
    int n = strlen(S);
    for (int p = 0; p < n; p++)
    {
        for (int i = 0; i < n - p; i++)
            if (S[i] != S[i + p])
            {
                return p+i;
            }
    }
    
}


int periodNaive(char *S){
     int n= strlen(S);
     for(int p=1; p<=n; p++){ //forse n-1
         char *s1=substring(S,0,n-p);
         char *s2= substring(S,p,n-p);
         if(strcmp(s1,s2)==0){return p;}
            
     }
     return n;
     

}


int main(){
  char S[1000];
  scanf("%999s", S);
  int p=periodNaive(S);
  printf("%d", p);
  return 0;

}


