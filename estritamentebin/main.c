#include <stdio.h>

#include "item.h"
#include "ab.h"

//main pronta, nao fiz isso aq
//para a explicacao do exercicio olhar ab.c
//entrada: numero de nós / [chave do nó, lado para inserir (0 esquerda, 1 direita), chave do nó pai] <- [isso para cada nó]

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

  ab_imprimir(arvore);

  if(ab_estritamente_binaria(arvore)) {
    printf("NÃO!");
  }
  else {
    printf("É ESTRITAMENTE SIM!\n");
  }

  return 0;
}
