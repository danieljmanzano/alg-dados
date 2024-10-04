#include "../graph.h"
#include <stdlib.h>

struct graph_ {
  int numVertices;
  Vertice **vertices;
  bool isDirected, isWeighted;
};

Graph *createGraph(int vertices, bool isDirected, bool isWeighted) {
  Graph *graph = malloc(sizeof(Graph));
  if (!graph) {
    return NULL;
  }
  graph->vertices = createVerticeList(vertices);
  if (!graph->vertices) {
    free(graph);
    graph = NULL;
    return NULL;
  }
  for (int i = 0; i < vertices; i++) {
    graph->vertices[i] = createVertice();
    if (!graph->vertices[i]) {
      while (i--) {
        deleteVertice(&graph->vertices[i]);
      }
      free(graph->vertices);
      graph->vertices = NULL;
      free(graph);
      graph = NULL;
      return NULL;
    }
  }
  graph->numVertices = vertices;
  graph->isDirected = isDirected;
  graph->isWeighted = isWeighted;
  return graph;
}

bool insertEdge(Graph *graph, int vertice1, int vertice2, int weight) {
  vertice1--;
  vertice2--;
  if (graph->isDirected) {
    if (graph->isWeighted) {
      createConnection(graph->vertices[vertice1], vertice2, weight);
      return true;
    } else {
      createConnection(graph->vertices[vertice1], vertice2, 0);
      return true;
    }
  } else {
    if (graph->isWeighted) {
      createConnection(graph->vertices[vertice1], vertice2, weight);
      createConnection(graph->vertices[vertice2], vertice1, weight);
      return true;
    } else {
      createConnection(graph->vertices[vertice1], vertice2, 0);
      createConnection(graph->vertices[vertice2], vertice1, 0);
      return true;
    }
  }
  return false;
}

int getWeightEdge(Graph *graph, int vertice1, int vertice2) {
  if (!graph) {
    exit(1);
  }
  vertice1--;
  vertice2--;
  return getWeightConnection(graph->vertices[vertice1], vertice2);
}

int getNumberVertices(Graph *graph) {
  if (!graph) {
    exit(1);
  }
  return graph->numVertices;
}

Graph *cloneGraph(Graph *graph) {
  Graph *newGraph =
      createGraph(graph->numVertices, graph->isDirected, graph->isWeighted);
  for (int i = 0; i < graph->numVertices; i++) {
    newGraph->vertices[i] = cloneVertice(graph->vertices[i]);
  }
  return newGraph;
}

void deleteGraph(Graph **graph) {
  if (*graph) {
    int vertices = (*graph)->numVertices;
    for (int i = 0; i < vertices; i++) {
      deleteVertice(&(*graph)->vertices[i]);
    }
    free((*graph)->vertices);
    (*graph)->vertices = NULL;
    free((*graph));
    (*graph) = NULL;
  }
  return;
}