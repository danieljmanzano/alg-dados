#ifndef LISTA_H
	#define LISTA_H
    #define TAM_MAX 200
    #define ERRO -8763521

    #include <stdbool.h>

    typedef struct lista_ LISTA;

    /*operaçoes de TAD*/
    LISTA *lista_criar();
    bool lista_apagar(LISTA **lista);
    bool lista_inserir(LISTA *lista, int chave);
    int lista_remover(LISTA *lista, int chave);
    void lista_imprimir(LISTA *lista);

    /*operaçoes de conjunto*/
    bool lista_pertence(LISTA *lista, int chave);
    LISTA *lista_uniao(LISTA *lista1, LISTA *lista2);
    LISTA *lista_interseccao(LISTA *lista1, LISTA *lista2);

#endif