#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "item.h"
#include "lista.h"

#define TAM_MAX 100 //nem sei o tamanho maximo, coloquei qqr coisa so pra funcionar a logica direito

//tentando implementar uma lista encadeada (do tipo simples)

typedef struct node_{
    struct node_ *prox;
    ITEM *item;
}NO;

typedef struct lista_{
    NO *inicio;
    NO *fim;
    int tam;
    bool ordenada; //mexendo aqui vou saber se to mexendo numa lista ordenada ou não
}LISTA;

LISTA *lista_criar(bool ordenada){
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
    lista->inicio = malloc(sizeof(NO));

    if(lista != NULL){
        lista->fim = lista->inicio; //coloco o fim no inicio, quer dizer que ta vazia ainda
        lista->tam = 0;
        lista->ordenada = ordenada;
    }
    return lista;
}

bool lista_apagar(LISTA **lista){
    if(*lista == NULL) return false; //caso a lista nao exista nao tem como apagar né

    NO *aux = (*lista)->inicio;
    while(aux->prox != NULL){
        ITEM *apaga = aux->item; //uso pra apagar o item do nó
        NO *apaga2 = aux; //uso pra apagar o nó
        aux = aux->prox; //vou pro proximo
        free(apaga);
        apaga = NULL;
        free(apaga2);
        apaga2 = NULL;
    }

    free(*lista);
    (*lista) = NULL;
    return true;
}

bool lista_inserir_fim(LISTA *lista, ITEM *item){  //essa nao ta no tad mas tenho que usar como parte da inserir
    NO *aux = malloc(sizeof(NO));
    if(aux == NULL) return false; //caso nao tenha alocado certo

    aux->item = item;
    lista->fim->prox = aux; 
    lista->fim = aux; //fazer isso (junto da linha de cima) meio que conecta o aux na lista certin, aí acaba meus problema
    lista->tam++;
    return true;
}

bool lista_ordenada_inserir(LISTA *lista, ITEM *item){ //mesmo caso da função de cima, nao ta no tad mas preciso
    NO *aux = lista->inicio;

    if(item_get_chave(item) < item_get_chave(aux->item)){ //pro caso de que preciso inserir logo no começo (no for embaixo eu pulo a primeira posição)
        aux = NULL; //tiro o aux do inicio só pra ter ctz que nao dá problema
        aux = malloc(sizeof(NO));
        aux->prox = lista->inicio;
        aux->item = item;
        lista->inicio = aux;
        lista->tam++;
        return true;
    }

    while(aux->prox != NULL){
        if(item_get_chave(item) <= item_get_chave(aux->prox->item)){ //se o item recebido é maior que o da lista, insiro ele ali 
            NO *aux2 = malloc(sizeof(NO)); //como o aux é só um guia pela lista preciso de outro auxiliar pr colocar o bagulho la dentro
            if(aux2 == NULL) return false; //caso nao tenha alocado certo
            aux2->item = item;
            aux2->prox = aux->prox;
            aux->prox = aux2;
            lista->tam++;
            return true;
        }else aux = aux->prox; //se nao achei eu ando o aux pra frente (pego a proxima posição da lista)
    }//se consegui sair do while quer dizer que o recebido é maior que geral da lista, entao coloco no fim
    return lista_inserir_fim(lista, item);
}


bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL || lista_cheia(lista)) return false;

    if(lista->tam == 0){
        lista->inicio->item = item;
        lista->tam++;
        return true;
    }

    if(lista->ordenada) //se a lista é ordenada, vou procurando (ordenadamente) onde o item tem que ser colocado
        return lista_ordenada_inserir(lista, item);
    else //se nao é ordenada só coloco no fim mesmo
        return lista_inserir_fim(lista, item);
}

ITEM *lista_remover(LISTA *lista, int chave){
    if(lista == NULL || lista_vazia(lista)) return NULL;

    if(lista->tam == 1 && chave == item_get_chave(lista->inicio->item)){ //tem que ter um caso pra 1 pq se nao eu acabo colocando o inicio onde nao devia
        ITEM *aux = lista->fim->item;
        lista->fim->item = NULL;
        lista->tam--;
        return aux;
    }

    if(chave == item_get_chave(lista->inicio->item)){ //faço essa pq ali no while eu pulo a primeira posição
        ITEM *aux = lista->inicio->item;
        NO *auxno = lista->inicio;
        lista->inicio = lista->inicio->prox; //coloco o inicio 1 pra frente (tive que retirar o item dali, entao tenho que andar 1)
        free(auxno);
        lista->tam--;
        return aux;
    }

    NO *aux = lista->inicio;
    while(aux->prox != NULL){ //vou percorrer a lista atras da chave especifica
        if(item_get_chave(aux->prox->item) == chave){ //achei o item a ser removido
            ITEM *auxitem = aux->prox->item;
            NO *auxno = aux->prox;
            aux->prox = aux->prox->prox; //pulo a posição que apaguei
            free(auxno);
            lista->tam--;
            return auxitem;
        }
        aux = aux->prox;
    }

    return NULL; //caso depois de todas as buscas eu nao tenha achado quer dizer que nao tava la pra apagar (aí retorna nada)
}

bool lista_cheia(LISTA *lista){
    if(lista->tam == TAM_MAX || lista == NULL) return true; //retorno que ta cheia caso ta paia de mexer nela (se ta cheia ou ela nao existe)
    return false;
}

bool lista_vazia(LISTA *lista){
    if(lista->tam == 0 || lista == NULL) return true; //mesma coisa de cima (se ta vazia ou ela nao existe)
    return false;
}

void lista_imprimir(LISTA *lista){ //so o basico 
    if(lista == NULL) return;

    NO *aux = lista->inicio;
    while(aux != NULL && aux->item != NULL){
        printf("%d ", item_get_chave(aux->item));
        aux = aux->prox;
    }
    printf("\n");
    return;
}

int lista_tamanho(LISTA *lista){
    if(lista == NULL) return 0;
    return lista->tam;
}
//ate entao nao achei nenhum erro aqui, daora