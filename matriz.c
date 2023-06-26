#include <stdio.h>

int pMatriz(int l, int c){
    int m[l][c],n1=1,n2=1,aux;
    for (int i=0;i<l;i++){
        for (int j=0;j<c;j++){
            if (i==0 && j==0 || i==0 && j==1){
                m[i][j]=1;
            }
            else{
                aux=n1;
                m[i][j]=n1+n2;
                n1=m[i][j];
                n2=aux;
            }
        }
    }
    for (int i=0;i<l;i++){
        for (int j=0; j<c;j++){
            if (j==c-1){
                printf("%d",m[i][j]);
            }else{
                printf("%d, ", m[i][j]);
            }
        }
        printf("\n");
    }
}

int main(){
    int l,c;
    printf("Digite a altura da matriz:");
    scanf("%d", &l);
    printf("Digite o comprimento da matriz:");
    scanf("%d",&c);
    pMatriz(l,c);

    return 0;
}