#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void cfundo(int r,int g,int b){
  printf("\e[48;2;%d;%d;%dm",r,g,b);
}
void corn(){
  printf("\e[m");
}
void corl(int r, int g, int b){
  printf("\e[38;2;%d;%d;%dm",r,g,b);
}

void pos(int lin, int col){
  printf("\e[%d;%dH", lin, col);
}

void quadrado(int r, int g, int b,int lin,int col){
  pos(lin,col);
  printf("Acerte as cores:");
  cfundo(r,g,b);
  for (int i=0;i<5;i++){
    pos(lin+i+1,col+1);
    printf("          ");
  }
  corn();
}

void quadradochute(int r, int g, int b,int lin,int col){
  pos(lin,col+18);
  printf("Chute anterior:");
  cfundo(r,g,b);
  for (int i=0;i<5;i++){
    pos(lin+i+1,col+19);
    printf("          ");
  }
  corn();
}

void ponto(float pontos, int lin, int col){
  pos(lin+18,col);
  if(pontos >= 80){
    corl(0,0,240);
    printf("Sua pontuação foi de: %.2f",pontos);
  }
  else if(pontos>=60 && pontos<80){
    corl(0,240,0);
    printf("Sua pontuação foi de: %.2f",pontos);
  }
  else{
    corl(240,0,0);
    printf("Sua pontuação foi de: %.2f",pontos);
  }
  corn();
}
void placar(int lin, int col, float pontos, int i){
  pos(lin+i+4,col);
  if(pontos>=80){
    corl(0,0,240);
    printf("%d. %.2f",i+1,pontos);
  }
  else if(pontos>=60 && pontos<80){
    corl(0,240,0);
    printf("%d. %.2f",i+1,pontos);
  }
  else{
    corl(240,0,0);
    printf("%d. %.2f",i+1,pontos);
  }
  corn();
}

void barra(int r, int g, int b, int lin, int col){
  pos(lin+12,col);
  for (int i=0;i<52;i++){
    if(r/5==i){
      corn();
    }
    else{
      cfundo(i*5,0,0);
    }
    printf(" ");
  }
  corn();
  pos(lin+14,col);
  for (int i=0;i<52;i++){
    if(g/5==i){
      corn();
    }
    else{
      cfundo(0,i*5,0);
    }
    printf(" ");
  }
  corn();
  pos(lin+16,col);
  for (int i=0;i<52;i++){
    if(b/5==i){
      corn();
    }
    else{
      cfundo(0,0,i*5);
    }
    printf(" ");
  }
  corn();
  printf("\n\n");
}



float jogada(int cr, int cb, int cg, int corj[3], int lin, int col){
  float dr, dg, db, pontos;
  pos(lin+7,col);
  printf("Valor de R:");
  pos(lin+8,col);
  printf("Valor de G:");
  pos(lin+9,col);
  printf("Valor de B:");
  pos(lin+7,col+11);
  scanf("%d", &corj[0]);
  pos(lin+8,col+11);
  scanf("%d", &corj[1]);
  pos(lin+9,col+11);
  scanf("%d", &corj[2]);
  if(corj[0]>255 || corj[1]>255 || corj[2]>255 || corj[0]<0 || corj[1]<0 || corj[2]<0){
    system("clear");
    pos(lin,col);
    printf("Digite valores válidos (entre 0 e 255)");
    getchar();
    return pontos;
  }
  dr = cr-corj[0]; dg=cg-corj[1]; db=cb-corj[2];
  if(dr<0){dr *= -1;}
  if(dg<0){dg *= -1;}
  if(db<0){db *= -1;}
  pontos = (dr+dg+db)/7.65;
  pontos = 100-pontos;
  barra(corj[0],corj[1],corj[2], lin, col);
  getchar();

  return pontos;
}


int main(){
  srand(time(0));
  int r, g, b, aux, continuar=1,lin=1,col=1;
  int corj[3];
  float pontos, ptotal;
  float mpontos[5];
  r=rand()%256; g=rand()%256; b=rand()%256;
  corj[0]=257;

  while(continuar==1){
    for (int i=0;i<5;i++){
      quadrado(r,g,b,lin,col);
      if(corj[0]!=257){
      quadradochute(corj[0],corj[1],corj[2],lin,col);
      }
      pontos = jogada(r,g,b, corj,lin,col);
      ponto(pontos, lin, col);
      mpontos[i]=pontos;
      getchar();
      system("clear");
    }
    for (int i=0;i<5;i++){
      for (int j=i;j<5;j++){
        if(mpontos[i]<mpontos[j]){
          aux = mpontos[i];
          mpontos[i]=mpontos[j];
          mpontos[j]=aux;
        }
      }
    }
    pos(lin,col);
    printf("Cor sorteada: %d, %d, %d", r,g,b);
    pos(lin+2,col);
    printf("Melhores pontuações: ");
    for (int i =0;i<3;i++){
      placar(lin,col,mpontos[i],i);
    }
    pos(lin+8,col);
    printf("Deseja continuar jogando?");
    pos(lin+9,col);
    printf("1 - Sim");
    pos(lin+9,col+9);
    printf("2 - Não");
    pos(lin+10,col);
    scanf("%d", &continuar);
    system("clear");
    corj[0]=257;
  }

  return 0;
}