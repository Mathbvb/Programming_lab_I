#include <stdio.h>


float opera(char op, float n1, float n2){
  float total;
  switch (op){
    case '+': total = n1 + n2;
    case '-': total = n1 - n2;
    case '*': total = n1 * n2;
    case '/': total = n1 / n2;
  }
  return total;
}

float calculadora(){
  float n1, n2, total = 0;
  char op, op2 ='+';

  scanf("%f", &n1);
  do{
    scanf("%c", &op);
    scanf("%f", &n2);
    if (op == '+' || op == '-'){
      total = opera(op2, total, n1);
      n1 = n2;
      op2 = op;
    }
    else if (op == '*' || op == '/'){
      n1 = opera(op, n1, n2);
    }
  } while (op != '=');

  if (op2 == '+' || op2 == '-'){
    total = opera(op2, total, n1);
  }
  return total;
}

int main(void) {
  float total;
  printf("Calculadora de operações básicas.\n");
  total = calculadora();
  printf("Resultado: %.2f\n", total);
  return 0;
}