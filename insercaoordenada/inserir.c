#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "lista.h"

//exercicio pra inserir itens ordenadamente numa lista sequencial

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
    if(lista == NULL || lista_cheia(lista)) return false;

    if(lista->tamanho == 0){ //pra colocar o primeiro (tem que ter um caso especifico pq o for ali debaixo nao funciona pra isso)
        lista->lista[0] = item;
        lista->tamanho++;
        lista->fim++;
        return true;
    }

    
    for(int i = 0; i < lista->tamanho; i++){ //vou procurando na lista inteira (sim, sem algoritmo bonitin)
        if(item_get_chave(lista->lista[i]) >= item_get_chave(item)){ //se o numero na lista for maior do que o que eu quero colocar
            for(int j = lista->fim - 1; j >= i; j--) lista->lista[j + 1] = lista->lista[j]; //percorro a lista jogando geral depois da posição i 1 pra frente
            lista->lista[i] = item; //coloco o item na posição que abri agora
            lista->fim++;
            lista->tamanho++;
            return true;
        }
    }

    lista->lista[lista->fim] = item; //caso tenha passado tudo, quer dizer que ele tem que ser colocado no fim
    lista->fim++;
    lista->tamanho++;
    return true;
}