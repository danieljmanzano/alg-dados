#ifndef _ARVORE_BINARIA_H
#define _ARVORE_BINARIA_H
 
  #include  "item.h"
  #define ERRO -32000
  #define FILHO_ESQ 0
  #define FILHO_DIR 1

 typedef struct arv_bin AB;
 
 AB *ab_criar(void);
 bool ab_inserir (AB *T, ITEM *item, int lado, int chave);
 void ab_imprimir (AB *T);
 void ab_apagar_arvore(AB **T);
 
 
 int ab_estritamente_binaria (AB *T); /*Essa função devolve 0 se a Árvore é estritamente binária e 1 caso contrário*/
 
   
#endif
