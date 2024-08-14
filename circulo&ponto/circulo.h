#ifndef CIRCULO_H
    #define CIRCULO_H
    #include "ponto.h"

    typedef struct circulo_ CIRCULO;

    CIRCULO *circulo_criar (PONTO *p, float raio);
    void circulo_apagar (CIRCULO **circulo);
    bool circulo_set_ponto (CIRCULO *c, PONTO *p);
    bool circulo_set_raio (CIRCULO *c, float raio);
    PONTO *circulo_get_ponto (CIRCULO *c);
    int circulo_get_raio (CIRCULO *c);
    
#endif
