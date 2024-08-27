#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "item.h"
#include "Pilha.h"

//exercicio em que vou receber uma sequencia de caracteres e devo fazer operações com base no algoritmo da "notação polonesa reversa" (sigla rpn no ingles)
//basicamente eu guardo os valores que recebo numa pilha e quando recebo um operador, faço a conta com os ultimos dois numeros da pilha
//ex.: 23*9+5/ == ((2 * 3) + 9) / 5 == 3 //// no caso minha entrada seria como essa primeira sequencia da linha
//aqui não tinha que implementar nenhum dos dois TADs, só fazer uso dos negocio com base nos .h que tem na pasta

float rpn(char *sequencia){
    PILHA *pilha = pilha_criar();
    float *auxf = malloc(sizeof(float) * 100);
    float *pont1 = malloc(sizeof(float));
    float *pont2 = malloc(sizeof(float));
    float *result = malloc(sizeof(float));
    void *pontaux = (void*)malloc(sizeof(void*));
    int i = 0;

    while(*sequencia != '\0'){ //42, 43, 45, 47 -> *, +, -, /
        if(*sequencia >= 48 && *sequencia <= 57){ //caso seja um numero namoral tenho que empilhar
            auxf[i] = *sequencia - 48; //aqui guardo o numero correspondente em float (tem que tirar 48 pela tabela ASCII)
            ITEM *item = item_criar(0, &auxf[i]); //uso só pra guardar o caractere que peguei agora
            if(!pilha_empilhar(pilha, item)) exit(1); //saio do codigo caso nao consiga empilhar 

        }else{ //senao, é pra ser um operador
            ITEM *item2 = pilha_desempilhar(pilha);// ja desempilho os ultimos dois numeros (a ordem ta estranha pq a ordem de operaçao é estranha mesmo)
            pont2 = item_get_dados(item2);
            ITEM *item1 = pilha_desempilhar(pilha);
            pont1 = item_get_dados(item1);
            //depois, só vou ver qual é a operação que tenho que fazer nos if
            if(*sequencia == 42){ // 42 == *
                auxf[i] = (*pont1) * (*pont2);

            }else if(*sequencia == 43){ // 43 == +
                auxf[i] = (*pont1) + (*pont2);

            }else if(*sequencia == 45){ // 45 == -
                auxf[i] = (*pont1) - (*pont2);

            }else if(*sequencia == 47){ // 47 == /
                auxf[i] = (*pont1) / (*pont2);

            }
            //tendo feito a operação, empilho um item que tenha esse resultado
            ITEM *item = item_criar(0, &auxf[i]); //uso só pra guardar o resultado que peguei no momento
            pilha_empilhar(pilha, item);
        }
        i++;
        sequencia++;
    }//obs.: fico criando os itens dentro do while pra que tenha menos perigo de acabar reutilizando algum com um endereço específico
    
    ITEM *item = item_criar(0, NULL);
    item = pilha_desempilhar(pilha); //uso pra desempilhar uma ultima vez (o que teoricamente vai ser o resultado final)
    result = item_get_dados(item);
    
    return *result;
    //nao dei nenhum free pq eles tavam me dando problema legal e nao to afim de resolver mais nada
}

//acho que foram umas 50 tentativas no runcodes, nunca mais faço isso sem implementar os .c do TAD antes
//nao ouvi o rudinei e aprendi a lição