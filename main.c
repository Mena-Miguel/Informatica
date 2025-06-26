#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "avaliador.h"

#define TAM_LINHA 256

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso correto: %s in.txt out.txt\n", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");
    if (!entrada || !saida) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    char linha[TAM_LINHA];
    int num_linha = 1;
    while (fgets(linha, TAM_LINHA, entrada)) {
        // Remove quebra de linha
        linha[strcspn(linha, "\r\n")] = 0;

        ListaTokens *tokens = lexer(linha);
        if (!tokens) {
            fprintf(saida, "Erro: Caracteres inválidos\n");
            num_linha++;
            continue;
        }

        int erro = 0;
        Fila *posfixa = parser(tokens, &erro);

        if (erro == 1) {
            fprintf(saida, "Erro: Parênteses desbalanceados\n");
        } else if (erro == 2) {
            fprintf(saida, "Erro: Expressão malformada\n");
        } else if (posfixa) {
            int resultado, erro_avaliacao = 0;
            resultado = avaliar(posfixa, &erro_avaliacao);
            if (erro_avaliacao == 1)
                fprintf(saida, "Erro: Divisão por zero\n");
            else
                fprintf(saida, "%d\n", resultado);
            liberar_fila(posfixa);
        }
        liberar_tokens(tokens);
        num_linha++;
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}