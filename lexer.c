#include "lexer.h"
#include <stdlib.h>
#include <ctype.h>

ListaTokens* lexer(const char *linha) {
    ListaTokens *lista = malloc(sizeof(ListaTokens));
    lista->inicio = lista->fim = NULL;

    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == ' ' || linha[i] == '\t') continue;

        Token *novo = malloc(sizeof(Token));
        novo->prox = NULL;

        if (isdigit(linha[i])) {
            novo->tipo = NUMERO;
            novo->valor = linha[i];
        } else if (strchr("+-*/", linha[i])) {
            novo->tipo = OPERADOR;
            novo->valor = linha[i];
        } else if (linha[i] == '(') {
            novo->tipo = PARENTESES_ESQ;
            novo->valor = linha[i];
        } else if (linha[i] == ')') {
            novo->tipo = PARENTESES_DIR;
            novo->valor = linha[i];
        } else {
            liberar_tokens(lista);
            return NULL; // caractere inválido
        }

        if (lista->fim)
            lista->fim->prox = novo;
        else
            lista->inicio = novo;
        lista->fim = novo;
    }
    return lista;
}

void liberar_tokens(ListaTokens *lista) {
    if (!lista) return;
    Token *atual = lista->inicio;
    while (atual) {
        Token *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista);
}