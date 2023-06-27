#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>




void sorteia(char matriz[5][5]){
        srand(time(0));
    int sort = rand()%4, posl=rand()%5, posc=rand()%5,i=0;
    while (matriz[posl][posc] != '0'){
        posl=rand()%5;
        posc=rand()%5;
        if (i>=25){
            break;
        }
        i++;
    }
    if (sort == 3){
        matriz[posl][posc] = 'B';
    }
    else{
        matriz[posl][posc] = 'A';
    }
}

void preenchem(char matriz[5][5]){
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            matriz[i][j]='0';
        }
    }
    for (int i=0;i<15;i++){
        sorteia(matriz);
    }
}

void imprime_matriz(char matriz[5][5]){
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            printf("%c",matriz[i][j]);
        }
        printf("\n");
    }
}

void transcreve(char matriz[5][5]){
    char nm[5][5];
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            nm[j][i]=matriz[i][j];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            matriz[i][j]=nm[i][j];
        }
    }
}

void invertelr(char matriz[5][5]){
    char aux[5][5];
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            aux[i][j]=matriz[i][5-j-1];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            matriz[i][j]=aux[i][j];
        }
    }
}

void movelr(char matriz[5][5]){
    for (int i=0;i<5;i++){
        int aux=0;
        for (int j=0;j<5;j++){
            if (matriz[i][j]!='0'){
                matriz[i][aux]=matriz[i][j];
                if(j>aux){
                    matriz[i][j]='0';
                }
            aux++;
            }
        }
    }
}

void jp(char matriz[5][5],int i,int j, char aux){
    switch (aux){
    case 'A':
        matriz[i][j]='B';
        break;
    case 'B':
        matriz[i][j]='C';
        break;
    case 'C':
        matriz[i][j]='D';
        break;
    case 'D':
        matriz[i][j]='E';
        break;
    case 'E':                
        matriz[i][j]='F';
        break;
    }
}

void juntalr(char matriz[5][5]){
    char aux;
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            if(matriz[i][j]==matriz[i][j+1] && matriz[i][j]==matriz[i][j+2]){
                aux=matriz[i][j];
                jp(matriz,i,j,aux);
                matriz[i][j+1]='0';
                matriz[i][j+2]='0';
            }
        }
    }
}



void clickleft(char matriz[5][5]){
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
}

void clickup(char matriz[5][5]){
    imprime_matriz(matriz);
        printf("\n\n");
    transcreve(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    transcreve(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
}

void clickright(char matriz[5][5]){
    imprime_matriz(matriz);
        printf("\n\n");
    invertelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    invertelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
}

void clickdown(char matriz[5][5]){
    imprime_matriz(matriz);
        printf("\n\n");
    transcreve(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    invertelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    movelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    juntalr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    invertelr(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
    transcreve(matriz);
    imprime_matriz(matriz);
        printf("\n\n");
}

int main(){
    char matriz[5][5];
    preenchem(matriz);
    clickdown(matriz);

    return 0;
}