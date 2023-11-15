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
          scanf("%d", &opcao);

          switch(opcao){
          case 1:
            printf("Cadastrar reserva\n");
            printf("%50s\n", "=");
            cadastrar_reserva(lista_editor);
            break;
          case 2:
            printf("Remover reserva\n");
            printf("%50s\n", "=");
            scanf("%c", cpf);
            removido = remover(*lista, cpf);
            if(removido){
                printf("Elemento a ser removido: %d\n", removido->Reserva->cpf);
                free(removido);
            }
            else
                printf("Elemento inexistente!\n");
            break;
          case 3:
            printf("Exibir reservas\n");
            printf("%50s\n", "=");
            printf("Digite um número para a opção: \n\t1. Exibir todas \n\t2. Exibir por data de check-in");
            scanf("%d", &opcao);
            if(opcao == 1){exibir_lista_completa(lista_editor);}
            else if(opcao == 2){exibir_lista_checkin(lista_editor);}
            break;
          case 4:
            printf("Encerrando sistema!");
            printf("%50s\n", "=");
            break;
          default:
              if(opcao != 0)
                  printf("Opcao inválida!\n");
          }

      }while(opcao != 0);

      return 0;
  }



}
