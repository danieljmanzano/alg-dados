#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lista.h"
#include "arvore.h"

typedef struct set_{
    LISTA *l;
    ARVORE *t;
    int escolha; //aqui vou guardar qual dos dois TADs meu cliente escolheu
}SET;

SET *set_criar(int escolha){ 
    SET *s = malloc(sizeof(SET));

    if(escolha == 0){
        s->l = lista_criar();
        s->escolha = 0;
        return s;
    }else if(escolha == 1){
        s->t = arvore_criar();
        s->escolha = 1;
        return s;
    }else return NULL;
}

void set_apagar(SET **s){

}

bool set_inserir(SET *s, int chave){

}
bool set_remover(SET *s, int chave){

}
void set_imprimir(SET *s){

}

bool set_pertence(SET *s, int chave){

}
SET *set_uniao(SET *s1, SET *s2){

}
SET *set_interseccao(SET *s1, SET *s2){

}

//ainda nao fiz nada aqui nao. pretendo fazer depois q ja to pra ser expulso da biblioteca agora