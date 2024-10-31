#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista_{
    int *lista[TAM_MAX];
    int tam;
};

int buscabin(LISTA *l, int i, int f, int busca, int *achou);

LISTA *lista_criar(){
    LISTA *l = malloc(sizeof(LISTA));
    if(l == NULL) return NULL; //erro de alocação

    l->tam = 0;
    return l;
}

bool lista_apagar(LISTA **l){
    if(*l == NULL) return false; //caso a lista nao exista, nao há como apagar

    for(int i = 0; i < (*l)->tam; i++)
        free((*l)->lista[i]); //dou free em cada posição da lista
    
    free(*l); //libero o ponteiro da lista em si
    *l = NULL;
    return true;
}

bool lista_inserir(LISTA *l, int chave){
    if(l == NULL || l->tam == TAM_MAX) return false;

    int i = buscabin(l, 0, l->tam - 1, chave, NULL); //como só quero inserir, nao me faz diferença a flag "achou" da função, por isso passo NULL nela
    for(int j = i; j < l->tam; j++)
        l->lista[j + 1] = l->lista[j]; //desloca todas posições para direita a partir da que eu quero inserir
    

    int *novo_elem = malloc(sizeof(int)); //ponteiro que terá a chave e será alocado na lista
    if(novo_elem == NULL) return false; 
    *novo_elem = chave; 

    l->lista[i] = novo_elem;
    l->tam++; 

    return true; 
}

int lista_remover(LISTA *l, int chave){
    if(l == NULL) return ERRO;
}

void lista_imprimir(LISTA *l){
    if(l == NULL || l->tam == 0) return;

    for(int i = 0; i < l->tam; i++)
        printf("%d ", *(l->lista[i]));

    return;
}

/*como tenho que usar busca binaria tanto para insercao como remoçao, uso a mesma função com o incremento da flag "achou"*/
int buscabin(LISTA *l, int i, int f, int busca, int *achou){ //busca um numero na lista ou posição onde o ele deve ser inserido
    int m = (i + f) / 2;

    if(i > f){ //caso nao tenha achado
        *achou = 0; //flag = 0
        return i; //retorna a posição onde deve ser inserido
    }
    if(*(l->lista[m]) == busca){ //caso tenha achado
        *achou = 1; //flag = 1
        return m; //retorna a posição onde se encontra
    }

    if(*(l->lista[m]) < busca){
        return buscabin(l, m + 1, f, busca, achou);
    }else if(*(l->lista[m]) > busca){
        return buscabin(l, i, m - 1, busca, achou);
    }
    
    return -1; //a função não chega aqui, mas para evitar warning fica esse retorno
}

/*operaçoes de conjunto*/
bool lista_pertence(LISTA *l, int chave);
LISTA *lista_uniao(LISTA *l1, LISTA *l2);
LISTA *lista_interseccao(LISTA *l1, LISTA *l2);

int main(void){
    LISTA *l = lista_criar();
    lista_inserir(l, 1);
    lista_inserir(l, 2);
    lista_imprimir(l);
} //dando segfault iiiihu