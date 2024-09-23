#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

//obs.: nao uso stdbool entao as funçoes que seriam tipo bool voltam um int 1 ou 0

typedef struct item{
    void *chave;
    int num;
    struct item *anterior; //o anterior aqui é o nó logo abaixo na pilha (o item aqui é meio que um nó mesmo, bagulho estranho releve)
}ITEM;

typedef struct pilha{
    ITEM *topo; 
    int tam;  
}PILHA;

PILHA *pilha_criar(){
    PILHA *p = malloc(sizeof(PILHA));
    if(p != NULL){
        p->topo = NULL;
        p->tam = 0;
    }
    return p;
}

void pilha_apagar(PILHA *p){
    if(p == NULL) return;
    ITEM *aux = malloc(sizeof(ITEM));
    while(p->tam > 0){
        aux = p->topo;
        p->topo = p->topo->anterior;
        free(aux);
        p->tam--;
    }
}

void pilha_inserir(PILHA *p, ITEM *i){ 
    if(p == NULL) return;
    if(p->topo == NULL){
        i->anterior = NULL;
        p->topo = i;
    }else{
        i->anterior = p->topo;
        p->topo = i;
        p->tam++;
    }
    return;
}

ITEM *pilha_remover(PILHA *p){
    if(p == NULL && !pilha_vazia(p)) return NULL;
    ITEM *aux = malloc(sizeof(ITEM));
    aux = p->topo;
    p->topo = p->topo->anterior;
    p->tam--;
    return aux;
}

int pilha_vazia(PILHA *p){
    if(p == NULL || p->tam == 0) return 1;
    return 0;
}

int pilha_cheia(PILHA *p){
    if(p == NULL || p->tam == TAM_MAX) return 1;
    return 0;
}

ITEM *item_criar(void *chave, int num){
    ITEM *aux = malloc(sizeof(ITEM));
    if(aux != NULL){
        aux->chave = chave;
        aux->num = num;
        aux->anterior = NULL;
    }
    return aux;
}

int item_numero(ITEM *item){
    if(item == NULL) return -1;
    return item->num;
}

void *item_pont(ITEM *item){
    if(item == NULL) return NULL;
    return item->chave;
}

void pilha_imprimir(PILHA *pilha){
    ITEM *aux = pilha->topo;
    while(aux != NULL){
        printf("%d ", aux->num);
        aux = aux->anterior;
    }
    printf("\n");
    return;
}

int pilha_tamanho(PILHA *p){
    ITEM *aux = p->topo;
    if(aux == NULL) return 0;

    int i = 0;    
    while(aux != NULL){
        aux = aux->anterior;
        i++;
    }
    return i;
}
