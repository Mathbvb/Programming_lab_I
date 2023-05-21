//programa que le 10 numeros e imprime os maiores que a media
#include <stdio.h>

void smedia(){
    float n[10], total=0;

for (int i=0; i<10; i++){
    printf("Digite um numero:\n");
    scanf("%f", &n[i]);
    total += n[i];
}
total = total/10;
for (int i = 0; i<10; i++){
    if(n[i]>total && i<9){
        printf("%.2f ,", n[i]);
    }
    else if (i==9 && n[i]>10){
        printf("%.2f", n[i]);
    }
}
}

int main(){
    smedia();
}