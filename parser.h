#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct NoFila {
    char valor;
    TipoToken tipo;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

Fila* parser(ListaTokens *tokens, int *erro);
void liberar_fila(Fila *fila);

#endif