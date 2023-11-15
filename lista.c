//
//  lista.c
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr & Mateus A. Ramos on 12/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "lista.h"

Lista_encadeada *criar_lista_encadeada(void) {
    Lista_encadeada *lista = malloc(sizeof(Lista_encadeada));
    if (lista == NULL) { // Verifica se a memória foi alocada corretamente
        return NULL;
    }

    lista->primeiro = NULL; // Define o ponteiro que aponta para o primeiro elemento da lista como NULL
    lista->ultimo = NULL; // Define o ponteiro que aponta para o próximo elemento da lista como NULL

    return lista;
}


void excluir_lista_encadeada(Lista_encadeada *lista) {
    if (lista == NULL) {
        return;
    }

    No *no = lista->primeiro;
    while (no != NULL) {
        No *proximo = no->proximo;
        free(no->Reserva);
        free(no);
        no = proximo;
    }

    free(lista);
}


int lista_encadeada_vazia(Lista_encadeada *lista) {
    return lista->primeiro == NULL;
}


void InserirRegistroOrdenado(Lista_encadeada *lista, Reserva *Reserva) {
    No *novo_no = (No*)malloc(sizeof(No));
    novo_no->Reserva = Reserva;

    No *p = NULL;
    No *q = lista->primeiro;

    int novo_cpf = Reserva->cpf;

    bool procurando = true;
    while (q && procurando) {
        if (novo_cpf <= q->Reserva->cpf) {
            procurando = false;
        } else {
            p = q;
            q = q->proximo;
        }
    }

    if (p == NULL) {
        // Insere no início da lista
        novo_no->proximo = lista->primeiro;
        lista->primeiro = novo_no;

        if (lista->ultimo == NULL) {
            // Se a lista estava vazia, ajusta o último elemento também
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


void gravar_lista_encadeada(const char *nome_arquivo, Lista_encadeada *lista) {
    FILE *arquivo_binario = fopen(nome_arquivo, "wb");
    if (arquivo_binario == NULL) {
        printf("Erro ao abrir o arquivo binário para escrita.\n");
        return;
    }

    No *no = lista->primeiro;
    while (no != NULL) {
        fwrite(&(no->Reserva->cpf), sizeof(int), 1, arquivo_binario);
        fwrite(no->Reserva->cliente, sizeof(char), MAX_STRING, arquivo_binario);
        fwrite(no->Reserva->pet, sizeof(char), MAX_STRING, arquivo_binario);
        fwrite(no->Reserva->data_check_in, sizeof(char), MIN_STRING, arquivo_binario);
        fwrite(no->Reserva->data_checkout, sizeof(char), MIN_STRING, arquivo_binario);
        fwrite(no->Reserva->descricao, sizeof(char), MAX_STRING, arquivo_binario);
        fwrite(&(no->Reserva->valor_reserva), sizeof(float), 1, arquivo_binario);

        no = no->proximo;
    }

    fclose(arquivo_binario);
}


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