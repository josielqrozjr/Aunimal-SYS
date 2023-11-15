#ifndef GERADOR_H
#define GERADOR_H

typedef struct {
    char *cpf;
    char *nome;
    char *pet;
    char *data_check_in;
    char *data_checkout;
    char *descricao;
    float valor_reserva;
} Reserva;

Reserva *registrar_reserva( const char *cpf, const char *nome, const char *pet, const char *data_check_in, const char *data_checkout, const char *descricao, float valor_reserva);

#endif
