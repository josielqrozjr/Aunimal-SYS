//
//  main.c
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr & Mateus A. Ramos on 12/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s arquivo_texto arquivo_binario\n", argv[0]);
        return 1;
    }

    // Abre o arquivo texto
    FILE *arquivo_texto = fopen(argv[1], "r");
    if (arquivo_texto == NULL) { puts("Erro na abertura do arquivo"); exit(1); }


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

    // Lê os dados do arquivo texto escolhido
    while (fscanf(arquivo_texto, "%d %s %s %s %s %s %f", &cpf, cliente, pet, data_check_in, data_checkout, descricao, &valor_reserva) != EOF) {
      
        // Cria a reserva
        Reserva *reserva = registrar_reserva(cpf, cliente, pet, data_check_in, data_checkout, descricao, valor_reserva);

        // Inserir a reserva na lista
        InserirRegistroOrdenado(lista, reserva);
    }

    // Fechar o arquivo texto
    fclose(arquivo_texto);

    // Gravar os dados da lista no arquivo binário
    gravar_lista_encadeada(argv[2], lista);

    // Destrói a lista encadeada
    excluir_lista_encadeada(lista);

    return 0;
}
