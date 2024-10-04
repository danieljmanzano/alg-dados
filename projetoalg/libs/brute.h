#ifndef BRUTE_H
#define BRUTE_H
#include "graph.h"
#include <stdlib.h>
typedef struct answer_ Answer;
/*
 *  Inicia o algoritmo de força bruta
 *  começando com um caminho padrão: 1 - 2 - 3 - .. - n
 *  @param:
 *    Graph* graph: grafo, int start: cidade inicial
 *
 *  @return:
 *    Answer* answer: ponteiro para uma struct que contêm o caminho mais
 * otimizado e a distância mínima
 *
 * */
Answer *brute_force(Graph *graph, int start);

static void bestPath(Graph *graph, Answer **ans, int *currPath, int start);
static int totalDistance(Graph *graph, int *currPath);
/*
 * Retorna a cidade no caminho dado um index
 * @param:
 *  Answer* ans: struct que guarda o caminho
 *  int index: index referente a posição da cidade no caminho
 *
 * @return:
 *  int cidade: inteiro representando o número da cidade*/
int path(Answer *ans, int index);
/* Retorna a distância mínima que foi calculada
 * @param:
 *  Answer* ans: struct que guarda a distância mínima
 *
 * @return:
 *  int distância: inteiro que representa a distância mínima calculada*/
int getMinDist(Answer *ans);
/*
 * Exclui o struct answer
 * @param:
 *  Answer **ans: endereço do struct ans
 *
 * @return:
 *  void*/
void deleteAnswer(Answer **ans);
#endif