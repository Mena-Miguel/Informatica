#include "parser.h"
#include <stdlib.h>

static int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Shunting Yard simplificado
Fila* parser(ListaTokens *tokens, int *erro) {
    Fila *saida = malloc(sizeof(Fila));
    saida->inicio = saida->fim = NULL;
    Token *atual = tokens->inicio;
    Token *pilha[100];
    int topo = -1, balanceamento = 0;

    while (atual) {
        if (atual->tipo == NUMERO) {
            NoFila *novo = malloc(sizeof(NoFila));
            novo->valor = atual->valor;
            novo->tipo = NUMERO;
            novo->prox = NULL;
            if (saida->fim)
                saida->fim->prox = novo;
            else
                saida->inicio = novo;
            saida->fim = novo;
        } else if (atual->tipo == OPERADOR) {
            while (topo >= 0 && pilha[topo]->tipo == OPERADOR 
                    && precedencia(pilha[topo]->valor) >= precedencia(atual->valor)) {
                NoFila *novo = malloc(sizeof(NoFila));
                novo->valor = pilha[topo]->valor;
                novo->tipo = OPERADOR;
                novo->prox = NULL;
                if (saida->fim)
                    saida->fim->prox = novo;
                else
                    saida->inicio = novo;
                saida->fim = novo;
                topo--;
            }
            pilha[++topo] = atual;
        } else if (atual->tipo == PARENTESES_ESQ) {
            balanceamento++;
            pilha[++topo] = atual;
        } else if (atual->tipo == PARENTESES_DIR) {
            balanceamento--;
            int encontrou = 0;
            while (topo >= 0) {
                if (pilha[topo]->tipo == PARENTESES_ESQ) {
                    encontrou = 1;
                    topo--;
                    break;
                } else {
                    NoFila *novo = malloc(sizeof(NoFila));
                    novo->valor = pilha[topo]->valor;
                    novo->tipo = pilha[topo]->tipo;
                    novo->prox = NULL;
                    if (saida->fim)
                        saida->fim->prox = novo;
                    else
                        saida->inicio = novo;
                    saida->fim = novo;
                    topo--;
                }
            }
            if (!encontrou || balanceamento < 0) {
                *erro = 1; // parênteses desbalanceados
                liberar_fila(saida);
                return NULL;
            }
        }
        atual = atual->prox;
    }
    if (balanceamento != 0) {
        *erro = 1; // parênteses desbalanceados
        liberar_fila(saida);
        return NULL;
    }
    while (topo >= 0) {
        if (pilha[topo]->tipo == PARENTESES_ESQ || pilha[topo]->tipo == PARENTESES_DIR) {
            *erro = 1;
            liberar_fila(saida);
            return NULL;
        }
        NoFila *novo = malloc(sizeof(NoFila));
        novo->valor = pilha[topo]->valor;
        novo->tipo = pilha[topo]->tipo;
        novo->prox = NULL;
        if (saida->fim)
            saida->fim->prox = novo;
        else
            saida->inicio = novo;
        saida->fim = novo;
        topo--;
    }
    *erro = 0;
    return saida;
}

void liberar_fila(Fila *fila) {
    if (!fila) return;
    NoFila *atual = fila->inicio;
    while (atual) {
        NoFila *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(fila);
}