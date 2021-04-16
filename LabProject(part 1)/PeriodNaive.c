#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int periodNaiveMethod1(char *S)
{
    int n = strlen(S);
    int counter = 0;
    for (int p = 1; p <= n; p++)
    {
        int i;
        for (i = 0; i < n - p; i++){
            if (S[i] != S[i + p])
            {
                break;
            }
        }

        if(i == n - p)
        return p;
        
    }
    
}

//for più esterno da 1 a n-1, 
//
//


char *substring(char *S, int a, int b){
    int l=b-a;
    char *s=(char *)malloc((l+1)*sizeof(char)); //quell' l+1 serve perche ho un carattere
                                                //in più che è lo 0
    int i=0;                                            
    while(i<l){
        s[i]=S[a+i];
        i++;
    }
    s[i]='\0';
    return s;
    
}

int periodNaiveMethod2(char *S){      //è giusto, gli indici son giusti
     int n= strlen(S);
     for(int p=1; p<=n-1; p++){
         char *s1= substring(S,0,n-p);
         char *s2= substring(S,p,n);
         if(strcmp(s1,s2)==0){
             free(s1);
             free(s2);
             return p;
             
         }
         free(s1);
         free(s2);
     }
     
     return n;
}



int main(){
  char S[1000];
  scanf("%999s", S);
  int p=periodNaiveMethod2(S);
  printf("%d", p);
  return 0;

}





/*int main(){
  char S[1000];
  scanf("%999s", S);
  int p=periodNaiveMethod1(S);
  //int p = periodNaive(S);
  printf("%d", p);
  return 0;

}
*/

