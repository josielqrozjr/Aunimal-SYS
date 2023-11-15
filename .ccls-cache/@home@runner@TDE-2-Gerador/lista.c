#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "lista.h"

ListaEncadeada *criar_lista_encadeada() {
    ListaEncadeada *lista = malloc(sizeof(ListaEncadeada));
    if (lista == NULL) {
        return NULL;
    }

    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

void destruir_lista_encadeada(ListaEncadeada *lista) {
    if (lista == NULL) {
        return;
    }

    NoLista *no = lista->primeiro;
    while (no != NULL) {
        NoLista *proximo = no->proximo;
        free(no->reserva);
        free(no);
        no = proximo;
    }

    free(lista);
}

int lista_encadeada_vazia(ListaEncadeada *lista) {
    return lista->primeiro == NULL;
}


void inserir_lista_encadeada(ListaEncadeada *lista, Reserva *reserva) {
    NoLista *novo_no = (NoLista*)malloc(sizeof(NoLista));
    novo_no->reserva = reserva;

    NoLista *p = NULL;
    NoLista *q = lista->primeiro;

    int novo_cpf = reserva->cpf;

    bool procurando = true;
    while (q && procurando) {
        if (novo_cpf <= q->reserva->cpf) {
            procurando = false;
        } else {
            p = q;
            q = q->proximo;
        }
    }

    if (p == NULL) {
        // insere no início da lista
        novo_no->proximo = lista->primeiro;
        lista->primeiro = novo_no;

        if (lista->ultimo == NULL) {
            // Se a lista estava vazia, ajusta o último também
            lista->ultimo = novo_no;
        }
    } else {
        p->proximo = novo_no;
        novo_no->proximo = q;

        if (q == NULL) {
            // Se o novo nó foi inserido no final, ajusta o último
            lista->ultimo = novo_no;
        }
    }
}


void remover_lista_encadeada(ListaEncadeada *lista, int cpf) {
    NoLista *no = lista->primeiro;
    NoLista *anterior = NULL;

    while (no != NULL) {
        if (no->reserva->cpf == cpf) {
            if (no == lista->primeiro) {
                lista->primeiro = no->proximo;
            } else {
                anterior->proximo = no->proximo;
            }

            if (no == lista->ultimo) {
                lista->ultimo = anterior;
            }

            free(no->reserva);
            free(no);
            return;
        }

        anterior = no;
        no = no->proximo;
    }

    // Se chegou aqui, significa que o CPF não foi encontrado
    printf("CPF não encontrado na lista.\n");
}

Reserva *procurar_lista_encadeada(ListaEncadeada *lista, int cpf) {
    NoLista *no = lista->primeiro;
    while (no != NULL) {
        if (no->reserva->cpf == cpf) {
            return no->reserva;
        }

        no = no->proximo;
    }

    return NULL;
}


void exibir_lista_encadeada(ListaEncadeada *lista) {
    NoLista *no = lista->primeiro;
    while (no != NULL) {
        // Exibir informações sobre a reserva aqui
        no = no->proximo;
    }
}

void gravar_lista_encadeada(const char *nome_arquivo, ListaEncadeada *lista) {
    FILE *arquivo_binario = fopen(nome_arquivo, "wb");
    if (arquivo_binario == NULL) {
        printf("Erro ao abrir o arquivo binário para escrita.\n");
        return;
    }

    NoLista *no = lista->primeiro;
    while (no != NULL) {
      fwrite(&(no->reserva->cpf), sizeof(int), 1, arquivo_binario);
      fwrite(no->reserva->cliente, sizeof(char), MAX_STRING, arquivo_binario);
      fwrite(no->reserva->pet, sizeof(char), MAX_STRING, arquivo_binario);
      fwrite(no->reserva->data_check_in, sizeof(char), MIN_STRING, arquivo_binario);
      fwrite(no->reserva->data_checkout, sizeof(char), MIN_STRING, arquivo_binario);
      fwrite(no->reserva->descricao, sizeof(char), MAX_STRING, arquivo_binario);
      fwrite(&(no->reserva->valor_reserva), sizeof(float), 1, arquivo_binario);

        no = no->proximo;
    }

    fclose(arquivo_binario);
}
