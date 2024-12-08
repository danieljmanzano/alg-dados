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
        s->t = NULL;
        return s;
    }else if(escolha == 1){
        s->t = arvore_criar();
        s->escolha = 1;
        s->l = NULL;
        return s;
    }else return NULL; //caso a escolha nao seja correta --- obs.: em todas funçoes deixo um 'return false/NULL' (ou pelo menos pensei em algo nesse sentido) pra caso a escolha esteja errada
}

void set_apagar(SET **s){
    if(!(*s)) return;

    if((*s)->escolha == 0)
        if((*s)->l != NULL)
            lista_apagar(&((*s)->l));

    if((*s)->escolha == 1)
        if((*s)->t != NULL)
            arvore_apagar(&((*s)->t));

    free (*s);
    *s = NULL;

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

    if(s1->escolha == 0 && s2->escolha == 0){
        SET *uniao = malloc(sizeof(SET));
        if(!uniao) return NULL; //se nao criou, volta como erro
        uniao->l = lista_uniao(s1->l, s2->l);
        if(!(uniao->l)) return NULL; //outro possivel erro
        return uniao;
    }

    else if(s1->escolha == 1 && s2->escolha == 1){ //mesma coisa de cima
        SET *uniao = malloc(sizeof(SET));
        if(!uniao) return NULL;
        uniao->t = arvore_uniao(s1->t, s2->t);
        if(!(uniao->t)) return NULL;
        return uniao;
    }

    return NULL;
}

SET *set_interseccao(SET *s1, SET *s2){

    if(s1->escolha == 0 && s2->escolha == 0){
        SET *inter = malloc(sizeof(SET));
        if(!inter) return NULL; //retornos NULL na mesma logica da uniao
        inter->l = lista_interseccao(s1->l, s2->l);
        if(!(inter->l)) return NULL;
        return inter;
    }
    
    else if(s1->escolha == 1 && s2->escolha == 1){
        SET *inter = malloc(sizeof(SET));
        if(!inter) return NULL;
        inter->t = arvore_interseccao(s1->t, s2->t);
        if(!(inter->t)) return NULL;
        return inter;
    }

    return NULL;
}