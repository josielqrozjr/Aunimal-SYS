  //
//  editor.c
//  Aunimal SYS
//
//  Created by Josiel Queiroz Jr & Mateus A. Ramos on 12/11/23.
//  Arquivo editor.c


#include <stdio.h>
#include <stdlib.h>

#include "lista.h"


int main(int argc, char *argv[]) {

  Lista_encadeada *lista_editor = abrir_arquivo_binario(argv[1]); // Abrir arquivo para ser utilizado no editor

  int opcao, valor, anterior;
  char cpf[12];
      No *removido, *lista = NULL;

      do{
          printf("\nAUNIMAL - HOTEL PET \nSistema de Reservas \n\t1 - Cadastrar reserva\n\t2 - Remover reserva\n\t3 - Exibir reservas\n\t4 - Sair\n");
          printf("Digite aqui o número da opção: ");
          scanf("%d", &opcao);

          switch(opcao){
          case 1:
            printf("Cadastrar reserva\n");
            cadastrar_reserva(lista_editor, argv[1]);
            break;
          case 2:
            printf("Remover reserva\n");
            printf("Digite o CPF do registro que deseja remover\n");
            scanf("%11s", cpf);
            removido = remover(&lista, cpf);
            if(removido){
                printf("Elemento a ser removido: %s\n", removido->Reserva->cpf);
                free(removido);
            }
            else
                printf("Elemento inexistente!\n");
            break;
          case 3:
            printf("Exibir reservas\n");
            printf("Opções: \n\t1. Exibir todas \n\t2. Exibir por data de check-in\n");
            printf("Digite aqui o número da opção: ");
            scanf("%d", &opcao);
            if(opcao == 1){exibir_lista_completa(lista_editor);}
            else if(opcao == 2){exibir_lista_checkin(lista_editor);}
            break;
          case 4:
            printf("Encerrando sistema!\n");
            break;
          default:
              if(opcao != 0)
                  printf("Opcao inválida!\n");
          }

      }while(opcao != 0);

      return 0;
  }




