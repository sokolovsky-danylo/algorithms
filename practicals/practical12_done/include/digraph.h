#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <stdbool.h>
#include <stdio.h>

typedef int vertex_t;
typedef int edge_t;
typedef struct Digraph *DigraphPtr;

DigraphPtr DigraphInit(int num_vertices);
void DigraphAddEdge(DigraphPtr g, vertex_t v, vertex_t w);
vertex_t DigraphV(const DigraphPtr g);
edge_t DigraphE(const DigraphPtr g);
const vertex_t *DigraphAdj(const DigraphPtr g, vertex_t v, int *size);
void DigraphPrint(const DigraphPtr g);
void DigraphDestroy(DigraphPtr g);

vertex_t* topological_sort(const DigraphPtr g);

#endif