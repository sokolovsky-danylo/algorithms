#include "digraph.h"
#include <stdlib.h>

typedef struct {
    vertex_t *neighbors;
    int size;
    int capacity;
} Vector;

struct Digraph {
    vertex_t V;
    edge_t E;
    Vector *adj;
};

static int add_neighbor(Vector *v, vertex_t w) {
    if (v->size >= v->capacity) {
        int new_cap = v->capacity == 0 ? 4 : v->capacity * 2;
        vertex_t *new_data = realloc(v->neighbors, new_cap * sizeof(vertex_t));
        if (!new_data) return 0;
        v->neighbors = new_data;
        v->capacity = new_cap;
    }
    v->neighbors[v->size++] = w;
    return 1;
}

DigraphPtr DigraphInit(int num_vertices) {
    DigraphPtr g = malloc(sizeof(struct Digraph));
    g->V = num_vertices;
    g->E = 0;
    g->adj = calloc(num_vertices, sizeof(Vector));
    return g;
}

void DigraphAddEdge(DigraphPtr g, vertex_t v, vertex_t w) {
    if (v < g->V && w < g->V) {
        if (add_neighbor(&g->adj[v], w)) g->E++;
    }
}

vertex_t DigraphV(const DigraphPtr g) { return g->V; }
edge_t DigraphE(const DigraphPtr g) { return g->E; }

const vertex_t *DigraphAdj(const DigraphPtr g, vertex_t v, int *size) {
    *size = g->adj[v].size;
    return g->adj[v].neighbors;
}

void DigraphDestroy(DigraphPtr g) {
    for (int i = 0; i < g->V; i++) free(g->adj[i].neighbors);
    free(g->adj);
    free(g);
}