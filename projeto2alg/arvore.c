#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct no_{
    struct no_ *esq, *dir;
    int chave;
}NO;

typedef struct arvore_{
    NO *raiz;
    int profundidade;
}ARVORE;
 
ARVORE *arvore_criar(void){
    ARVORE *t = malloc(sizeof(ARVORE));
    if(t != NULL){
        t->profundidade = -1; //uma arvore inicializada ainda nao tem nenhum nó, o que faz dela ter profundidade -1
        t->raiz = NULL;
    }
    return t;
}

NO *no_criar(int chave){
    NO *no = malloc(sizeof(NO));
    if(!no) return NULL;

    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

int altura(NO *no){ 
    if(!no) return -1;
    
    int alt_esq = altura(no->esq);
    int alt_dir = altura(no->dir);
    
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir); //vai pegar a maior altura com essa condiçao
}

int arvore_profundidade(NO *no){ //serve pra ver de subarvores tambem, só passar o nó que quiser analisar
    if(!no) return -1;
    int e = arvore_profundidade(no->esq);
    int d = arvore_profundidade(no->dir);
    return((e > d) ? e : d) + 1;
}

int fatorBalanceamento(NO *no){
    if(!no) return 0;
    return altura(no->esq) - altura(no->dir);
}

/*rotações simples e balanceamento*/
NO* rotacaoDireita(NO *desbalanceado){ 
    NO *novaRaiz = desbalanceado->esq;
    NO *subarvoreTransferida = novaRaiz->dir;

    novaRaiz->dir = desbalanceado;
    desbalanceado->esq = subarvoreTransferida;

    return novaRaiz;
}

NO* rotacaoEsquerda(NO *desbalanceado){
    NO *novaRaiz = desbalanceado->dir;
    NO *subarvoreTransferida = novaRaiz->esq;

    novaRaiz->esq = desbalanceado;
    desbalanceado->dir = subarvoreTransferida;

    return novaRaiz;
}

NO* balancear(NO *raiz) {
    int balance = fatorBalanceamento(raiz);
    
    // Rotação Esquerda-Esquerda
    if (balance > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);
    
    // Rotação Direita-Direita
    if (balance < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);
    
    // Rotação Esquerda-Direita
    if (balance > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    
    // Rotação Direita-Esquerda
    if (balance < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    
    return raiz;
}
/*--------------*/

/*funçoes juntas*/
NO *arvore_inserir_no(NO *raiz, NO *novo_no) {
    if(!raiz)
        return novo_no; //chegou às folhas: local de inserção

    else if(novo_no->chave < raiz->chave)
        raiz->esq = arvore_inserir_no(raiz->esq, novo_no);

    else if(novo_no->chave > raiz->chave)
        raiz->dir = arvore_inserir_no(raiz->dir, novo_no);
    
    return balancear(raiz);
}

bool arvore_inserir(ARVORE *t, int chave){
    if(!t) return false;

    NO *novo_no = no_criar(chave);
    if(!novo_no) return false;

    t->raiz = arvore_inserir_no(t->raiz, novo_no);
    return true;
}
/*--------------*/

/*funções juntas*/
NO* acha_menor_valor(NO* no){ //função auxiliar pra achar menor valor presente numa subarvore
    NO* atual = no;
    while(atual && atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

NO* arvore_remover_no(NO *raiz, int chave){
    if (raiz == NULL)
        return raiz;
    
    if(chave < raiz->chave)
        raiz->esq = arvore_remover_no(raiz->esq, chave);
    else if(chave > raiz->chave)
        raiz->dir = arvore_remover_no(raiz->dir, chave);
    else{ //caso tenha achado o que é pra remover

        /*pra nó com um filho ou nenhum*/
        if (raiz->esq == NULL) {
            NO *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL) {
            NO *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        
        /*pra nó com dois filhos*/
        NO *temp = acha_menor_valor(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = arvore_remover_no(raiz->dir, temp->chave);
    }
    
    if(raiz == NULL) //pra caso em que a arvore tinha só um nó (nao precisa balancear ali embaixo)
        return raiz;
    
    return balancear(raiz); //rebalancear em função do nó atual
}

bool arvore_remover(ARVORE *t, int chave) {
    if (!t || !t->raiz) return false;
    t->raiz = arvore_remover_no(t->raiz, chave);
    return true;
}

void verificar_altura(NO *raiz){ //função pra debugar, show da bola
    if(raiz == NULL) return;
    
    printf("nó %d: altura = %d, fb = %d\n", raiz->chave, altura(raiz), fatorBalanceamento(raiz));
    
    verificar_altura(raiz->esq);
    verificar_altura(raiz->dir);
}
/*--------------*/

/*funçoes juntas*/
void apagar_arvore(NO **raiz){
    if(*raiz != NULL){
        apagar_arvore(&(*raiz)->esq);
        apagar_arvore(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }

    return;
}

void arvore_apagar(ARVORE **t){
    apagar_arvore(&(*t)->raiz);
    free(*t);
    *t = NULL;
    return;
}
/*--------------*/

void imprimir_em_ordem(NO *raiz){ 
    if(raiz != NULL){
        imprimir_em_ordem(raiz->esq);
        printf("%d ", raiz->chave);
        imprimir_em_ordem(raiz->dir);
    }
    return;
}

/*pra testar as operações aqui em baixo (depois vou tirar pq nao é pra ter main aqui né)*/
int main(void){
    ARVORE *arvore = arvore_criar();

    arvore_inserir(arvore, 8);
    arvore_remover(arvore, 8);
    arvore_inserir(arvore, 4);
    arvore_inserir(arvore, 2);
    arvore_inserir(arvore, 6);
    arvore_inserir(arvore, 10);
    arvore_inserir(arvore, 5);

    printf("Árvore em ordem: ");
    imprimir_em_ordem(arvore->raiz);
    printf("\n");
    verificar_altura(arvore->raiz);


    arvore_inserir(arvore, 12);
    printf("Árvore em ordem: ");
    imprimir_em_ordem(arvore->raiz);
    printf("\n");

    verificar_altura(arvore->raiz);
    return 0;
}

/*pelo visto ta dando certo!!!!! graças a Deus!!!*/