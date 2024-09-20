#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "lista.h"

#ifndef STRUCTS_
    #define STRUCTS_
    struct lista_{ 
        ITEM *lista[TAM_MAX];
        int inicio; // pos do primeiro item
        int fim; // pos do próximo espaço vazio
        int tamanho;
    };
#endif

bool lista_inserir(LISTA *lista, ITEM *item){
    if(lista->tamanho == 0){
        lista->lista[0] = item;
        lista->tamanho++;
        lista->fim++;
        return true;
    }

    lista->fim++;
    lista->tamanho++;
    lista->lista[lista->fim] = NULL;

    for(int i = 0; i < lista->tamanho; i++){ //vou procurando na lista inteira (sim, sem algoritmo bonitin)
        if(item_get_chave(lista->lista[i]) < item_get_chave(item)){ //se o numero na lista for maior do que o que eu quero colocar
            for(int j = lista->fim; j >= i; j--) lista->lista[j] = lista->lista[j - 1]; //percorro a lista jogando geral depois da posição i 1 pra frente
            lista->lista[i] = item; //coloco o item na posição que abri agora
            return true;
        }
    }

    return false; //caso tenha feito tudo e nao tenha inserido retorna falso (acho que nao tem como nem chegar aqui)
}