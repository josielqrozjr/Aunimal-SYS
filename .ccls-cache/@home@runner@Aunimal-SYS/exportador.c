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


int main(int argc, char *argv[]) {

  Lista_encadeada *lista_nova_reserva = abrir_arquivo_binario(argv[1]);

  // Gravar os dados da lista no arquivo binário
  gravar_lista_encadeada_em_texto(argv[2], lista_nova_reserva);

  // Destruir a lista encadeada
  excluir_lista_encadeada(lista_nova_reserva);

  return 0;
}
