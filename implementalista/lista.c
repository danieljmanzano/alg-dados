#include <stdio.h>
#include <stdlib.h>
#include "item.h"

#define TAM_MAX 100 //nem sei o tamanho maximo, coloquei qqr coisa so pra funcionar a logica direito

//tentando implementar uma lista encadeada

typedef struct node_{
    struct node_ *anterior;
    struct node_ *prox;
    ITEM *item;
}NO;

typedef struct lista_{
    NO *inicio;
    NO *fim;
    int tam;
    int ordenada; //mexendo aqui vou saber se to mexendo numa lista ordenada ou não
}LISTA;

LISTA *lista_criar(){
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));

    if(lista != NULL){
        lista->fim = lista->inicio; //coloco o fim no inicio, quer dizer que ta vazia ainda
        lista->tam = 0;
    }
    return lista;
}

void lista_apagar(LISTA **lista){
    NO *aux = (NO*)malloc(sizeof(NO));
    aux = (*lista)->inicio;

    for(int i = 0; i < (*lista)->tam; i++){
        if(aux->prox == NULL) break; //só pra garantir que nao vou sair do tanto que tenho que andar
        aux = aux->prox;
        free(aux->anterior);
        aux->anterior = NULL;
    }

    free(*lista);
    *lista = NULL;
}

int lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL || lista_cheia(lista)) return 0;
}

int lista_cheia(LISTA *lista){
    if(lista->tam == TAM_MAX || lista == NULL) return 1; //retorno que ta cheia caso ta paia de mexer nela (se ta cheia ou ela nao existe)
    return 0;
}

int lista_vazia(LISTA *lista){
    if(lista->tam == 0 || lista == NULL) return 1;
    return 0;
}

//ainda em progresso