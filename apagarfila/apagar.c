#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "fila.h"
//atividade para implementar só a função de apagar uma fila recursivamente (sim, só isso)
//essa recursão nem é tão recursão mesmo, mas nao tinha outro jeito de fazer assim

#ifndef _STRUCTS_
    #define _STRUCTS_

    typedef struct no_ {
    ITEM* item;
    struct no_* proximo;
    }noObj;

    typedef noObj NO;

    typedef struct fila_ {
    NO* inicio;
    NO* fim;
    int tamanho;
    }filaObj;

    typedef filaObj FILA;

#endif
//esse ifndef é só pra nao dar erro no runcodes

void fila_apagar(FILA **f){

    if(fila_tamanho(*f) == 0){//caso base: ja tirou tudo que tinha na fila
        free(*f);
        *f = NULL;
        return;
    }

    item_apagar(&(*f)->inicio->item);
    free(fila_remover(*f)); //o fila_remover tira o item no inicio da fila e anda uma posição
    //só com essa linha de cima entao dou conta de tirar o que preciso e ir pra frente, aí só repetir até acabar
    fila_apagar(f);
}