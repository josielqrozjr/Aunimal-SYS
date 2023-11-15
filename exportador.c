#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

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
  
int main(int argc, char* argv[]){
  if (argc != 3 )
  {
    puts("ERRO: numero incorreto de argumentos!");
    exit(1);
  }

  Lista_encadeada *lista_nova_reserva = abrir_arquivo_binario("binario.bin");
  
  Reserva *nova_reserva = solicitar_dados();

  // Registrar dados da nova reserva na lista anterior
  InserirRegistroOrdenado(lista_nova_reserva, nova_reserva);
}