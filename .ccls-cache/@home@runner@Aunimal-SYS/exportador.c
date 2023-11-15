//
//  exportador.c
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr & Mateus A. Ramos on 15/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

void gravar_lista_encadeada_em_texto(const char *nome_arquivo,
                                     Lista_encadeada *lista) {
  FILE *arquivo_texto = fopen(nome_arquivo, "w");
  if (arquivo_texto == NULL) {
    printf("Erro ao abrir o arquivo de texto para escrita.\n");
    return;
  }

  No *no = lista->primeiro;
  while (no != NULL) { // Loop para escrever cada nó da lista no arquivo
    fprintf(arquivo_texto, "%s ", no->Reserva->cpf);
    fprintf(arquivo_texto, "%s ", no->Reserva->cliente);
    fprintf(arquivo_texto, "%s ", no->Reserva->pet);
    fprintf(arquivo_texto, "%s ", no->Reserva->data_check_in);
    fprintf(arquivo_texto, "%s ", no->Reserva->data_checkout);
    fprintf(arquivo_texto, "%s ", no->Reserva->descricao);
    fprintf(arquivo_texto, "%f\n", no->Reserva->valor_reserva);

    // Move o ponteiro para o próximo nó da lista
    no = no->proximo;
  }

  fclose(arquivo_texto);
}

int main(int argc, char *argv[]) {

  Lista_encadeada *lista_nova_reserva = abrir_arquivo_binario(argv[1]);

  // Gravar os dados da lista no arquivo binário
  gravar_lista_encadeada_em_texto(argv[2], lista_nova_reserva);

  // Destruir a lista encadeada
  excluir_lista_encadeada(lista_nova_reserva);

  return 0;
}
