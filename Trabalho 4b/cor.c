#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void readtxt(float pontos[5], char nomes[5][20]){
  FILE *arq = fopen("./tabela.txt","r");
  if (arq == NULL){
    for (int i=0;i<5;i++){
      pontos[i]=0;
      nomes[i][0]='A';
      nomes[i][1]='\0';
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
  default:
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
  pontos = (dischu/madis)*100;
  return pontos;
}

float pontmed(float ponto1[3], double tempo){
  float total=0, bonus=1;
  bonus=bonus* 0.05 * (20-tempo); 
  total = (100-(ponto1[0]+ponto1[1]+ponto1[2])/3);
  total += total * bonus;
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
  tela_limpa();
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
  tela_limpa();
}

int final(float *ponto, float pontos[5], char nomes[5][20], int continuar){
  ordena(*ponto,pontos,nomes);
  mplacar(nomes,pontos);
  while(tela_le_char()!=c_enter);
  tela_limpa();
  printf("Deseja continuar jogando? \n1 - Sim   |   2 - Não\n");
  scanf("%d", &continuar);
  writetxt(pontos,nomes);
  return continuar;
}

void inicia(float pontos[5], char nomes[5][20]){
  srand(time(0));
  tela_cria();  
  tela_limpa();
  tela_mostra_cursor(false);
  readtxt(pontos,nomes);
}

void choosebar(placar *pontuacao){
  switch (pontuacao->cor){
    case 1:
      pontuacao->user.vermelho=jogada(10,pontuacao->v,0);
      break;
    case 2:
      pontuacao->user.verde=jogada(12,pontuacao->v,1);
      break;
    case 3: 
      pontuacao->user.azul=jogada(14,pontuacao->v,2);
      break;
    default:
      break;
  }
  return;
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

void finalcalc(placar *pontuacao){
  pontuacao->ponto1[0]=calcpontos(pontuacao->user.vermelho, pontuacao->random.vermelho);
  pontuacao->ponto1[1]=calcpontos(pontuacao->user.verde, pontuacao->random.verde);
  pontuacao->ponto1[2]=calcpontos(pontuacao->user.azul, pontuacao->random.azul);
  pontuacao->ponto=pontmed(pontuacao->ponto1,pontuacao->tempo);
}

void jogando(placar *pontuacao){
  do {
      pontuacao->tempo = tela_relogio() - pontuacao->inicio;
      desenhatela(pontuacao->tempo,pontuacao->user,pontuacao->random, pontuacao->inicio);
      int lugar=tela_le_char();
      switch (lugar)
      {
      case c_up:
        if (pontuacao->cor>1){
          pontuacao->cor--;
        }
        break;
      case c_down:
        if (pontuacao->cor<3){
          pontuacao->cor++;
        }
      default:
        break;
      }
      choosebar(&(*pontuacao));
  }while (pontuacao->tempo <= 20);
}

int main(){
  placar pontuacao;
  int continuar=1;
  while (continuar==1){
    inicia(pontuacao.pontos,pontuacao.nomes);    
    atribuir(&pontuacao);
    jogando(&pontuacao);
    finalcalc(&pontuacao);
    desenhafim(pontuacao.user,pontuacao.random,pontuacao.ponto);  
    continuar=final(&(pontuacao.ponto),pontuacao.pontos, pontuacao.nomes, continuar);
  }
  tela_limpa();
  system("clear");
}