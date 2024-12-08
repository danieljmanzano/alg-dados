#include <stdio.h>
#include <stdlib.h>
#include "set.h"

//segundo projeto de alg
//main feita pelo rudinei

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

    scanf("%d", &tipo); //isso aqui é pra decidir o TAD mas como to so testando lista nao muda nada ainda

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
        if(inter) set_imprimir(inter); //só imprime se nao for
        set_apagar(&inter);
    }

    set_apagar(&A);
    set_apagar(&B);

    return 0;
}


//essa main aqui embaixo é para ser compativel com a entrada de txt do gerador de caso teste. servindo pra testar o codigo
//uma diferença de logica dessa pra original é que essa roda mais de um caso teste de uma vez. a original só faz uma operaçao e acaba
//depois de rodar aqui dá pra olhar o arquivo de saída esperada e comparar
//só usando o make / make run / make clean funciona tudo legal. 
/*
int main(void) {
    FILE *input_file = NULL;
    int teste = 1;

    // Abre o arquivo de casos de teste para leitura
    input_file = fopen("test_cases.txt", "r");
    if (input_file == NULL) {
        printf("Erro ao abrir o arquivo de casos de teste.\n");
        return 1;
    }

    // Loop para processar todos os casos de teste no arquivo
    while (!feof(input_file)) {
        SET *A, *B;
        int n_a, n_b, x;
        int op;
        int tipo;
        int chave;

        // Verifica se conseguiu ler o tipo de estrutura
        if (fscanf(input_file, "%d", &tipo) != 1) {
            break;  // Sai se não conseguir ler mais dados
        }

        // Cria os conjuntos
        A = set_criar(tipo);
        B = set_criar(tipo);

        // Lê o número de elementos de cada conjunto
        if (fscanf(input_file, "%d %d", &n_a, &n_b) != 2) {
            printf("Erro ao ler o número de elementos dos conjuntos no teste %d.\n", teste);
            set_apagar(&A);
            set_apagar(&B);
            break;
        }

        // Lê e insere elementos no primeiro conjunto
        for (int i = 0; i < n_a; i++) {
            if (fscanf(input_file, "%d", &x) != 1) {
                printf("Erro ao ler elemento do primeiro conjunto no teste %d.\n", teste);
                set_apagar(&A);
                set_apagar(&B);
                break;
            }
            set_inserir(A, x);
        }

        // Lê e insere elementos no segundo conjunto
        for (int i = 0; i < n_b; i++) {
            if (fscanf(input_file, "%d", &x) != 1) {
                printf("Erro ao ler elemento do segundo conjunto no teste %d.\n", teste);
                set_apagar(&A);
                set_apagar(&B);
                break;
            }
            set_inserir(B, x);
        }

        // Lê a operação
        if (fscanf(input_file, "%d", &op) != 1) {
            printf("Erro ao ler a operação no teste %d.\n", teste);
            set_apagar(&A);
            set_apagar(&B);
            break;
        }

        printf("--- Teste %d ---\n", teste);

        // Realiza a operação conforme o código original
        if (op == 1) { // pertence
            if (fscanf(input_file, "%d", &chave) != 1) {
                printf("Erro ao ler chave para operação de pertence no teste %d.\n", teste);
                set_apagar(&A);
                set_apagar(&B);
                break;
            }
            
            if (set_pertence(A, chave))
                printf("Pertence\n");
            else
                printf("Nao pertence\n");
        } else if (op == 2) { // uniao
            SET *uniao = set_uniao(A, B);
            printf("União dos conjuntos:\n");
            set_imprimir(uniao);
            set_apagar(&uniao);
        } else if (op == 3) { // remoção
            if (fscanf(input_file, "%d", &chave) != 1) {
                printf("Erro ao ler chave para operação de remoção no teste %d.\n", teste);
                set_apagar(&A);
                set_apagar(&B);
                break;
            }
            
            if (set_remover(A, chave)) {
                printf("Remoção bem sucedida. Conjunto atualizado:\n");
                set_imprimir(A);
            } else
                printf("Remoção mal sucedida\n");
        } else if (op == 4) { // intersecção
            SET *inter = set_interseccao(A, B);
            if(inter){
                printf("Intersecção dos conjuntos:\n");
                set_imprimir(inter);
            }
            set_apagar(&inter);
        }

        // Libera os conjuntos
        set_apagar(&A);
        set_apagar(&B);

        teste++;
    }

    // Fecha o arquivo
    fclose(input_file);

    printf("Total de testes processados: %d\n", teste - 1);

    return 0;
}
*/