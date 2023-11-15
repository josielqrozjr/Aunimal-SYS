//
//  leitor.c
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr on 12/11/23.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct reserva {
    int cpf;
    char cliente[100];
    char pet[100];
    char data_check_in[50];
    char data_checkout[50];
    char descricao[100];
    float valor_reserva;
} Reserva;

int main(void) {
    FILE *arquivo_binario = fopen("saida.bin", "rb");

    if (arquivo_binario == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo binário.\n");
        return 1;
    }

    Reserva reserva;

    // Lê os dados do arquivo binário e exibe
    while (fread(&reserva, sizeof(Reserva), 1, arquivo_binario) == 1) {
        printf("CPF: %d\n", reserva.cpf);
        printf("Cliente: %s\n", reserva.cliente);
        printf("Pet: %s\n", reserva.pet);
        printf("Data Check-in: %s\n", reserva.data_check_in);
        printf("Data Checkout: %s\n", reserva.data_checkout);
        printf("Descrição: %s\n", reserva.descricao);
        printf("Valor Reserva: %.2f\n", reserva.valor_reserva);
        printf("\n");
    }

    fclose(arquivo_binario);

    return 0;
}
