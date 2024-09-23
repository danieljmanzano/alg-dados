#ifndef PILHAEHNOIS
    #define PILHAEHNOIS
    #define TAM_MAX 100

    typedef struct item ITEM;
    typedef struct pilha PILHA;

    PILHA *pilha_criar();
    void pilha_apagar(PILHA *p);
    void pilha_inserir(PILHA *p, ITEM *i);
    ITEM *pilha_remover(PILHA *p);
    int pilha_vazia(PILHA *p);
    int pilha_cheia(PILHA *p);
    void pilha_imprimir(PILHA *p);
    int pilha_tamanho(PILHA *p);

    ITEM *item_criar(void *chave, int num);
    int item_numero(ITEM *item);
    void *item_pont(ITEM *item);
#endif