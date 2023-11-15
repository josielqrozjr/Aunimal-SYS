#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

void solicitar_dados(){

  int cpf;
  char cliente[MAX_STRING];
  char pet[MAX_STRING];
  char data_check_in[MIN_STRING];
  char data_checkout[MIN_STRING];
  char descricao[MAX_STRING];
  float valor_reserva;
  
  printf("Digite o nome do cliente: ");
  scanf("%s", cliente);
  printf("Digite o CPF do cliente: ");
  scanf("%d", &cpf);
  printf("Digite o nome do pet: ");
  scanf("%s", pet);
  printf("Digite a data de check-in: ");
  scanf("%s", data_check_in);
  printf("Digite a data de check-out: ");
  scanf("%s", data_checkout);
  printf("Digite a descrição da reserva: ");
  scanf("%s", descricao);
  printf("Digite o valor da reserva: ");
  scanf("%f", &valor_reserva);

  return;
  
}






int main(void){

  

  return 0;
}