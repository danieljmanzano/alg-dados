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

void lista_apagar(LISTA **l){
    if(*l == NULL) return; //caso a lista nao exista, nao há como apagar

    for(int i = 0; i < (*l)->tam; i++)
        free((*l)->lista[i]); //dou free em cada posição da lista
    
    free(*l); //libero o ponteiro da lista em si
    *l = NULL;
    return;
}

bool lista_inserir(LISTA *l, int chave){
    if(l == NULL || l->tam == TAM_MAX) return false;

    int flag = 0;
    int i = buscabin(l, 0, l->tam - 1, chave, &flag); 
    for(int j = l->tam; j > i; j--)
        l->lista[j] = l->lista[j - 1]; //desloca todas posições para direita a partir da que eu quero inserir
        
    
    int *novo_elem = malloc(sizeof(int)); //ponteiro que terá a chave e será alocado na lista
    if(novo_elem == NULL) return false; 
    *novo_elem = chave; 

    l->lista[i] = novo_elem;
    l->tam++; 

    return true; 
}

bool lista_remover(LISTA *l, int chave){
    if(l == NULL || l->tam == 0) return false;

    int flag = 0;
    int i = buscabin(l, 0, l->tam - 1, chave, &flag);

    if(!flag) return false; //caso nao tenha achado

    for(int j = i; j < l->tam - 1; j++)
        l->lista[j] = l->lista[j + 1];
    
    l->tam--;

    return true;
}   

void lista_imprimir(LISTA *l){
    if(l == NULL || l->tam == 0) return;

    for(int i = 0; i < l->tam; i++)
        printf("%d ", *(l->lista[i]));

    printf("\n");
    return;
}

/*como tenho que usar busca binaria tanto para insercao como remoçao, uso a flag "achou" para casos em que preciso buscar e remover, enquanto ignoro para quando quero apenas inserir*/
int buscabin(LISTA *l, int i, int f, int busca, int *achou){ //fora o comentário acima, a função é uma busca binária comum
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

bool lista_pertence(LISTA *l, int chave){
    if(l == NULL || l->tam == 0) return false;

    int flag = 0;
    buscabin(l, 0, l->tam - 1, chave, &flag);

    if(flag) return true;
    return false;
}

LISTA *lista_uniao(LISTA *l1, LISTA *l2){
    LISTA *uniao = lista_criar();
    if(uniao == NULL) return NULL;

    int i = 0, j = 0, cont = 0;
    while(i < l1->tam && j < l2->tam){ //pego sempre o menor numero dos dois vetores a cada iteração e avanço posição no de onde peguei
        if(*(l1->lista[i]) < *(l2->lista[j])) 
            uniao->lista[cont++] = l1->lista[i++];
            
        else if(*(l1->lista[i]) > *(l2->lista[j]))
            uniao->lista[cont++] = l2->lista[j++];

        else{ //aqui, caso os numeros sejam iguais, adiciono só uma vez
            uniao->lista[cont++] = l1->lista[i];
            i++;
            j++;
        }
    }

    while(i < l1->tam) //adiciono na uniao os restantes da lista 1 (caso existam)
        uniao->lista[cont++] = l1->lista[i++];

    while(j < l2->tam) //o mesmo para a lista 2
        uniao->lista[cont++] = l2->lista[j++];

    uniao->tam = cont;
    return uniao;
}

LISTA *lista_interseccao(LISTA *l1, LISTA *l2){
    LISTA *inter = lista_criar();
    if(inter == NULL) return NULL;

    int i = 0, j = 0, cont = 0;
    while(i < l1->tam && j < l2->tam){ //avanço uma posiçao sempre na lista com o menor numero
        if(*(l1->lista[i]) < *(l2->lista[j])) 
            i++;
            
        else if(*(l1->lista[i]) > *(l2->lista[j]))
            j++;

        else{ //quando encontro iguais, coloco na intersecçao
            inter->lista[cont++] = l1->lista[i];
            i++;
            j++;
        }
    }

    inter->tam = cont;
    if(cont == 0) printf("intersecção vazia\n");
    return inter;
}