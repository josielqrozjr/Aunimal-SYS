#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

Reserva *registrar_reserva(int cpf, const char *cliente, const char *pet, const char *data_check_in, const char *data_checkout, const char *descricao, float valor_reserva) {
    Reserva *reserva = malloc(sizeof(Reserva));
    if (reserva == NULL) {
        return NULL;
    }

    reserva->cpf = cpf;
    strcpy(reserva->cliente, cliente);
    strcpy(reserva->pet, pet);
    strcpy(reserva->data_check_in, data_check_in);
    strcpy(reserva->data_checkout, data_checkout);
    strcpy(reserva->descricao, descricao);
    reserva->valor_reserva = valor_reserva;

    return reserva;
}

void destruir_reserva(Reserva *reserva) {
    if (reserva == NULL) {
        return;
    }
    free(reserva);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s arquivo_texto arquivo_binario\n", argv[0]);
        return 1;
    }

    // Abre o arquivo texto
    FILE *arquivo_texto = fopen(argv[1], "r");
    if (arquivo_texto == NULL) { puts("Erro na abertura do arquivo"); exit(1); }


    // Cria a lista encadeada
    ListaEncadeada *lista = criar_lista_encadeada();

  // Extrai os dados da linha
  int cpf;
  char cliente[255];
  char pet[255];
  char data_check_in[20];
  char data_checkout[20];
  char descricao[255];
  float valor_reserva;

    // Lê os dados do arquivo texto
    while (fscanf(arquivo_texto, "%d %s %s %s %s %s %f", &cpf, cliente, pet, data_check_in, data_checkout, descricao, &valor_reserva) != EOF) {
        // Lê uma linha do arquivo texto
        char linha[255];
        fgets(linha, 255, arquivo_texto);

        // Cria a reserva
        Reserva *reserva = registrar_reserva(cpf, cliente, pet, data_check_in, data_checkout, descricao, valor_reserva);

        // Inserir a reserva na lista
        inserir_lista_encadeada(lista, reserva);
    }

    // Fechar o arquivo texto
    fclose(arquivo_texto);

    // Gravar os dados da lista no arquivo binário
    gravar_lista_encadeada(argv[2], lista);

    // Destrói a lista encadeada
    destruir_lista_encadeada(lista);

    return 0;
}
