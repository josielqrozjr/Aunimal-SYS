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
    char cpf[12];
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

typedef struct Lista_encadeada { // Estrutura da lista
    No *primeiro;
    No *ultimo;
} Lista_encadeada;


// Protótipo da função para criar uma reserva e alocar dinamicamente
Reserva *registrar_reserva(const char *cpf,
                           const char *cliente,
                           const char *pet,
                           const char *data_check_in,
                           const char *data_checkout,
                           const char *descricao,
                           float valor_reserva);

// Protótipo da função para criar uma lista encadeada
Lista_encadeada *criar_lista_encadeada(void);

// Protótipo da função para excluir uma lista encadeada
void excluir_lista_encadeada(Lista_encadeada *lista);

// Protótipo da função para criar uma lista vazia
int lista_encadeada_vazia(Lista_encadeada *lista);

// Protótipo da função para inserir em ordem crescente
void InserirRegistroOrdenado(Lista_encadeada *lista, Reserva *reserva);

// Protótipo da função para gravar os dados da lista num arquivo binário
void gravar_lista_encadeada(const char *nome_arquivo, Lista_encadeada *lista);

// Protótipo da função para abrir um arquivo binário e inserir numa lista encadeada
Lista_encadeada *abrir_arquivo_binario(const char *nome_arquivo);

// Protótipo da função para solicitar dados de reserva para o usuário
Reserva *solicitar_dados(void);

// Protótipo da função para liberar espaço alocado
void destruir_reserva(Reserva *reserva);

// Função para cadastrar reserva no sistema e salvar no binário
void cadastrar_reserva(const char *arquivo_binario);

#endif

/* lista_h */
