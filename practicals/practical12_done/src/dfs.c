#include "../include/digraph.h"
#include <stdlib.h>

static void dfs_order(const DigraphPtr g, vertex_t v, bool *marked, vertex_t *res, int *pos) {
    marked[v] = true;
    int size;
    const vertex_t *adj = DigraphAdj(g, v, &size);
    
    for (int i = 0; i < size; i++) {
        if (!marked[adj[i]]) {
            dfs_order(g, adj[i], marked, res, pos);
        }
    }
    res[(*pos)--] = v; 
}

vertex_t* topological_sort(const DigraphPtr g) {
    int V = DigraphV(g);
    vertex_t *result = malloc(sizeof(vertex_t) * V);
    bool *marked = calloc(V, sizeof(bool));
    int pos = V - 1;

    for (int v = 0; v < V; v++) {
        if (!marked[v]) {
            dfs_order(g, v, marked, result, &pos);
        }
    }

    free(marked);
    return result;
}