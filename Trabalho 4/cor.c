#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Programa exemplo do uso das funções de tela.[ch]
// Além deste arquivo, necessita de tela.h e tela.c
//
// Para compilar:
//   gcc -Wall -o cassa cassa.c tela.c
//
// tente sobreviver à cerquinha assassina durante 10s

// funções auxiliares
typedef struct{
  int r;
  int g;
  int b;
} cores;

typedef struct{
  float ponto1[3];
  float ponto;
  float pontos[5];
  char nomes[5][20];
  int v[3];
  int cor;
} placar;

int max(int a, int b)
{
  return a>b ? a : b;
}

int abs(int a)
{
  return a<0 ? -a : a;
}

void readtxt(float pontos[5], char nomes[5][20]){
  FILE *arq = fopen("./tabela.txt","r");
  if (arq == NULL){
    fclose(arq);
  }
  for (int i=0; i<5;i++){
    fscanf(arq,"%f %s",&pontos[i],nomes[i]);
  }
  fclose(arq);
}

void writetxt(float pontos[5], char nomes[5][20]){
  FILE *arq = fopen("./tabela.txt","w");
  for (int i=0; i<5;i++){
    fprintf(arq,"%.2f %s\n",pontos[i],nomes[i]);
  }
  fclose(arq);
}

void quadrado(int r, int g, int b, int col){
  tela_cor_fundo(r,g,b);
  for (int i=0;i<5;i++){
    tela_lincol(i+3,col);
    printf("          ");
  }
  tela_cor_normal();
}

void bar(int r, int g, int b, int lt){
  for (int i=0;i<52;i++){
    if(lt/5==i){
      tela_cor_fundo(255,255,255);
      putchar(' ');
    }
    else{
      tela_cor_fundo(r*i,g*i,b*i);
      putchar(' ');
    }
  }
  tela_cor_normal();
}

void playbar(){
  tela_lincol(10,1);
  bar(5,0,0,260);
  tela_lincol(12,1);
  bar(0,5,0,260);
  tela_lincol(14,1);
  bar(0,0,5,260);
}

int jogada(int pr,int v[3], int i){
  tela_lincol(pr,v[i]);
  tela_cor_fundo(255,255,255);
  putchar(' ');
  tela_cor_normal();
  int tecla = tela_le_char();
  switch (tecla)  {
  case c_left:
    if (v[i]>1){
      v[i]--;
    }
    break;
  case c_right:
    if (v[i]<51){ 
      v[i]++;
    }
    break;
  }
  return (v[i]*5);
}

float calcpontos(int corj, int cor){ 
  int madis, dischu;
  float pontos;
  dischu=corj-cor;
  if(dischu<0){
    dischu*=-1;
  }
  if(cor>128){
    madis=cor;
  } else {
    madis=255-cor;
  }
  pontos = dischu/madis*100;
  return pontos;
}
float pontmed(float ponto1[3], double tempo){
  float total=0, bonus=1;
  if (tempo<20){
    for (int j=tempo;j<20;j++){
      bonus+=0.05;
    }
  }
  total = (100-(ponto1[0]+ponto1[1]+ponto1[2])/3)*bonus;
  return total;
}

void ordena(float ponto, float pontos[5],char nomes[5][20]){
  float aux;
  char nomeaux[20];
  if(ponto>pontos[4]){
    pontos[4]=ponto;
    printf("Digite seu nome:");
    scanf("%19s", nomes[4]);
  }
  for (int i=0;i<5;i++){
    for (int j=i;j<5;j++){
      if (pontos[j]>pontos[i]){
        aux=pontos[i];
        pontos[i]=pontos[j];
        pontos[j]=aux;
        strcpy(nomeaux,nomes[i]);
        strcpy(nomes[i],nomes[j]);
        strcpy(nomes[j],nomeaux);
      }
    }
  }
}

void mplacar(char nomes[5][20], float pontos[5]){
  system("clear");
  printf("Melhores pontuações:\n");
  for (int i=0;i<5;i++){
    printf("%d. ",i+1);
    printf("%.2f  ",pontos[i]);
    printf("%s\n",nomes[i]);
  }
}

void desenhatela(double tempo, cores user, cores random, double inicio){
  tela_cor_normal();
  tela_limpa();
  tela_lincol(1, 1);
  printf("%.1lf", tempo);
  quadrado(random.r,random.g,random.b,2);
  playbar();
  quadrado(user.r,user.g,user.b,20);
}

void desenhafim(cores user,cores random, float ponto){
  tela_limpa();
  tela_lincol(1,2);
  printf("Cor sorteada:");
  quadrado(random.r,random.g,random.b,2);
  tela_lincol(1,20);
  printf("Sua cor:");
  quadrado(user.r,user.g,user.b,20);
  tela_lincol(10,2);
  printf("Você conseguiu %.2f pontos!", ponto);
  tela_lincol(12,2);
  printf("Clique enter para continuar");
  tela_mostra_cursor(true);
  while (tela_le_char() != c_enter);
  tela_destroi();
  system("clear");
}

int final(float *ponto, float pontos[5], char nomes[5][20], int continuar){
  ordena(*ponto,pontos,nomes);
  mplacar(nomes,pontos);
  getchar();
  getchar();
  system("clear");
  printf("Deseja continuar jogando? \n1 - Sim   |   2 - Não\n");
  scanf("%d", &continuar);
  writetxt(pontos,nomes);
  return continuar;
}

void inicia(float pontos[5], char nomes[5][20]){
  srand(time(0));
  tela_cria();    // sempre tem que ser a primeira função de tela a ser chamada
  tela_limpa();
  tela_mostra_cursor(false);
  readtxt(pontos,nomes);
}

void choosebar(int v[3], int *cor, int *r, int *g, int *b, int jr, int jg, int jb){
  switch (*cor){
    case 1:
      *r=jogada(jr,v,0);
      break;
    case 2:
      *g=jogada(jg,v,1);
      break;
    case 3: 
      *b=jogada(jb,v,2);
      break;
  }
}

void atribuir(int *ur, int *ug, int *ub, int *rr, int *rg, int *rb, int *cor, int v[3]){
  *rr=(rand()%52)*5;
  *rg=(rand()%52)*5; 
  *rb=(rand()%52)*5;
  *ur=0;
  *ug=0;
  *ub=0;
  *cor=1;
  v[0]=1;
  v[1]=1;
  v[2]=1;
}

void finalcalc(float ponto1[3], cores user, cores random, double tempo,float *ponto){
  ponto1[0]=calcpontos(user.r, random.r);
  ponto1[1]=calcpontos(user.g, random.g);
  ponto1[2]=calcpontos(user.b, random.b);
  *ponto=pontmed(ponto1,tempo);
}

void jogando(placar pontuacao, cores *user, double tempo, double inicio, cores random){
  do {
      tempo = tela_relogio() - inicio;
      desenhatela(tempo,*user,random, inicio);
      int lugar=tela_le_char();
      if(lugar == c_up){
        if (pontuacao.cor>1){
          pontuacao.cor--;
        }
      }
      else if(lugar == c_down){
        if (pontuacao.cor<3){
          pontuacao.cor++;
        }
      }
      else if (lugar == c_enter){
        break;
      }
      else {choosebar(pontuacao.v,&(pontuacao.cor),&(user->r),&(user->g),&(user->b),10,12,14);
        }
  }while (tempo <= 20);
}

int main(){
  placar pontuacao; cores user; cores random;
  int continuar=1;
  while (continuar==1){
    inicia(pontuacao.pontos,pontuacao.nomes);    
    atribuir(&(user.r),&(user.g),&(user.b),&(random.r),&(random.g),&(random.b),&(pontuacao.cor),pontuacao.v);
    double inicio = tela_relogio(), tempo;
    jogando(pontuacao, &user, tempo, inicio, random);
    finalcalc(pontuacao.ponto1,user,random,tempo,&(pontuacao.ponto));
    desenhafim(user,random,pontuacao.ponto);  
    continuar=final(&(pontuacao.ponto),pontuacao.pontos, pontuacao.nomes, continuar);
  }
  tela_limpa();
}