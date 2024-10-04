#include "../brute.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct answer_ {
  int *path, minDistance;
};

void swap(int *n1, int *n2) {
  int temp = *n1;
  *n1 = *n2;
  *n2 = temp;
}

Answer *brute_force(Graph *graph, int start) {
  Answer *ans = malloc(sizeof(Answer));
  if (!ans) {
    return NULL;
  }
  start--;
  ans->path = malloc(sizeof(int) * (getNumberVertices(graph)));
  ans->minDistance = INT_MAX;
  int *currPath = malloc(sizeof(int) * (getNumberVertices(graph)));
  for (int i = 0; i < getNumberVertices(graph); i++) {
    currPath[i] = i + 1;
    if (i == start) {
      swap(&currPath[i], &currPath[0]);
    }
  } // O(n) sendo n o número de vértices
  bestPath(graph, &ans, currPath, 1); // O(n!) -> (n-1)!
  free(currPath);
  return ans;
}

static void bestPath(Graph *graph, Answer **ans, int *currPath, int start) {
  if (start >= getNumberVertices(graph)) {
    int current_distance = totalDistance(graph, currPath); // O(n)
    if (current_distance < (*ans)->minDistance) {
      (*ans)->minDistance = current_distance;
      memcpy((*ans)->path, currPath, getNumberVertices(graph) * sizeof(int));
    }
  } else {
    for (int i = start; i < getNumberVertices(graph); i++) {
      swap(&currPath[start], &currPath[i]);
      bestPath(graph, ans, currPath,
               start + 1); // O(n-1) -> chama sempre um for de n-1 elementos
      swap(&currPath[start], &currPath[i]);
    } // O(n)
  }
}

static int totalDistance(Graph *graph, int *currPath) {
  int total = 0;
  for (int i = 1; i < getNumberVertices(graph); i++) {
    int pesoAtual = getWeightEdge(graph, currPath[i - 1], currPath[i]);
    if (pesoAtual == INT_MAX) {
      return pesoAtual;
    }
    total += pesoAtual;
  }
  if (getWeightEdge(graph, currPath[getNumberVertices(graph) - 1],
                    currPath[0]) == INT_MAX) {
    return INT_MAX;
  }
  total +=
      getWeightEdge(graph, currPath[getNumberVertices(graph) - 1], currPath[0]);
  return total;
}

int path(Answer *ans, int index) {
  if (ans) {
    return ans->path[index];
  }
  exit(1);
}

int getMinDist(Answer *ans) {
  if (ans) {
    return ans->minDistance;
  }
  exit(1);
}

void deleteAnswer(Answer **ans) {
  if (*ans) {
    free((*ans)->path);
    free(*ans);
  }
  return;
}