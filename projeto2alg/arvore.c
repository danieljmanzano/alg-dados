#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

/*coloquei as funçoes do ultimo exercicio de alg, mas acho que nem todas vao ser aplicaveis aqui.
de qualquer forma, vou tentar começar por elas pra desenvolver as que vou usar namoral*/

typedef struct no_{
    struct no_ *esq, *dir;
    int chave;
}NO;

typedef struct arvore_{
    NO *raiz;
    int profundidade;
}ARVORE;
 
ARVORE *arvore_criar(void){
    ARVORE *arv = malloc(sizeof(ARVORE));
    if(arv != NULL){
        arv->profundidade = -1; //uma arvore inicializada ainda nao tem nenhum nó, o que faz dela ter profundidade -1
        arv->raiz = NULL;
    }
    return arv;
}

int arvore_profundidade(NO *no){
    if(no == NULL) return -1;
    int e = arvore_profundidade(no->esq);
    int d = arvore_profundidade(no->dir);
    return((e > d) ? e : d) + 1;
}

/*funçoes juntas*/
void arvore_inserir_no(NO *raiz, NO *no, int lado, int chave_pai){
    if(raiz != NULL){

        arvore_inserir_no(raiz->esq, no, lado, chave_pai);
        arvore_inserir_no(raiz->dir, no, lado, chave_pai);
        
        if(chave_pai == raiz->chave){
            if(lado == FILHO_ESQ)
                raiz->esq = no;
            else if(lado == FILHO_DIR)
                raiz->dir = no;
        }
    } 

    return;
}                                                  

bool arvore_inserir(ARVORE *t, int inserir, int lado, int chave_pai){
    NO *aux = malloc(sizeof(NO));
    if(aux == NULL) return false;
    aux->chave = inserir;

    if(t->raiz == NULL){ //pra quando a arvore ainda está vazia 
        aux->dir = NULL;
        aux->esq = NULL;
        t->raiz = aux;
        return true;
    }

    aux->dir = NULL;
    aux->esq = NULL;
    arvore_inserir_no(t->raiz, aux, lado, chave_pai);
    return true;
}
/*--------------*/


/*funçoes juntas*/
void imprimir_em_ordem(NO *raiz){ //como nao especifica no pdf da atividade, escolhi que printa em ordem 
    if(raiz != NULL){
        imprimir_em_ordem(raiz->esq);
        printf("%d ", raiz->chave);
        imprimir_em_ordem(raiz->dir);
    }
}

void arvore_imprimir(ARVORE *t){
    printf("árvore em ordem: ");
    imprimir_em_ordem(t->raiz);
    printf("\n");
    return;
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

void arvore_apagar_arvore(ARVORE **t){
    apagar_arvore(&(*t)->raiz);
    free(*t);
    *t = NULL;
    return;
}
/*--------------*/
