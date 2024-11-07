#include <stdio.h>
#include <stdlib.h>
#include "ab.h"

//temos que implementar as operações basicas de uma arvore + uma função para analisar se a arvore é estritamente binaria
//estritamente binaria quer dizer que todos os nós têm 0 ou 2 filhos

typedef struct no_{
    struct no_ *esq, *dir;
    ITEM *item;
}NO;

typedef struct arv_bin{
    NO *raiz;
    int profundidade;
}AB;
 
AB *ab_criar(void){
    AB *arv = malloc(sizeof(AB));
    if(arv != NULL){
        arv->profundidade = -1; //uma arvore inicializada ainda nao tem nenhum nó, o que faz dela ter profundidade -1
        arv->raiz = NULL;
    }
    return arv;
}

int ab_profundidade(NO *no){
    if(no == NULL) return -1;
    int e = ab_profundidade(no->esq);
    int d = ab_profundidade(no->dir);
    return((e > d) ? e : d) + 1;
}

/*funçoes juntas*/
void ab_inserir_no(NO *raiz, NO *no, int lado, int chave){
    if(raiz != NULL){

        ab_inserir_no(raiz->esq, no, lado, chave);
        ab_inserir_no(raiz->dir, no, lado, chave);
        
        if(chave == item_get_chave(raiz->item)){
            if(lado == FILHO_ESQ)
                raiz->esq = no;
            else if(lado == FILHO_DIR)
                raiz->dir = no;
        }
    } 

    return;
}                                                  

bool ab_inserir(AB *t, ITEM *item, int lado, int chave){
    NO *aux = malloc(sizeof(NO));
    if(aux == NULL) return false;
    aux->item = item;

    if(t->raiz == NULL){ //pra quando a arvore ainda está vazia 
        aux->dir = NULL;
        aux->esq = NULL;
        t->raiz = aux;
        return true;
    }

    aux->dir = NULL;
    aux->esq = NULL;
    ab_inserir_no(t->raiz, aux, lado, chave);
    return true;
}
/*--------------*/


/*funçoes juntas*/
void imprimir_em_ordem(NO *raiz){ //como nao especifica no pdf da atividade, escolhi que printa em ordem 
    if(raiz != NULL){
        imprimir_em_ordem(raiz->esq);
        printf("%d ", item_get_chave(raiz->item));
        imprimir_em_ordem(raiz->dir);
    }
}

void ab_imprimir(AB *t){
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
        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
    }

    return;
}

void ab_apagar_arvore(AB **t){
    apagar_arvore(&(*t)->raiz);
    free(*t);
    *t = NULL;
    return;
}
/*--------------*/


/*funçoes juntas*/
int estr_bin(NO *raiz){
    if(raiz == NULL) //alcancei uma folha
        return 1;

    if((raiz->esq == NULL && raiz->dir != NULL) || (raiz->esq != NULL && raiz->dir == NULL))
        return 0;

    return (estr_bin(raiz->esq) && estr_bin(raiz->dir));
}

int ab_estritamente_binaria(AB *t){
    if(t == NULL) 
        return 0;

    return !estr_bin(t->raiz); //por algum motivo devo retornar 0 pra se é e 1 pra se nao é estritamente binaria. que ideia hein
}
/*--------------*/
