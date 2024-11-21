#ifndef SET_H
    #define SET_H

    #include "lista.h"
    #include "arvore.h"
    #include <stdbool.h>

    typedef struct set_ SET;

    /*operaçoes de TAD*/
    SET *set_criar();
    void set_apagar(SET **s);
    bool set_inserir(SET *s, int chave);
    bool set_remover(SET *s, int chave);
    void set_imprimir(SET *s);

    /*operaçoes de conjunto*/
    bool set_pertence(SET *s, int chave);
    SET *set_uniao(SET *s1, SET *s2);
    SET *set_interseccao(SET *s1, SET *s2);

#endif