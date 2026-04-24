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
void GraphDestroy(GraphPtr g);

// Modified signatures to output the number of visited nodes and support multiple targets (lamps)
vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count);
vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count);

#endif