#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ponto.h"
#include "circulo.h"

//programa para receber coordenadas de um ponto, do centro de um circulo e do comprimento de um raio
//a partir disso usar TAD pra guardar/manipular/printar as informaçoes
//como é um problema simples nem fazia sentido usar TAD aqui (rsrsrs), era so ler e printar na mesma variavel
//mas de qualquer forma é só pra treinar usar TAD, bem do basico memo, achei daora

int main(void){
    PONTO *p, *centro; //o centro aqui eu vou usar pro circulo
    CIRCULO *c;
    float px, py, cx, cy, raio; //ponto x, ponto y, centro x, centro y

    scanf("%f %f %f %f %f", &px, &py, &cx, &cy, &raio);

    p = ponto_criar(px, py);
    centro = ponto_criar(cx, cy);
    c = circulo_criar(centro, raio);
    raio = (float)circulo_get_raio(c); //eu to só pegando o mesmo raio la de cima... mas ok to fazendo questao de usar as funçao que eu criei

    printf("Ponto: ");
    ponto_print(p);
    printf("\nCirculo: Centro ");
    ponto_print(centro);
    printf(", Raio = %.1f\n", raio);

    circulo_apagar(&c);
    ponto_apagar(&centro);
    ponto_apagar(&p);
}