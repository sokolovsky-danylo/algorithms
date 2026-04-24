#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>

typedef int vertex_t;
typedef int edge_t;
typedef struct Graph *GraphPtr;

GraphPtr GraphInit(int num_vertices);
void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w);
vertex_t GraphV(const GraphPtr g);
edge_t GraphE(const GraphPtr g);
const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size);
void GraphPrint(const GraphPtr g);
void GraphDestroy(GraphPtr g);

vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len);

#endif