#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

//codigo do rudinei pra testar o tad lista, depois que conseguir fazer 100% vou tirar da pasta

int main(int argc, char *argv[]){
    
    LISTA *lista;
    ITEM *item;
    
    lista = lista_criar(false);
        
    lista_inserir (lista, item_criar(3, NULL));
    lista_inserir (lista, item_criar(4, NULL));    
    lista_inserir (lista, item_criar(8, NULL));
    lista_inserir (lista, item_criar(12, NULL));
    lista_inserir (lista, item_criar(18, NULL));

    lista_imprimir(lista);

    item = lista_remover(lista, 18); // remove no do meio da lista
    item_apagar(&item); //apaga o item retornado. responsabilidade do chamado em vez de ser ser lista_remover(); decisão de projeto
    lista_imprimir(lista);
    
    item = lista_remover(lista, 111); //remove 1o item da lista
    item_apagar(&item);
    lista_imprimir(lista);

        
    lista_apagar(&lista);
    lista_imprimir(lista);
   	
    return (0);
}


