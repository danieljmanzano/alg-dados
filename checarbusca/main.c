#include <stdio.h>

#include "item.h"
#include "ab.h"

//main pronta do exercicio. olhar ab.c pra explicaçao

int main(void) {
  int n;
  scanf("%d", &n);
  
  AB* arvore = ab_criar();

  for(int i = 0; i < n; i++) {
    int chave, lado, pai;
    scanf("%d", &chave);
    scanf("%d", &lado);
    scanf("%d", &pai);

    ab_inserir(arvore, item_criar(chave, NULL), lado, pai);
  }

  if(ab_checar_busca(arvore)) {
    printf("NÃO!");
  }
  else {
    printf("É DE BUSCA SIM!\n");
  }

  return 0;
}