#include <stdio.h> 

 void impressaoRec (long long n){

    if (n==1){
        printf ("1");
    }
    else{
        printf ("%lld \n", n);
        impressaoRec (n -1);
    }
}
int main (){
    long long n;
    printf("Digite um numero: ");
    scanf("%lld", &n);
    impressaoRec (n);
    return 0;
}