  #include <stdio.h>
  #include <stdlib.h>

void binario_para_texto(char *arquivoBinario, char *arquivoTexto) {
    // Abre o arquivo binário para leitura
    FILE *arqBinario = fopen(arquivoBinario, "rb");
    if (arqBinario == NULL) {puts("Erro na abertura do arquivo binário, para leitura"); exit(1);}

    // Abre o arquivo de texto para escrita
    FILE *arqTexto = fopen(arquivoTexto, "w");
    if (arqTexto == NULL) {puts("Erro na abertura do arquivo texto, para escrita"); exit(1);}

    // Aloca memória para o buffer
    size_t tamanho_do_buffer = 256; // Quantidade aleaória de memória, passível de realocação
    char *buffer = (char *) malloc(tamanho_do_buffer); // Aloca memória para o buffer

    if(buffer == NULL) {puts("Erro na alocacao de memoria"); exit(1);}

    // Lê os dados do arquivo binário e escreva no arquivo de texto
    int contador; // Serve para contar quantos dados foram lidos

    // Executa enquanto houverem dados para serem lidos
    while ((contador = fread(buffer, sizeof(char), tamanho_do_buffer, arqBinario)) != EOF) {

        // Verifica se o buffer está cheio, caso esteja dobra o seu tamanho
        if (contador == tamanho_do_buffer) {
            tamanho_do_buffer *= 2;
            buffer = realloc(buffer, tamanho_do_buffer);
            if(buffer == NULL){puts("Erro na realocacao de memoria"); exit(1);}
        }
      
    
      
        for (size_t i = 0; i < contador; i++) {
            fprintf(arqTexto, "%c", buffer[i]); // Ajeitar aqui de acordo com a formatação que o txt deverá possuir
        }
    }

    // Libera a memória do buffer
    free(buffer);

    // Fecha os arquivos
    fclose(arqBinario);
    fclose(arqTexto);

    printf("Arquivo texto criado com sucesso.\n");
}

int main(int argc, char* argv[]){
  if (argc != 3 )
  {
    puts("ERRO: numero incorreto de argumentos!");
    exit(1);
  }

  binario_para_texto(argv[1], argv[2]);
}
