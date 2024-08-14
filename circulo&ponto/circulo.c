#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circulo.h"

struct circulo_{
    float raio;
    PONTO *centro;
};

CIRCULO *circulo_criar(PONTO *p, float raio){
    CIRCULO *c;
    c = (CIRCULO*) malloc(sizeof(CIRCULO)); 

    if(c == NULL) return NULL;
    c->centro = p;
    c->raio = raio;
    return c;
}

void circulo_apagar(CIRCULO **c){
    if(*c != NULL){
        free(*c);
        *c = NULL;
    }
    return;
}

bool circulo_set_ponto(CIRCULO *c, PONTO *p){
    if(c != NULL & p != NULL){
        c->centro = p;
        return true;
    }
    return false;
}

bool circulo_set_raio(CIRCULO *c, float raio){
    if(c != NULL){
        c->raio = raio;
        return true;
    }
    return false;
}

PONTO *circulo_get_ponto(CIRCULO *c){
    if(c != NULL){
        return c->centro;
    }
    return NULL;
}

int circulo_get_raio(CIRCULO *c){
    if(c != NULL){
        return c->raio;
    }
    exit(1);
}