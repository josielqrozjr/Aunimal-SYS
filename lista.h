//
//  lista.h
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr & Mateus A. Ramos on 12/11/23.
// Arquivo contendo os protótipos das funções

#ifndef LISTA_H
#define LISTA_H

#define MAX_STRING 100
#define MIN_STRING 20

typedef struct Reserva {    // Estrutura da tabela reserva
    int cpf;
    char cliente[MAX_STRING];
    char pet[MAX_STRING];
    char data_check_in[MIN_STRING];
    char data_checkout[MIN_STRING];
    char descricao[MAX_STRING];
    float valor_reserva;
} Reserva;

typedef struct No {     // Estrutura do nó
    struct No *proximo;
    Reserva *Reserva;
} No;

typedef struct Lista_encadeada {
    No *primeiro;
    No *ultimo;
} Lista_encadeada;

Reserva *registrar_reserva(int cpf, 
                           const char *cliente,
                           const char *pet,
                           const char *data_check_in,
                           const char *data_checkout,
                           const char *descricao,
                           float valor_reserva);    // Protótipo da função para cadastrar uma reserva

Lista_encadeada *criar_lista_encadeada(void);

void excluir_lista_encadeada(Lista_encadeada *lista);

int lista_encadeada_vazia(Lista_encadeada *lista);

void InserirRegistroOrdenado(Lista_encadeada *lista, Reserva *reserva);

void gravar_lista_encadeada(const char *nome_arquivo, Lista_encadeada *lista);


#endif

/* lista_h */
