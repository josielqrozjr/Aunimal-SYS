//
//  lista.c
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr & Mateus A. Ramos on 12/11/23.
//  Arquivo lista.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "lista.h"


//-----------------------------------------------------------------------------------
// Função para criar uma lista encadeada
Lista_encadeada *criar_lista_encadeada(void) {
    Lista_encadeada *lista = malloc(sizeof(Lista_encadeada));
    if (lista == NULL) { // Verifica se a memória foi alocada corretamente
        return NULL;
    }

    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

//-----------------------------------------------------------------------------------
// Função para excluir uma lista encadeada
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

//-----------------------------------------------------------------------------------
// Função para inserir ordenado crescentemente na lista encadeada
void InserirRegistroOrdenado(Lista_encadeada *lista, Reserva *Reserva) {
    No *novo_no = (No*)malloc(sizeof(No));
    novo_no->Reserva = Reserva;

    No *p = NULL;
    No *q = lista->primeiro;

    char novo_cpf[12];
    strcpy(novo_cpf, Reserva->cpf);

    bool procurando = true;
    while (q && procurando) {
      if (strcmp(novo_cpf, q->Reserva->cpf) <= 0) {
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

//-----------------------------------------------------------------------------------
// Função para gravar os dados da lista encadeada em um arquivo binário
void gravar_lista_encadeada(const char *nome_arquivo, Lista_encadeada *lista) {
    FILE *arquivo_binario = fopen(nome_arquivo, "wb");
    if (arquivo_binario == NULL) {
        printf("Erro ao abrir o arquivo binário para escrita.\n");
        return;
    }

    No *no = (No*) malloc(sizeof(No));
    no = lista->primeiro;
    while (no != NULL) { // Loop para escrever cada nó da lista no arquivo
        fwrite(no->Reserva->cpf, sizeof(char), 12, arquivo_binario);
        fwrite(no->Reserva->cliente, sizeof(char), MAX_STRING, arquivo_binario);
        fwrite(no->Reserva->pet, sizeof(char), MAX_STRING, arquivo_binario);
        fwrite(no->Reserva->data_check_in, sizeof(char), MIN_STRING, arquivo_binario);
        fwrite(no->Reserva->data_checkout, sizeof(char), MIN_STRING, arquivo_binario);
        fwrite(no->Reserva->descricao, sizeof(char), MAX_STRING, arquivo_binario);
        fwrite(&(no->Reserva->valor_reserva), sizeof(float), 1, arquivo_binario);

        // Move o ponteiro para o próximo nó da lista
        no = no->proximo;
    }

  fclose(arquivo_binario);
}

//-----------------------------------------------------------------------------------
// Função para criar os dados de uma reserva
Reserva *registrar_reserva(const char *cpf, const char *cliente, const char *pet, const char *data_check_in, const char *data_checkout, const char *descricao, float valor_reserva) {
    Reserva *reserva = malloc(sizeof(Reserva));
    if (reserva == NULL) {
        return NULL;
    }

    strcpy(reserva->cpf, cpf);
    strcpy(reserva->cliente, cliente);
    strcpy(reserva->pet, pet);
    strcpy(reserva->data_check_in, data_check_in);
    strcpy(reserva->data_checkout, data_checkout);
    strcpy(reserva->descricao, descricao);
    reserva->valor_reserva = valor_reserva;

    return reserva;
}

//-----------------------------------------------------------------------------------
// Função para buscar uma reserva pelo cpf
Reserva *buscar_cpf(Lista_encadeada *lista, No *no, const char *cpf) {
    // Verifica se o nó é nulo
    if (no == NULL) {
        return NULL; // CPF não encontrado
    }

    // Analisa se o CPF no nó atual corresponde ao CPF inserido
    if (strcmp(no->Reserva->cpf, cpf) == 0) {
        return no->Reserva; // Encontrou o CPF
    }

    // Chama a função recursivamente para o próximo nó na lista
    return buscar_cpf(lista, no->proximo, cpf);
}

//-----------------------------------------------------------------------------------
// Função para abrir o arquivo binário e retornar numa lista encadeada
Lista_encadeada *abrir_arquivo_binario(const char *nome_arquivo){
  // Abre o arquivo binário para leitura
  FILE *arquivo_binario = fopen(nome_arquivo, "rb");
  if (arquivo_binario == NULL) {
    puts("Erro na abertura do arquivo!");
    exit(1);
  }

  // Criar a lista encadeada
  Lista_encadeada *lista = criar_lista_encadeada();

  Reserva reserva;

  // Ler os dados do arquivo binário e insere na lista encadeada
  while (fread(&reserva, sizeof(Reserva), 1, arquivo_binario) || !feof(arquivo_binario)) {
    Reserva *reserva_nova = malloc(sizeof(Reserva));
    if (reserva_nova == NULL) {
      puts("Erro na alocação de memória!");
      exit(1);
    }

    // Copiar os dados para a nova reserva
    memcpy(reserva_nova, &reserva, sizeof(Reserva));
    InserirRegistroOrdenado(lista, reserva_nova);
  }
  // Fechar o arquivo binário
  fclose(arquivo_binario);

  return lista;
}

//-----------------------------------------------------------------------------------
// Função para validar um CPF
bool validar_cpf(Lista_encadeada *lista, const char *cpf) {
    No *no = lista->primeiro;
    if (strlen(cpf) != 11) {
        printf("CPF inválido: formato incorreto.\n");
        return false;
    }
    // Loop para percorrer e verificar se todos são números
    for (int i = 0; i < strlen(cpf); i++) {
    if (cpf[i] < '0' || cpf[i] > '9') {return false;}}

    if (buscar_cpf(lista, no, cpf) != NULL) {
        printf("CPF já cadastrado!\n");
        return false;
    }

    return true; // CPF válido
}
//-----------------------------------------------------------------------------------
// Função para solicitar ao usuário que informe os dados de uma reserva
Reserva *solicitar_dados(Lista_encadeada *lista){

  char cpf[12];
  char cliente[MAX_STRING];
  char pet[MAX_STRING];
  char data_check_in[MIN_STRING];
  char data_checkout[MIN_STRING];
  char descricao[MAX_STRING];
  float valor_reserva;

  printf("Digite o nome do cliente: ");
  scanf("%s", cliente);

  do {
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
  } while (validar_cpf(lista, cpf) == false); // Validar CPF inserido

  printf("Digite o nome do pet: ");
  scanf("%s", pet);

  printf("Digite a data de check-in (DD-MM-AAAA): ");
  scanf("%s", data_check_in);

  printf("Digite a data de check-out (DD-MM-AAAA): ");
  scanf("%s", data_checkout);

  printf("Digite a descrição da reserva: ");
  scanf("%s", descricao);

  printf("Digite o valor da reserva: ");
  scanf("%f", &valor_reserva);

  // Armazenar os dados da reserva
  Reserva *reserva = registrar_reserva(cpf, cliente, pet, data_check_in, data_checkout, descricao, valor_reserva);

  return reserva; // Retornar os dados inseridos pelo usuário
}

//-----------------------------------------------------------------------------------
// Função para cadastrar reserva no sistema e salvar no binário
void cadastrar_reserva(Lista_encadeada *lista_nova_reserva, const char *arquivo_binario){

  Reserva *nova_reserva = solicitar_dados(lista_nova_reserva);

  // Registrar dados da nova reserva na lista anterior
  InserirRegistroOrdenado(lista_nova_reserva, nova_reserva);

  // Gravar os dados da lista no arquivo binário
  gravar_lista_encadeada(arquivo_binario, lista_nova_reserva);

    printf("Reserva cadastrada com sucesso!.\n");

}

//-----------------------------------------------------------------------------------
// Função para exibir TODOS os dados de reserva da lista encadeada
void exibir_lista_completa(Lista_encadeada *lista) {
    No *no = lista->primeiro;

    // Loop para imprimir todos os dados da lista encadeada
    while (no != NULL) {
        if (no->Reserva != NULL) {
            printf("CPF: %s\n", no->Reserva->cpf);
            printf("Cliente: %s\n", no->Reserva->cliente);
            printf("Pet: %s\n", no->Reserva->pet);
            printf("Data Check-in: %s\n", no->Reserva->data_check_in);
            printf("Data Checkout: %s\n", no->Reserva->data_checkout);
            printf("Descrição: %s\n", no->Reserva->descricao);
            printf("Valor Reserva: %f\n", no->Reserva->valor_reserva);
            printf("\n");
        } else {
            printf("Sem reservas cadastradas no momento!\n");
        }

        // Desloca o ponteiro para o próximo nó da lista encadeada
        no = no->proximo;
    }
}

//-----------------------------------------------------------------------------------
// Função para exibir as reservas da data de check_in escolhida
void exibir_lista_checkin(Lista_encadeada *lista) {

    // Solicitar data para o usuário
    char data_escolhida[MIN_STRING];
    printf("Digite a data de check-in: ");
    scanf("%s", data_escolhida);

    No *no = lista->primeiro;

    while (no != NULL) {
        // Verificar se a reserva está na data escolhida
        if (strcmp(no->Reserva->data_check_in, data_escolhida) == 0) {
            // Exibir informações sobre a reserva
            printf("CPF: %s\n", no->Reserva->cpf);
            printf("Cliente: %s\n", no->Reserva->cliente);
            printf("Pet: %s\n", no->Reserva->pet);
            printf("Data Check-in: %s\n", no->Reserva->data_check_in);
            printf("Data Checkout: %s\n", no->Reserva->data_checkout);
            printf("Descrição: %s\n", no->Reserva->descricao);
            printf("Valor Reserva: %.2f\n", no->Reserva->valor_reserva);
            printf("\n");
        }

        no = no->proximo;
    }
}

//-----------------------------------------------------------------------------------
// Função para gravar lista em arquivo de texto.txt
void gravar_lista_encadeada_em_texto(const char *nome_arquivo, Lista_encadeada *lista) {
  FILE *arquivo_texto = fopen(nome_arquivo, "w");
  if (arquivo_texto == NULL) {
    printf("Erro ao abrir o arquivo de texto para escrita.\n");
    return;
  }

  No *no = lista->primeiro;
  while (no != NULL) { // Loop para escrever cada nó da lista no arquivo de texto
    fprintf(arquivo_texto, "%s ", no->Reserva->cpf);
    fprintf(arquivo_texto, "%s ", no->Reserva->cliente);
    fprintf(arquivo_texto, "%s ", no->Reserva->pet);
    fprintf(arquivo_texto, "%s ", no->Reserva->data_check_in);
    fprintf(arquivo_texto, "%s ", no->Reserva->data_checkout);
    fprintf(arquivo_texto, "%s ", no->Reserva->descricao);
    fprintf(arquivo_texto, "%f\n", no->Reserva->valor_reserva);

    // Desloca o ponteiro para o próximo nó da lista encadeada
    no = no->proximo;
  }

  fclose(arquivo_texto);
}

//-----------------------------------------------------------------------------------
// Função para excluir um elemento (nó) da lista encadeada
void remover_elemento(Lista_encadeada *lista, const char *cpf, const char *nome_arquivo) {
    No *anterior = NULL;
    No *atual = lista->primeiro;

    while (atual != NULL) {
        if (strcmp(atual->Reserva->cpf, cpf) == 0) {
            // Encontrou o elemento a ser removido

            if (anterior == NULL) {
                // O elemento a ser removido está no início da lista
                lista->primeiro = atual->proximo;
            } else {
                // O elemento a ser removido não está no início da lista
                anterior->proximo = atual->proximo;
            }

            // Liberar a memória do elemento removido
            free(atual->Reserva);
            free(atual);

            // Gravar os dados da lista no arquivo binário
            gravar_lista_encadeada(nome_arquivo, lista);

            printf("Reserva com CPF %s removido do sistema.\n", cpf);
            return;

        }

        // Avançar para o próximo nó da lista
        anterior = atual;
        atual = atual->proximo;
    }

    // O CPF não foi encontrado na lista
    printf("Reserva com CPF %s não encontrado no sistema.\n", cpf);
}
