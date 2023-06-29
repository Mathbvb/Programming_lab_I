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
    char maior_pontos[5][21];
    double mpontos[5];
} val;

#define fundo tela_cria_cor(255.0/255.0,210.0/255.0,97.0/255.0);
#define borda tela_cria_cor(225.0/255.0,80.0/255.0,31.0/255.0);
#define fundoa tela_cria_cor(240.0/255.0,150.0/255.0,34.0/255.0);
#define fundob tela_cria_cor(217.0/255.0,203.0/255.0,20.0/255.0);
#define fundoc tela_cria_cor(23.0/255.0,252.0/255.0,23.0/255.0);
#define fundod tela_cria_cor(217.0/255.0,29.0/255.0,20.0/255.0);
#define fundoe tela_cria_cor(189.0/255.0,66.0/255.0,250.0/255.0);
#define fundof tela_cria_cor(85.0/255.0,60.0/255.0,250.0/255.0);

void game(double pontos, int cb, int cf, bool venceu,double mpontos[5],char maior_pontos[5][21]);

void readtxt(double mpontos[5], char maior_pontos[5][21]){
  FILE *arq = fopen("./tabela.txt","r");
  if (arq == NULL){
    for (int i=0;i<5;i++){
      mpontos[i]=0;
      maior_pontos[i][0]='A';
      maior_pontos[i][1]='\0';
    }
    return;
  }
  for (int i=0; i<5;i++){
    fscanf(arq,"%lf %s",&mpontos[i],maior_pontos[i]);
  }
  fclose(arq);
}

void writetxt(double mpontos[5], char maior_pontos[5][21]){
  FILE *arq = fopen("./tabela.txt","w");
  for (int i=0; i<5;i++){
    fprintf(arq,"%.1f %s\n",mpontos[i],maior_pontos[i]);
  }
  fclose(arq);
}

void ordena(double mpontos[5],char maior_pontos[5][21]){
    double aux;
    char nomeaux[21];
    for (int i=0;i<5;i++){
        for (int j=i;j<5;j++){
            if (mpontos[j]>mpontos[i]){
                aux=mpontos[i];
                mpontos[i]=mpontos[j];
                mpontos[j]=aux;
                strcpy(nomeaux,maior_pontos[i]);
                strcpy(maior_pontos[i],maior_pontos[j]);
                strcpy(maior_pontos[j],nomeaux);
            }
        }
    }
}

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

void jp(char matriz[5][5],double *pontos,int i,int j, char aux, int cb, int cf,double mpontos[5],char maior_pontos[5][21]){
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
        game(*pontos,cb,cf,true,mpontos,maior_pontos);
        break;
    }
}

void juntalr(char matriz[5][5],double *pontos, int cb, int cf,double mpontos[5],char maior_pontos[5][21]){
    char aux;
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            if(matriz[i][j]==matriz[i][j+1] && matriz[i][j]==matriz[i][j+2]){
                aux=matriz[i][j];
                jp(matriz,&(*pontos),i,j,aux, cb, cf,mpontos,maior_pontos);
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

void clickleft(char matriz[5][5], double *pontos, int cb, int cf,double mpontos[5],char maior_pontos[5][21]){
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
    *pontos=addponto(*pontos);
}

void clickup(char matriz[5][5], double *pontos, int cb, int cf,double mpontos[5],char maior_pontos[5][21]){
    transcreve(matriz);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
    transcreve(matriz);
    *pontos=addponto(*pontos);
}

void clickright(char matriz[5][5],double *pontos, int cb, int cf,double mpontos[5],char maior_pontos[5][21]){
    invertelr(matriz);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
    invertelr(matriz);
    *pontos=addponto(*pontos);
}

void clickdown(char matriz[5][5], double *pontos, int cb, int cf,double mpontos[5],char maior_pontos[5][21]){
    transcreve(matriz);
    invertelr(matriz);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
    movelr(matriz);
    juntalr(matriz,&(*pontos),cb,cf,mpontos,maior_pontos);
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

bool verifica_move(char matriz[5][5]){
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            if(matriz[i][j]==matriz[i][j+1] && matriz[i][j]==matriz[i][j+2]){
                return false;
            }
        }
    }
    return true;
}

bool espelha(char matriz[5][5]){
    bool moves;
    char matriz_aux[5][5];
    for (int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            matriz_aux[i][j]=matriz[i][j];
        }
    }
    moves = verifica_move(matriz_aux);
    if (moves == false){ 
        return moves;
    }
    else{
        invertelr(matriz_aux);
        moves = verifica_move(matriz_aux);
        return moves;
    }
}

bool matriz_move(char matriz[5][5]){
    bool cheia = true;
    for (int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if (matriz[i][j]==' '){
                cheia = false;
            }
        }
    }
    if (cheia == true){
        cheia=espelha(matriz);
    }
    return cheia;
}

void desenha_placar(val valores){
    char buf[8],nom[22]={"Melhores Pontuações\0"};
    tela_retangulo(0,0,1280,720,5,valores.cf,valores.cf);
    tela_texto(640,80,100,valores.cb,nom);
    for(int i=0;i<5;i++){
        tela_texto(320,200+i*100,60,valores.cb,valores.maior_pontos[i]);
        sprintf(buf,"%.1f", valores.mpontos[i]);
        tela_texto(960,200+i*100,60,valores.cb,buf);
    }
}

void placar(val valores){
    ordena(valores.mpontos, valores.maior_pontos);
    while(true){
        int tecla = tela_tecla();
        desenha_placar(valores);
        if(tecla==c_esc){
            return;
        }
        tela_atualiza();
    }
}

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

void desenha_attplacar(int cb, int cf){
    char nr[12]={"Parabéns!\0"},nrr[26]={"Você quebrou um recorde!\0"};
    tela_retangulo(0,0,1280,720,5,cf,cf);
    tela_texto(640,100,100,cb,nr);
    tela_texto(640,200,55,cb,nrr);
}

void passa(char maior_pontos[5][21],int cb){
    char nm[21];
    for(int i=0;i<21;i++){
        nm[i]=maior_pontos[4][i];
    }
    tela_texto(640,400,60,cb,nm);
}

void attplacar(char maior_pontos[5][21],int cf, int cb){
    maior_pontos[4][0]='\0';
    int tam=0;
    while(true){
        desenha_attplacar(cb,cf);
        int tecla = tela_tecla();
        switch (tecla){
            case c_back:
                if(tam>0){
                    maior_pontos[4][tam-1]='\0';
                    tam--;
                }
                break;
            case c_enter:
                return;
            case c_none:
                passa(maior_pontos,cb);
                break;
            default:
                if (tam<20){
                maior_pontos[4][tam]=tecla;
                tam++;
                }
                break;
        }
        tela_atualiza();
    }
}

void desenhafim(double pontos, int cb, int cf, bool vencedor){
    char buf[8], ponto[16]={"Pontos: "},fechar[7]={"Fechar\0"};
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

void game(double pontos, int cb, int cf, bool venceu, double mpontos[5],char maior_pontos[5][21]){
    while (true){
        desenhafim(pontos, cb, cf,venceu);
        int tecla = tela_tecla();
        switch(tecla){
            case c_enter:
            if(pontos>mpontos[4]){
                mpontos[4]=pontos;
                attplacar(maior_pontos,cf,cb);
            }
                return;
        }
        tela_atualiza();
    }
}

void tela_acaba(val valores){
    game(valores.pontos,valores.cb,valores.cf,false,valores.mpontos,valores.maior_pontos);
}

void jogo(val valores){
    while (true){        
        desenhatela(valores);
        int tecla = tela_tecla();
        switch (tecla){
        case c_up:
            clickup(valores.matrizl,&(valores.pontos),valores.cb,valores.cf,valores.mpontos,valores.maior_pontos);
            sorteia(valores.matrizl);
            break;
        case c_down:
            clickdown(valores.matrizl,&(valores.pontos),valores.cb,valores.cf,valores.mpontos,valores.maior_pontos);
            sorteia(valores.matrizl);
            break;
        case c_left:
            clickleft(valores.matrizl,&(valores.pontos),valores.cb,valores.cf,valores.mpontos,valores.maior_pontos);
            sorteia(valores.matrizl);
            break;
        case c_right:
            clickright(valores.matrizl,&(valores.pontos),valores.cb,valores.cf,valores.mpontos,valores.maior_pontos);
            sorteia(valores.matrizl);
            break;
        case c_esc:
            tela_acaba(valores);
            return;
        }
        tela_atualiza();
        bool acaba = matriz_move(valores.matrizl);
        if (acaba == true){
            tela_acaba(valores);
            return;
        }
    }
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

void inicio(val valores){
    int pos = 0;
    while(true){
        desenha_inicio(valores.cf,valores.cb, pos);
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
                    jogo(valores);
                }
                else{
                    placar(valores);
                }
                break;
            case c_esc:
                return;
        }
        tela_atualiza();
    }
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
    readtxt(valores->mpontos,valores->maior_pontos);
}

int main()
{
    tela_inicio(1280,720,"EFE");
    val valores;   
    iniciaval(&valores);

    inicio(valores);

    writetxt(valores.mpontos,valores.maior_pontos);
    tela_fim();
    return 0;
}