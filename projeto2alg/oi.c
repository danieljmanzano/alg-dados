#include <stdio.h>
#include <stdlib.h>

typedef struct no_ {
    struct no_ *esq, *dir;
    int chave;
} NO;

typedef struct arvore_ {
    NO *raiz;
    int profundidade;
} ARVORE;

// Função para calcular altura de um nó
int altura(NO *no) {
    if (no == NULL) return 0;
    
    int alt_esq = altura(no->esq);
    int alt_dir = altura(no->dir);
    
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

// Função para calcular fator de balanceamento
int fatorBalanceamento(NO *no) {
    if (no == NULL) return 0;
    return altura(no->esq) - altura(no->dir);
}

// Rotação simples à direita
NO* rotacaoDireita(NO *y) {
    NO *x = y->esq;
    NO *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    return x;
}

// Rotação simples à esquerda
NO* rotacaoEsquerda(NO *x) {
    NO *y = x->dir;
    NO *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    return y;
}

// Função de inserção recursiva
NO* inserirNo(NO *no, int chave) {
    // Inserção padrão de BST
    if (no == NULL) {
        NO *novo = malloc(sizeof(NO));
        novo->chave = chave;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (chave < no->chave)
        no->esq = inserirNo(no->esq, chave);
    else if (chave > no->chave)
        no->dir = inserirNo(no->dir, chave);
    else
        return no; // Chaves duplicadas não são permitidas

    // Verificar balanceamento
    int balance = fatorBalanceamento(no);

    // Casos de rotação
    // Esquerda-Esquerda
    if (balance > 1 && chave < no->esq->chave)
        return rotacaoDireita(no);

    // Direita-Direita
    if (balance < -1 && chave > no->dir->chave)
        return rotacaoEsquerda(no);

    // Esquerda-Direita
    if (balance > 1 && chave > no->esq->chave) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    // Direita-Esquerda
    if (balance < -1 && chave < no->dir->chave) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Função para inserir na árvore
void inserir(ARVORE *arvore, int chave) {
    arvore->raiz = inserirNo(arvore->raiz, chave);
}

// Função para imprimir árvore em ordem
void imprimirEmOrdem(NO *no) {
    if (no != NULL) {
        imprimirEmOrdem(no->esq);
        printf("%d ", no->chave);
        imprimirEmOrdem(no->dir);
    }
}

int main() {
    ARVORE arvore = {NULL, 0};

    // Exemplo de inserções
    inserir(&arvore, 10);
    inserir(&arvore, 20);
    inserir(&arvore, 30);
    inserir(&arvore, 40);
    inserir(&arvore, 50);
    inserir(&arvore, 25);

    printf("Árvore em ordem: ");
    imprimirEmOrdem(arvore.raiz);
    printf("\n");

    printf("%d\n", altura(arvore.raiz));

    return 0;
}