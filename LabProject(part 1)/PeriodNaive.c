#include <stdio.h>
#include <string.h>
#include <time.h>

int main(){
    
    char S[1000];
    scanf("%999s", S);
    int p=periodNaive(S);
    printf("%d", p);
    return 0;
}


int periodNaive(char *S){

    int n = strlen(S);
    for(int p=1; p<=n;p++){
        for(int i=1; i<=n; i++){
            if(S[i] == S[i+p]){
                return p;
                } else {
                    return 0;
                }
            }
        }
}
