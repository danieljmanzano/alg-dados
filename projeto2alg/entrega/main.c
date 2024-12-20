#include <stdio.h>
#include <stdlib.h>
#include "set.h"

/*Alunos:
Artur Kenzo Obara Kawazoe - 15652663
Daniel Jorge Manzano - 15446861*/

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
    SET *A, *B;
    int n_a, n_b, x;
    int op;
    int tipo;

    scanf("%d", &tipo); 

    A = set_criar(tipo);
    B = set_criar(tipo);

    scanf("%d %d", &n_a, &n_b);

    for(int i = 0; i < n_a; i++){
        scanf("%d", &x);
        set_inserir(A, x);
    }

    for(int i = 0; i < n_b; i++){
        scanf("%d", &x);
        set_inserir(B, x);
    }

    scanf("%d", &op);


    if(op == 1){ //pertence
        int chave;
        scanf("%d", &chave);
        if(set_pertence(A, chave)) 
            printf("Pertence\n");
        else
            printf("Nao pertence\n");

    }else if(op == 2){ //uniao
        SET *uniao = set_uniao(A, B);
        set_imprimir(uniao);
        set_apagar(&uniao);

    }else if(op == 3){ //remoçao
        int chave;
        scanf("%d", &chave);
        if(set_remover(A, chave))
            set_imprimir(A);
        else
            printf("remocao mal sucedida\n");

    }else if(op == 4){ //intersecçao
        SET *inter = set_interseccao(A, B);
        if(inter) set_imprimir(inter); //só imprime se nao for vazia
        set_apagar(&inter);
    }

    set_apagar(&A);
    set_apagar(&B);

    return 0;
}

