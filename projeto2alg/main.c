#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//segundo projeto de alg
//ate o momento so fiz a a parte da lista sequencial

/*Implementar o TAD Conjunto de modo que o usuário possa escolher entre 2 a
Estruturas de Dados que implementam o conjunto. Ou seja, o TAD Conjunto deve ser
cliente de 2 outros TADs, sendo que um será escolhido pelo usuário em tempo de
execução. A escolha das Estruturas de Dados dos TADs de suporte ao Conjunto é
livre. Entretanto, as estruturas escolhidas devem possibilitar que as operações
específicas do Conjunto tenham a menor complexidade computacional possível.
As operações consideradas são:
- 1) Operações básicas para TADs em geral: Criar (um conjunto), Apagar (um
conjunto), Inserir (um elemento em um conjunto), Remover (um elemento de um
conjunto) e Imprimir (imprimir os elementos armazenados no Conjunto).
- 2) Operações específicas de conjuntos: Pertence (um elemento está presente
ou não no conjunto), União entre 2 Conjuntos, Intersecção entre 2 Conjuntos. Note
que essas 2 útlimas operações recebem como entrada 2 conjuntos e devolvem um
terceiro conjunto como resposta.*/

int main(void){ 
    LISTA *A, *B;
    int n_a, n_b, x;
    int op;
    int tipo;

    scanf("%d", &tipo); //isso aqui é pra decidir o TAD mas como to so testando lista nao muda nada ainda

    A = lista_criar();
    B = lista_criar();

    scanf("%d %d", &n_a, &n_b);

    for(int i = 0; i < n_a; i++){
        scanf("%d", &x);
        lista_inserir(A, x);
    }

    for(int i = 0; i < n_b; i++){
        scanf("%d", &x);
        lista_inserir(B, x);
    }

    scanf("%d", &op);


    if(op == 1){ //pertence
        int chave;
        scanf("%d", &chave);
        if(lista_pertence(A, chave)) //lembrando que o pertence é pra analisar na primeira lista sempre
            printf("Pertence\n");
        else
            printf("Nao pertence\n");

    }else if(op == 2){ //uniao
        LISTA *uniao = lista_uniao(A, B);
        lista_imprimir(uniao);
        free(uniao);

    }else if(op == 3){ //remoçao
        int chave;
        scanf("%d", &chave);
        if(lista_remover(A, chave)){
            printf("remocao bem sucedida\n");
            lista_imprimir(A);
        }else
            printf("remocao mal sucedida\n");

    }else if(op == 4){ //intersecçao
        LISTA *inter = lista_interseccao(A, B);
        lista_imprimir(inter);
        free(inter);
    }

    return 0;
}