#ifndef ARVORE_H
    #define ARVORE_H
    #define TAM_MAX 200
    #define ERRO -8763521

    #include <stdbool.h>

    typedef struct arvore_ ARVORE;

    /*operaçoes de TAD*/
    ARVORE *arvore_criar();
    void arvore_apagar(ARVORE **arv);
    bool arvore_inserir(ARVORE *arv, int chave);
    bool arvore_remover(ARVORE *arv, int chave);
    void arvore_imprimir(ARVORE *arv);

    /*operaçoes de conjunto*/
    bool arvore_pertence(ARVORE *arv, int chave);
    void arvore_uniao(ARVORE *arv1, ARVORE *arv2, ARVORE *nova_arvore);
    void arvore_interseccao(ARVORE *arv1, ARVORE *arv2, ARVORE *nova_arvore);
    
#endif