#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void binario_para_texto(const char *nome_arquivo, Lista_encadeada *lista){
  FILE *arquivo_texto = fopen(nome_arquivo, "w");
  if (arquivo_texto == NULL) {
      printf("Erro ao abrir/criar o arquivo texto para escrita.\n");
      return;
  }

  No *no = lista->primeiro;
  while (no != NULL) {

    fprintf(arquivo_texto, "%d", no->Reserva->cpf);
    fprintf(arquivo_texto, "%s", no->Reserva->cliente);
    fprintf(arquivo_texto, "%s", no->Reserva->pet);
    fprintf(arquivo_texto, "%s", no->Reserva->data_check_in);
    fprintf(arquivo_texto, "%s", no->Reserva->data_checkout);
    fprintf(arquivo_texto, "%s", no->Reserva->descricao);
    fprintf(arquivo_texto, "%f", no->Reserva->valor_reserva);

    no = no->proximo;
      
  }

  fclose(arquivo_texto);
}


  
int main(int argc, char* argv[]){
  if (argc != 2 )
  {
    puts("ERRO: numero incorreto de argumentos!");
    exit(1);
  }

// Abre o arquivo binario
FILE *arquivo_binario = fopen(argv[1], "rb");
if (arquivo_binario == NULL) { puts("Erro na abertura do arquivo"); exit(1); }

// Cria a lista encadeada
Lista_encadeada *lista = criar_lista_encadeada();

// Extrai os dados da linha
int cpf;
char cliente[MAX_STRING];
char pet[MAX_STRING];
char data_check_in[MIN_STRING];
char data_checkout[MIN_STRING];
char descricao[MAX_STRING];
float valor_reserva;

// Executa enquanto houverem dados para serem lidos (até o End Of File (EOF))
while ((fread(lista, sizeof(lista), 1, arquivo_binario)) != EOF){

  // Cria a reserva
  Reserva *reserva = registrar_reserva(cpf, cliente, pet, data_check_in, data_checkout, descricao, valor_reserva);

  // Inserir a reserva na lista
  InserirRegistroOrdenado(lista, reserva);
  
}

// Fechar o arquivo binario
fclose(arquivo_binario);

// Gravar os dados da lista no arquivo texto
binario_para_texto(argv[2], lista);

// Destrói a lista encadeada
excluir_lista_encadeada(lista);
}