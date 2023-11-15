#ifndef LISTA_H
#define LISTA_H

#define MAX_STRING 100
#define MIN_STRING 50

typedef struct reserva {
    int cpf;
    char cliente[MAX_STRING];
    char pet[MAX_STRING];
    char data_check_in[MIN_STRING];
    char data_checkout[MIN_STRING];
    char descricao[MAX_STRING];
    float valor_reserva;
} Reserva;

typedef struct no_lista {
    struct no_lista *proximo;
    Reserva *reserva;
} NoLista;

typedef struct lista_encadeada {
    NoLista *primeiro;
    NoLista *ultimo;
} ListaEncadeada;

Reserva *registrar_reserva(int cpf, const char *cliente, const char *pet, const char *data_check_in, const char *data_checkout, const char *descricao, float valor_reserva);

ListaEncadeada *criar_lista_encadeada();
void destruir_lista_encadeada(ListaEncadeada *lista);
int lista_encadeada_vazia(ListaEncadeada *lista);
void inserir_lista_encadeada(ListaEncadeada *lista, Reserva *reserva);
void remover_lista_encadeada(ListaEncadeada *lista, int cpf);
Reserva *procurar_lista_encadeada(ListaEncadeada *lista, int cpf);
void exibir_lista_encadeada(ListaEncadeada *lista);
void gravar_lista_encadeada(const char *nome_arquivo, ListaEncadeada *lista);

#endif
