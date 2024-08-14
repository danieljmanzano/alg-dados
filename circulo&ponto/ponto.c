#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ponto.h"

struct ponto_{
    float x;
    float y;
};

PONTO *ponto_criar(float x, float y){
    PONTO *ponto;
    ponto = (PONTO*) malloc(sizeof(PONTO));
    if(ponto == NULL) return NULL;

    ponto->x = x;
    ponto->y = y;
    return ponto;
}

void ponto_apagar(PONTO **p){
    if(*p != NULL){
        free(*p);
        *p = NULL;
    }
    return;
}

bool ponto_set(PONTO *p, float x, float y){
    if(p != NULL){
        p->x = x;
        p->y = y;
        return true;
    }
    return false;
}

float ponto_get_x(PONTO *p){
    if(p != NULL) return p->x;
    else return 0;
}

float ponto_get_y(PONTO *p){
    if(p != NULL) return p->y;
    else return 0;
}

void ponto_print(PONTO *p){
    if(p != NULL) printf("(%.1f, %.1f)", p->x, p->y);
    else return;
}
