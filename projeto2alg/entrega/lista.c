#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista_{
    int *lista;
    int tam;
};

int buscabinL(LISTA *l, int i, int f, int busca, int *achou); //não coloco essa no .h, então faço o protótipo aqui mesmo

LISTA *lista_criar(){
    LISTA *l = malloc(sizeof(LISTA));
    if(!l) return NULL; //erro de alocação

    l->lista = NULL;
    l->tam = 0;
    return l;
}   

void lista_apagar(LISTA **l){
    if(*l == NULL) return; //caso a lista nao exista, nao há como apagar
    
    free((*l)->lista);
    (*l)->lista = NULL;
    free(*l); 
    *l = NULL;
    return;
}

bool lista_inserir(LISTA *l, int chave){
    if(l == NULL || l->tam == TAM_MAX) return false;

    int flag = 0;
    int i = buscabinL(l, 0, l->tam - 1, chave, &flag); 
    if(flag) return false; //ja tem ele na lista, nao insere

    l->tam++; //incremento o tamanho da lista
    l->lista = realloc(l->lista, sizeof(int) * l->tam); //realoco para o novo tamanho
    for(int j = l->tam - 1; j > i; j--)
        l->lista[j] = l->lista[j - 1]; //desloca todas posições para direita a partir da que eu quero inserir

    l->lista[i] = chave;
    return true; 
}

bool lista_remover(LISTA *l, int chave){
    if(l == NULL || l->tam == 0) return false;

    int flag = 0;
    int i = buscabinL(l, 0, l->tam - 1, chave, &flag);

    if(!flag) return false; //caso nao tenha achado

    for(int j = i; j < l->tam - 1; j++)
        l->lista[j] = l->lista[j + 1];
    
    l->tam--;
    l->lista = realloc(l->lista, sizeof(int) * l->tam);

    return true;
}   

void lista_imprimir(LISTA *l){
    if(!l) return;

    for(int i = 0; i < l->tam; i++)
        printf("%d ", l->lista[i]);

    printf("\n");
    return;
}

/*como tenho que usar busca binaria tanto para insercao como remoçao, uso a flag "achou" para casos em que preciso buscar e remover, enquanto ignoro para quando quero apenas inserir*/
int buscabinL(LISTA *l, int i, int f, int busca, int *achou){ //fora o comentário acima, a função é uma busca binária comum
    int m = (i + f) / 2;

    if(i > f){ //caso nao tenha achado
        *achou = 0; //flag = 0
        return i; //retorna a posição onde deve ser inserido
    }
    if(l->lista[m] == busca){ //caso tenha achado
        *achou = 1; //flag = 1
        return m; //retorna a posição onde se encontra
    }

    if(l->lista[m] < busca){
        return buscabinL(l, m + 1, f, busca, achou);
    }else if(l->lista[m] > busca){
        return buscabinL(l, i, m - 1, busca, achou);
    }
    
    return -1; //a função não chega aqui, mas para evitar warning fica esse retorno
}

bool lista_pertence(LISTA *l, int chave){
    if(l == NULL || l->tam == 0) return false;

    int flag = 0;
    buscabinL(l, 0, l->tam - 1, chave, &flag);

    if(flag) return true;
    return false;
}

void lista_uniao(LISTA *l1, LISTA *l2, LISTA *uniao){
    uniao->lista = malloc(sizeof(int) * (l1->tam + l2->tam));
    if(!uniao || !uniao->lista) return;

    int i = 0, j = 0, cont = 0;
    while(i < l1->tam && j < l2->tam && uniao->tam < TAM_MAX){ //pego sempre o menor numero das duas listas a cada iteração e avanço posição no de onde peguei

        if(l1->lista[i] < l2->lista[j]){
            uniao->lista[cont++] = l1->lista[i++];
            uniao->tam++;
        }
            
        else if(l1->lista[i] > l2->lista[j]){
            uniao->lista[cont++] = l2->lista[j++];
            uniao->tam++;
        }

        else{ //aqui, caso os numeros sejam iguais, adiciono só uma vez (e avanço as duas listas)
            uniao->lista[cont++] = l1->lista[i++];
            uniao->tam++;
            j++;
        }
    }

    while(i < l1->tam && uniao->tam < TAM_MAX){ //adiciono na uniao os restantes da lista 1 (caso existam)
        uniao->lista[cont++] = l1->lista[i++];
        uniao->tam++;
    }

    while(j < l2->tam && uniao->tam < TAM_MAX){ //o mesmo para a lista 2
        uniao->lista[cont++] = l2->lista[j++];
        uniao->tam++;
    }

    if(uniao->tam == TAM_MAX - 1){
        printf("espaço insuficiente para gerar a união!\n");
        exit (1);
    }

    uniao->lista = realloc(uniao->lista, sizeof(int) * uniao->tam);
    if(cont == 0) printf("união vazia");
    return;
}

void lista_interseccao(LISTA *l1, LISTA *l2, LISTA *inter){
    inter->lista = malloc(sizeof(int) * (l1->tam < l2->tam ? l1->tam : l2->tam)); //realoco a intersecção pro tamanho da menor lista
    if(!inter || !inter->lista) return;

    int i = 0, j = 0, cont = 0;
    while(i < l1->tam && j < l2->tam){ //avanço uma posiçao sempre na lista com o menor numero
        if(l1->lista[i] < l2->lista[j]) 
            i++;
            
        else if(l1->lista[i] > l2->lista[j])
            j++;

        else{ //quando encontro iguais, coloco na intersecçao
            inter->lista[cont++] = l1->lista[i++];
            inter->tam++;
            j++;
        }
    }

    inter->lista = realloc(inter->lista, sizeof(int) * inter->tam);
    if(cont == 0) printf("intersecção vazia");
    return;
}
/*
int main(void){
    LISTA *l = lista_criar();
    lista_inserir(l, 1);
    lista_inserir(l, 2);
    lista_inserir(l, 3);
    lista_inserir(l, 14);
    lista_inserir(l, 1);
    lista_imprimir(l);
    lista_remover(l, 14);
    lista_imprimir(l);
    lista_inserir(l, 128);
    lista_inserir(l, 12937);
    lista_imprimir(l);
    LISTA *l2 = lista_criar();
    lista_inserir(l2, 3);
    lista_inserir(l2, 1);
    lista_inserir(l2, 14);
    lista_inserir(l2, 312123);
    LISTA *inter = lista_criar();
    lista_interseccao(l, l2, inter);
    lista_imprimir(inter);
    printf("oi\n");
}
*/