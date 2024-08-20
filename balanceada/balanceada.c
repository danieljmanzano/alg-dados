#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "Pilha.h"

//a ideia do exercicio era basicamente criar uma unica função que use a TAD e as funções dos .h da pasta para analisar o "balanceamento" de uma sequencia de char (basicamente, é pra usar pilha)
//a string vai ser formada por (), {} ou []. toda vez que um desses elementos for aberto tem de existir um correspondente para fechar corretamente
//ex. de balanceados: {[()[]]}; ()[]{}([]); ({[]}) - ex. de não balanceados: {(}); ({[]}; ()]({}.
//nesse exercicio era só pra fazer essa função (tanto que o zip é só esse .c) em específico e o resto tava no runcodes pra rodar, então a pasta ta teoricamente incompleta (sem os .c dos TAD, só os .h pra dar uma ideia das funções existentes)

bool balanceada(char *sequencia){
    PILHA *pilha;
    void *pont; //nao sei pra que serve esse ponteiro aqui, mas pro item_criar precisava de um ponteiro void ent criei um
    char letra;
    pilha = pilha_criar();

    letra = sequencia[0];
    while(letra != 0){
        if(letra == '(' || letra == '{' || letra == '['){
            pilha_empilhar(pilha, item_criar(letra, pont));
        }else if((letra == ')' && !pilha_vazia(pilha)) || (letra == '}' && !pilha_vazia(pilha)) || (letra == ']' && !pilha_vazia(pilha))){
            if((letra == ')' && (char)item_get_chave(pilha_topo(pilha)) == '(') || (letra == '}' && (char)item_get_chave(pilha_topo(pilha)) == '{') || (letra == ']' && (char)item_get_chave(pilha_topo(pilha)) == '[')){
                pilha_desempilhar(pilha);
            }else return false;
        }else return false;
        sequencia++;
        letra = *sequencia;
    }

    if(pilha_vazia(pilha)) return true;
    else return false;
}