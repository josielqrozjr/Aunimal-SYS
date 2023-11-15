//
//  leitor.c
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr & Mateus A. Ramos on 12/11/23.
//

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"


int main(void) {
    FILE *arquivo_binario = fopen("binario.bin", "rb");

    if (arquivo_binario == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo binário.\n");
        return 1;
    }

    Reserva reserva;

    // Lê os dados do arquivo binário e exibe
    while (fread(&reserva, sizeof(Reserva), 1, arquivo_binario) == 1) { // Enquanto houver registro ele retorna 1 para verdadeiro
        printf("CPF: %s\n", reserva.cpf);
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
