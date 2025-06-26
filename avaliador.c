#include "avaliador.h"
#include <stdlib.h>

int avaliar(Fila *posfixa, int *erro) {
    int pilha[100];
    int topo = -1;
    NoFila *atual = posfixa->inicio;

    while (atual) {
        if (atual->tipo == NUMERO) {
            pilha[++topo] = atual->valor - '0';
        } else if (atual->tipo == OPERADOR) {
            if (topo < 1) {
                *erro = 2; // expressão malformada
                return 0;
            }
            int b = pilha[topo--];
            int a = pilha[topo--];
            int r = 0;
            switch (atual->valor) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0) {
                        *erro = 1; // divisão por zero
                        return 0;
                    }
                    r = a / b;
                    break;
            }
            pilha[++topo] = r;
        }
        atual = atual->prox;
    }
    if (topo != 0) {
        *erro = 2; // expressão malformada
        return 0;
    }
    *erro = 0;
    return pilha[topo];
}