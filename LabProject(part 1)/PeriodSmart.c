#include <stdio.h>
#include <string.h>
#include <time.h>

int periodSmart(char *S);

int main(){

  char S[1000];
  scanf("%999s", S);
  int p=periodSmart(S);
  printf("%d", p);
  return 0;

}

int periodSmart(char *S){
   
   int n=strlen(S);
   int r[n]; //r[0..n-1]  
   r[0]=0;
   for(int i=0; i<=n-2; i++){ 
      //calcolo r[i+1]
      int z=r[i];
      while (z>0 && S[z]!=S[i+1])   //r[i] = lunghezza del primo bordo del primo bordo di S[0..i], S[i] compreso
      {
          z=r[z];   
      }
      if (S[z]==S[i+1])  //metto r[i] al posto di r[i]+1 in quanto partendo da 0,  la lunghezza del bordo 
                            //sarà gia l'indice del carattere successivo all'ultimo carattere del bordo
                        
      {
          r[i+1]=z+1;
      }else{        

          r[i+1]=0;
      }
    }
    return n-r[n-1];
}