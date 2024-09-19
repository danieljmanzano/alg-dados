#ifndef PILHAEHNOIS
    #define PILHAEHNOIS
    #define TAM_MAX 100

    typedef struct item ITEM;
    typedef struct pilha PILHA;

    PILHA *pilha_criar();
    void pilha_apagar(PILHA *p);
    void pilha_inserir(PILHA *p, ITEM *j);
    ITEM *pilha_remover(PILHA *p);
    int pilha_vazia(PILHA *p);
    int pilha_cheia(PILHA *p);

    ITEM *item_criar(char *nome, int over);
    int item_ponto(ITEM *item);
    char *item_nome(ITEM *item);
#endif