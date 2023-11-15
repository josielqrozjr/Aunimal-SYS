#include <stdio.h>
#include <stdlib.h>

#include "lista.h"


// Função para solicitar ao usuário que informe os dados de uma reserva
Reserva *solicitar_dados(void){

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
  getchar();  // Limpar o buffer

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

  // Armazenar os dados da reserva
  Reserva *reserva = registrar_reserva(cpf, cliente, pet, data_check_in, data_checkout, descricao, valor_reserva);

  return reserva; // Retornar os dados inseridos pelo usuário
}


// Função para abrir o arquivo binário e retornar numa lista encadeada
Lista_encadeada *abrir_arquivo_binario(const char *nome_arquivo){
  
  // Abre o arquivo binário para leitura
  FILE *arquivo_binario = fopen(nome_arquivo, "rb");
  if (arquivo_binario == NULL) 
  { puts("Erro na abertura do arquivo"); exit(1); } 

  Reserva *reserva;
  
  // Criar a lista encadeada
  Lista_encadeada *lista = criar_lista_encadeada();
  
  // Ler os dados do arquivo binário e insere na lista encadeada
  while (fread(&reserva, sizeof(Reserva), 1, arquivo_binario) == 1) {
    InserirRegistroOrdenado(lista, reserva);
  }
  // Fechar o arquivo binário
  fclose(arquivo_binario);  

  return lista;
}


int main(void){

  Lista_encadeada *lista_nova_reserva = abrir_arquivo_binario("binario.bin");

  Reserva *nova_reserva = solicitar_dados();
  
  // Registrar dados da nova reserva na lista anterior
  InserirRegistroOrdenado(lista_nova_reserva, nova_reserva);
  
  // Gravar os dados da lista no arquivo binário
  gravar_lista_encadeada("binario.bin", lista_nova_reserva);

  // Destruir a lista encadeada
  excluir_lista_encadeada(lista_nova_reserva);


  return 0;
}