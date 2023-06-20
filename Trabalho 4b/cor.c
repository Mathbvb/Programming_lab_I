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
  float ponto1[3];
  float ponto;
  float pontos[5];
  char nomes[5][20];
  int v[3];
  int cor;
  double inicio;
  double tempo;
  cor user;
  cor random;
} placar;

const cor RED={5,0,0};
const cor GREEN={0,5,0};
const cor BLUE={0,0,5};
const cor WHITE={255,255,255};

void poslincol(int lin, int col){
  posicao pos={lin,col};
  tela_posiciona(pos);
}

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
    for (int i=0;i<5;i++){
      pontos[i]=0;
    }
    return;
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

void quadrado(cor cores, int col){
  tela_cor_fundo(cores);
  for (int i=0;i<5;i++){
    poslincol(i+3,col);
    printf("          ");
  }
  tela_cor_normal();
}

void bar(cor desbar){
  for (int i=1;i<53;i++){
    cor desbar2={i*desbar.vermelho, i*desbar.verde, i*desbar.azul};
    tela_cor_fundo(desbar2);
    putchar(' ');
  }
  tela_cor_normal();
}

void playbar(){
  poslincol(10,1);
  bar(RED);
  poslincol(12,1);
  bar(GREEN);
  poslincol(14,1);
  bar(BLUE);
}

int jogada(int pr,int v[3], int i){
  poslincol(pr,v[i]);
  tela_cor_fundo(WHITE);
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
    madis=0;
  } else {
    madis=255;
  }
  pontos = (madis/100)*dischu;
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

void desenhatela(double tempo, cor user, cor random, double inicio){
  tela_cor_normal();
  tela_limpa();
  poslincol(1, 1);
  printf("%.1lf", tempo);
  quadrado(random,2);
  playbar();
  quadrado(user,20);
}

void desenhafim(cor user,cor random, float ponto){
  tela_limpa();
  poslincol(1,2);
  printf("Cor sorteada:");
  quadrado(random,2);
  poslincol(1,20);
  printf("Sua cor:");
  quadrado(user,20);
  poslincol(10,2);
  printf("Você conseguiu %.2f pontos!", ponto);
  poslincol(12,2);
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

void atribuir(placar *pontuacao){
  pontuacao->random.vermelho=(rand()%52)*5;
  pontuacao->random.verde=(rand()%52)*5; 
  pontuacao->random.azul=(rand()%52)*5;
  pontuacao->user.vermelho=0;
  pontuacao->user.verde=0;
  pontuacao->user.azul=0;
  pontuacao->cor=1;
  pontuacao->v[0]=1;
  pontuacao->v[1]=1;
  pontuacao->v[2]=1;
  pontuacao->inicio = tela_relogio();
  pontuacao->tempo=0;
}

void finalcalc(float ponto1[3], cor user, cor random, double tempo,float *ponto){
  ponto1[0]=calcpontos(user.vermelho, random.vermelho);
  ponto1[1]=calcpontos(user.verde, random.verde);
  ponto1[2]=calcpontos(user.azul, random.azul);
  *ponto=pontmed(ponto1,tempo);
}

void jogando(placar pontuacao, cor *user, double tempo, double inicio, cor random){
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
      else {choosebar(pontuacao.v,&(pontuacao.cor),&(user->vermelho),&(user->verde),&(user->azul),10,12,14);
        }
  }while (tempo <= 20);
}

int main(){
  placar pontuacao;
  int continuar=1;
  while (continuar==1){
    inicia(pontuacao.pontos,pontuacao.nomes);    
    atribuir(&pontuacao);
    jogando(pontuacao, &(pontuacao.user), pontuacao.tempo, pontuacao.inicio, pontuacao.random);
    finalcalc(pontuacao.ponto1,pontuacao.user,pontuacao.random,pontuacao.tempo,&(pontuacao.ponto));
    desenhafim(pontuacao.user,pontuacao.random,pontuacao.ponto);  
    continuar=final(&(pontuacao.ponto),pontuacao.pontos, pontuacao.nomes, continuar);
  }
  tela_limpa();
}