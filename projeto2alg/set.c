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
    if(!s) return NULL; //nao alocou

    if(escolha == 0){
        s->l = lista_criar();
        s->escolha = 0;
        return s;
    }else if(escolha == 1){
        s->t = arvore_criar();
        s->escolha = 1;
        return s;
    }else return NULL; //caso a escolha nao seja correta --- obs.: em todas funçoes deixo um 'return false/NULL' pra caso a escolha esteja errada
}

void set_apagar(SET **s){
    if((*s)->escolha == 0)
        lista_apagar(&(*s)->l);

    else if((*s)->escolha == 1)
        arvore_apagar(&(*s)->t);

    return;
}

bool set_inserir(SET *s, int chave){
    if(s->escolha == 0)
        return lista_inserir(s->l, chave);
    
    else if(s->escolha == 1)
        return arvore_inserir(s->t, chave);

    return false; 
}

bool set_remover(SET *s, int chave){
    if(s->escolha == 0)
        return lista_remover(s->l, chave);
    
    else if(s->escolha == 1)
        return arvore_remover(s->t, chave);

    return false;
}

void set_imprimir(SET *s){
    if(s->escolha == 0)
        lista_imprimir(s->l);

    else if(s->escolha == 1)
        arvore_imprimir(s->t);
    
    return;
}

bool set_pertence(SET *s, int chave){
    if(s->escolha == 0)
        return lista_pertence(s->l, chave);

    else if(s->escolha == 1)
        return arvore_pertence(s->t, chave);

    return false;
}

SET *set_uniao(SET *s1, SET *s2){
    SET *uniao;
    if(s1->escolha == 0 && s2->escolha == 0){
        uniao = set_criar(0);
        uniao->l = lista_uniao(s1->l, s2->l);
        return uniao;
    }
    else if(s1->escolha == 1 && s2->escolha == 1){
        uniao = set_criar(1);
        uniao->t = arvore_uniao(s1->t, s2->t);
        return uniao;
    }

    return NULL;
}

SET *set_interseccao(SET *s1, SET *s2){
    SET *inter;

    if(s1->escolha == 0 && s2->escolha == 0){
        inter = set_criar(0);
        inter->l = lista_interseccao(s1->l, s2->l);
        return inter;
    }
    
    else if(s1->escolha == 1 && s2->escolha == 1){
        inter = set_criar(1);
        inter->t = arvore_interseccao(s1->t, s2->t);
        return inter;
    }

    return NULL;
}