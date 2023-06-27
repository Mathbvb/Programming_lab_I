#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "tela.h"
#include <string.h>

typedef struct {
    char matrizl[5][5];
    double pontos;
    int cf;
    int cb;
    int fa, fb, fc, fd, fe, ff;
    char maior_pontos[5][20];
    double mpontos[5];
} val;

#define fundo tela_cria_cor(255.0/255.0,210.0/255.0,97.0/255.0);
#define borda tela_cria_cor(222.0/255.0,101.0/255.0,27.0/255.0);
#define fundoa tela_cria_cor(240.0/255.0,150.0/255.0,34.0/255.0);
#define fundob tela_cria_cor(217.0/255.0,203.0/255.0,20.0/255.0);
#define fundoc tela_cria_cor(23.0/255.0,252.0/255.0,23.0/255.0);
#define fundod tela_cria_cor(217.0/255.0,29.0/255.0,20.0/255.0);
#define fundoe tela_cria_cor(189.0/255.0,66.0/255.0,250.0/255.0);
#define fundof tela_cria_cor(85.0/255.0,60.0/255.0,250.0/255.0);


void desenhafundo(int cf){
    tela_retangulo(0,0,1280,720,5,cf,cf);
}

void desenhabotao(float x, float y, int cb, float com, float alt){
    tela_retangulo(x,y,x+com,y+alt,5,cb,cb);
}

int corfundoquad(val valores, int i, int j){
    char l = valores.matrizl[i][j];
    switch (l){
        case 'A':
            return valores.fa;
            break;
        case 'B':
            return valores.fb;
            break;
        case 'C':
            return valores.fc;
            break;
        case 'D':
            return valores.fd;
            break;
        case 'E':
            return valores.fe;
            break;
        case 'F':
            return valores.ff;
            break;
    }
    return 0;
}

void desenhaquadrado(val valores){
    int cf;
    float x=360,y=80;
    for(int j=0;j<5;j++){
        for (int i=0;i<5;i++){
            cf = corfundoquad(valores,j,i);
            tela_retangulo(x+115*i,y+115*j,x+115*i+115,y+115*j+115,3,valores.cb,cf);
        }
    }
}

void imprime_matriz(char matriz[5][5], int cb){
    float x=418,y=135;
    char v[2];
    v[1]='\0';
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            v[0] = matriz[i][j];
            tela_texto(x+115*j,y+115*i,90,cb,v);
        }
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
            if (matriz[i][j]!=' '){
                matriz[i][aux]=matriz[i][j];
                if(j>aux){
                    matriz[i][j]=' ';
                }
            aux++;
            }
        }
    }
}

void jp(char matriz[5][5],double *pontos,int i,int j, char aux, int cb, int cf){
    switch (aux){
    case 'A':
        matriz[i][j]='B';
        *pontos+=30;
        break;
    case 'B':
        matriz[i][j]='C';
        *pontos+=90;
        break;
    case 'C':
        matriz[i][j]='D';
        *pontos+=270;
        break;
    case 'D':
        matriz[i][j]='E';
        *pontos+=810;
        break;
    case 'E':                
        matriz[i][j]='F';
        *pontos+=2430;
        game(*pontos,cb,cf,true);
        break;
    }
}

void juntalr(char matriz[5][5],double *pontos, int cb, int cf){
    char aux;
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            if(matriz[i][j]==matriz[i][j+1] && matriz[i][j]==matriz[i][j+2]){
                aux=matriz[i][j];
                jp(matriz,&(*pontos),i,j,aux, cb, cf);
                matriz[i][j+1]=' ';
                matriz[i][j+2]=' ';
            }
        }
    }
}

double addponto(double pontos){
    pontos += 1;
    return pontos;
}

void clickleft(char matriz[5][5], double *pontos, int cb, int cf){
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    *pontos=addponto(*pontos);
}

void clickup(char matriz[5][5], double *pontos, int cb, int cf){
    transcreve(matriz);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    transcreve(matriz);
    *pontos=addponto(*pontos);
}

void clickright(char matriz[5][5],double *pontos, int cb, int cf){
    invertelr(matriz);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    invertelr(matriz);
    *pontos=addponto(*pontos);
}

void clickdown(char matriz[5][5], double *pontos, int cb, int cf){
    transcreve(matriz);
    invertelr(matriz);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf);
    invertelr(matriz);
    transcreve(matriz);
    *pontos=addponto(*pontos);
}

void sorteia(char matriz[5][5]){
    srand(time(0));
    int sort = rand()%4, posl=rand()%5, posc=rand()%5,i=0;
    while (matriz[posl][posc] != ' '){
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

bool matriz_cheia(char matriz[5][5]){
    bool cheia = true;
    for (int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if (matriz[i][j]==' '){
                cheia = false;
            }
        }
    }
    return cheia;
}

bool temF(char matriz[5][5]){
    bool haveF = false;
    for (int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if (matriz[i][j]=='F'){
                haveF = true;
            }
        }
    }
    return haveF;
}

void iniciaval(val *valores){
    valores->pontos = 0;
    for(int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            valores->matrizl[i][j]=' ';
        }
    }
    for (int i=0;i<3;i++){
        sorteia(valores->matrizl);
    }
    valores->cb = borda;
    valores->cf = fundo;
    valores->fa = fundoa;
    valores->fb = fundob;
    valores->fc = fundoc;
    valores->fd = fundod;
    valores->fe = fundoe;
    valores->ff = fundof;
}

void placar(){}

void imp_tela(double pontos, int cb){
    char buf[8];
    sprintf(buf,"%.1f", pontos);
    tela_texto(860,40,60,cb,buf);
}

void desenhatela(val valores){
    desenhafundo(valores.cf);
    imp_tela(valores.pontos, valores.cb);
    desenhaquadrado(valores);
    imprime_matriz(valores.matrizl, valores.cb);
}

void desenha_inicio(int cor_logo, int cor_texto, int pos){
    char logo[4]={"EFE\0"}, jogar[7]={"Jogar\0"}, inst[35]={"Combine 3 letras iguais de A a F\0"}, lplac[8]={"Placar\0"};
    desenhafundo(cor_logo);
    tela_texto(640,120,120,cor_texto,logo);
    tela_texto(640,650,40,cor_texto,inst);
    if (pos==0){
        desenhabotao(384,290,cor_texto,512,144);
        tela_texto(640,360,70,cor_logo,jogar);
        desenhabotao(420,460,cor_texto,440,110);
        tela_texto(640,510,50,cor_logo,lplac);
    }
    else{
        desenhabotao(420,290,cor_texto,440,110);
        tela_texto(640,340,50,cor_logo,jogar);
        desenhabotao(384,460,cor_texto,512,144);
        tela_texto(640,530,70,cor_logo,lplac);
    }
}

void inicio(int cor_logo, int cor_texto){
    int pos = 0;
    while(true){
        desenha_inicio(cor_logo,cor_texto, pos);
        int tecla = tela_tecla();
        switch (tecla){
            case c_up:
                if(pos>0){
                    pos--;
                }
                break;
            case c_down:
                if(pos==0){
                    pos++;
                }
                break;
            case c_enter:
                if(pos == 0){
                    return;
                }
                else{
                    placar();
                }
        }
        tela_atualiza();
    }
}

void desenhafim(double pontos, int cb, int cf, bool vencedor){
    char buf[8], ponto[16]={"Pontos: "},fechar[15]={"Fechar - Enter\0"};
    sprintf(buf,"%.1f", pontos);
    strcat(ponto,buf);
    desenhafundo(cf);
    if (vencedor==true){
        char venceu[25]={"Parabéns você venceu!\0"};
        tela_texto(640,180,100,cb,venceu);
    }
    else{
        char venceu[25]={"Você perdeu"};
        tela_texto(640,180,100,cb,venceu);
    }
    tela_texto(640,260,70,cb,ponto);
    desenhabotao(384,330,cb,512,144);
    tela_texto(640,400,60,cf,fechar);
}

void game(double pontos, int cb, int cf, bool venceu){
    while (true){
        desenhafim(pontos, cb, cf,venceu);
        int tecla = tela_tecla();
        switch(tecla){
            case c_enter:
                return;
        }
        tela_atualiza();
    }
}

void tela_acaba(val valores){
    game(valores.pontos,valores.cb,valores.cf,false);
}

void jogo(val valores){
    while (true){        
        desenhatela(valores);
        int tecla = tela_tecla();
        switch (tecla){
        case c_up:
            clickup(valores.matrizl,&(valores.pontos),valores.cb,valores.cf);
            sorteia(valores.matrizl);
            break;
        case c_down:
            clickdown(valores.matrizl,&(valores.pontos),valores.cb,valores.cf);
            sorteia(valores.matrizl);
            break;
        case c_left:
            clickleft(valores.matrizl,&(valores.pontos),valores.cb,valores.cf);
            sorteia(valores.matrizl);
            break;
        case c_right:
            clickright(valores.matrizl,&(valores.pontos),valores.cb,valores.cf);
            sorteia(valores.matrizl);
            break;
        case c_back:
            return;
        }
        tela_atualiza();
        bool cheia = matriz_cheia(valores.matrizl);
        if (cheia == true){
            tela_acaba(valores);
            return;
        }
    }
}

int main()
{
    tela_inicio(1280,720,"EFE");
    val valores;   
    iniciaval(&valores);

    inicio(valores.cf, valores.cb);
    jogo(valores);

    tela_fim();
    return 0;
}