#ifndef GRAPH_H
#define GRAPH_H
#include "vertice.h"
typedef struct graph_ Graph;
/*
 * Cria um grafo representado por um array de vertices
 * @param:
 *  int vertices: número de vértices no grafo
 *  bool isDirected: booleano que indica se o grafo é direcionado ou não
 *  bool isWeighted: booleano que indica se o grafo possui pesos em suas arestas
 *
 * @return:
 *  Graph *: ponteiro para o grafo criado*/
Graph *createGraph(int vertices, bool isDirected, bool isWeighted);
/*
 * Insere uma aresta em um dos vertices do grafo
 * @param:
 *  Graph *graph: grafo no qual será inserido a aresta
 *  int vertice1: primeiro vertice da conexão
 *  int vertice2: segundo vertice da conexão
 *  int weight: peso dessa aresta
 *
 * @return:
 *  bool: boolean indicando o sucesso da operação*/
bool insertEdge(Graph *graph, int vertice1, int vertice2, int weight);
/*
 * Retorna o peso de uma aresta especifica
 * @param:
 *  Graph* graph: grafo do qual será recuperado o peso de uma aresta
 *  int vertice1: primeiro vertice da conexão
 *  int vertice2: segundo vertice da conexão
 *
 * @return:
 *  int: peso da conexão*/
int getWeightEdge(Graph *graph, int vertice1, int vertice2);
/*
 * Retorna o número de vertices de um grafo
 * @param:
 *  Graph* graph: grafo do qual será retornado o número de vertices
 *
 * @return:
 *  int: o numero de vertices do grafo*/
int getNumberVertices(Graph *graph);

Graph *cloneGraph(Graph *graph);

/*
 * Exclui um grafo e todos os seus vertices
 * @param:
 *  Graph** graph: endereço do grafo que sera excluido
 *
 * @return: void*/
void deleteGraph(Graph **graph);
#endif