#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pilha {
    int topo;
    int *dados;
} Pilha;

Pilha* criarPilha(int tamanho) {
    Pilha *p = malloc(sizeof(Pilha));
    p->topo = -1;
    p->dados = malloc(tamanho * sizeof(int));
    return p;
}

void empilhar(Pilha *p, int dado) {
    p->topo++;
    p->dados[p->topo] = dado;
}

int desempilhar(Pilha *p) {
    int dado = p->dados[p->topo];
    p->topo--;
    return dado;
}

bool pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

typedef struct fila {
    int inicio, fim, max;
    int *dados;
} Fila;

Fila* criarFila(int max) {
    Fila *f = malloc(sizeof(Fila));
    f->inicio = 0;
    f->fim = -1;
    f->max = max;
    f->dados = malloc(max * sizeof(int));
    return f;
}

bool estaVazia(Fila *f) {
    return (f->fim < f->inicio);
}

bool estaCheia(Fila *f) {
    return (f->fim == f->max - 1);
}

bool inserir(Fila *f, int dado) {
    if (!estaCheia(f)) {
        f->fim++;
        f->dados[f->fim] = dado;
        return true;
    }
    return false;
}

int remover(Fila *f) {
    if (!estaVazia(f)) {
        int aux = f->dados[f->inicio];
        f->inicio++;
        return aux;
    }
}

void imprimirFilaInvertida(Fila *f) {
    Pilha *pilhaAuxiliar = criarPilha(f->max);

    while (!estaVazia(f)) {
        empilhar(pilhaAuxiliar, remover(f));
    }

    while (!pilhaVazia(pilhaAuxiliar)) {
        printf("%d\n", desempilhar(pilhaAuxiliar));
    }

    free(pilhaAuxiliar->dados);
    free(pilhaAuxiliar);
}

int tamanho(Fila *f) {
    return f->fim - f->inicio + 1;
}

void limparFila(Fila *f) {
    while (!estaVazia(f)) {
        remover(f);
    }

    free(f->dados);

    f->inicio = 0;
    f->fim = -1;
}

int main() {
    Fila *f = criarFila(5);

    inserir(f, 8);
    inserir(f, 10);
    inserir(f, 20);
    inserir(f, 30);
    inserir(f, 40);

    printf("Elementos da fila em ordem inversa:\n");
    imprimirFilaInvertida(f);

    printf("Tamanho da fila: %d\n", tamanho(f));

    limparFila(f);
    printf("Fila limpa.\n");

    free(f);
    
    return 0;
}