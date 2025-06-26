#ifndef LEXER_H
#define LEXER_H

typedef enum {
    NUMERO, OPERADOR, PARENTESES_ESQ, PARENTESES_DIR, INVALIDO
} TipoToken;

typedef struct Token {
    TipoToken tipo;
    char valor;
    struct Token *prox;
} Token;

typedef struct {
    Token *inicio;
    Token *fim;
} ListaTokens;

ListaTokens* lexer(const char *linha);
void liberar_tokens(ListaTokens *lista);

#endif