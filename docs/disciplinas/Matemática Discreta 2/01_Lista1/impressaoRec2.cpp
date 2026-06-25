#include <stdio.h> 

void impressaoRec2 (long n, long i){
    if (i==n){
        printf ("%lld", n);
    }
    else{
        printf ("%lld + ", i);
        impressaoRec2 (n, i + 1);
    }
}
int main (){
    long long n;
    long long i = 0;
    printf("Digite um numero: ");
    scanf("%lld", &n);
    impressaoRec2 (n, i);
    return 0;
}