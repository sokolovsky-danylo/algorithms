#include "../include/graph.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    vertex_t *neighbors;
    int size;
    int capacity;
} Vector;

struct Graph {
    vertex_t V;
    edge_t E;
    Vector *adj;
};

static int add_adjacent_vertex(Vector *list, vertex_t v) {
    if (list->size >= list->capacity) {
        int new_cap = list->capacity == 0 ? 4 : list->capacity * 2;
        vertex_t *new_data = realloc(list->neighbors, new_cap * sizeof(vertex_t));
        if (!new_data) return 0;
        list->neighbors = new_data;
        list->capacity = new_cap;
    }
    list->neighbors[list->size++] = v;
    return 1;
}

GraphPtr GraphInit(int num_vertices) {
    GraphPtr g = malloc(sizeof(struct Graph));
    g->V = num_vertices;
    g->E = 0;
    g->adj = calloc(num_vertices, sizeof(Vector));
    return g;
}

void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w) {
    if (v < g->V && w < g->V) {
        add_adjacent_vertex(&g->adj[v], w);
        g->E++;
    }
}

const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size) {
    *size = g->adj[v].size;
    return g->adj[v].neighbors;
}

static void ShortestDFS(const GraphPtr g, vertex_t current, vertex_t end, 
                        vertex_t *path, int path_len, 
                        vertex_t **shortest, int *shortest_len, 
                        char *visited) {
    
    visited[current] = 1;
    path[path_len] = current;
    path_len++;

    if (current == end) {
        if (*shortest_len == -1 || path_len < *shortest_len) {
            *shortest_len = path_len;
            if (*shortest) free(*shortest);
            *shortest = malloc(sizeof(vertex_t) * path_len);
            memcpy(*shortest, path, sizeof(vertex_t) * path_len);
        }
    } else {
        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);
        for (int i = 0; i < size; i++) {
            vertex_t next = adj[i];
            if (!visited[next] && (*shortest_len == -1 || path_len + 1 < *shortest_len)) {
                ShortestDFS(g, next, end, path, path_len, shortest, shortest_len, visited);
            }
        }
    }

    visited[current] = 0;
}

vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len) {
    if (!g || start >= g->V || end >= g->V) return NULL;

    vertex_t *path = malloc(sizeof(vertex_t) * g->V);
    char *visited = calloc(g->V, sizeof(char));
    vertex_t *shortest = NULL;
    int shortest_l = -1;

    ShortestDFS(g, start, end, path, 0, &shortest, &shortest_l, visited);

    free(path);
    free(visited);
    *path_len = shortest_l;
    return shortest;
}

void GraphDestroy(GraphPtr g) {
    for (int i = 0; i < g->V; i++) free(g->adj[i].neighbors);
    free(g->adj);
    free(g);
}