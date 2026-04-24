#include "graph.h"
#include "queue.h"
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
        add_adjacent_vertex(&g->adj[w], v);
        g->E++;
    }
}

const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size) {
    *size = g->adj[v].size;
    return g->adj[v].neighbors;
}

//BFS implementation (task 1 and 1 additional)
vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count) {
    if (!g || start >= g->V) return NULL;

    bool *visited = calloc(g->V, sizeof(bool));
    vertex_t *parent = malloc(g->V * sizeof(vertex_t));
    for(int i = 0; i < g->V; i++) parent[i] = -1;

    Queue *q = QueueInit(g->V);
    QueueEnqueue(q, start);
    visited[start] = true;
    *visited_count = 1;

    vertex_t found_end = -1;

    while (!QueueIsEmpty(q)) {
        vertex_t current = QueueDequeue(q);

//check if current it the destanation
        for (int i = 0; i < num_ends; i++) {
            if (current == ends[i]) {
                found_end = current;
                break;
            }
        }
        if (found_end != -1) break;

        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);
        for (int i = 0; i < size; i++) {
            vertex_t next = adj[i];
            if (!visited[next]) {
                visited[next] = true;
                parent[next] = current;
                (*visited_count)++;
                QueueEnqueue(q, next);
            }
        }
    }

    QueueDestroy(q);
    free(visited);

    if (found_end == -1) {
        free(parent);
        *path_len = 0;
        return NULL; //no path
    }

//reconstruct the path
    int temp_len = 0;
    vertex_t curr = found_end;
    while (curr != -1) {
        temp_len++;
        curr = parent[curr];
    }

    vertex_t *path = malloc(temp_len * sizeof(vertex_t));
    curr = found_end;
    for (int i = temp_len - 1; i >= 0; i--) {
        path[i] = curr;
        curr = parent[curr];
    }

    *path_len = temp_len;
    free(parent);
    return path;
}

//modified dfs imlementation
static void ShortestDFS(const GraphPtr g, vertex_t current, vertex_t *ends, int num_ends, 
                        vertex_t *path, int path_len, 
                        vertex_t **shortest, int *shortest_len, 
                        char *visited, int *visited_count) {
    
    visited[current] = 1;
    (*visited_count)++;
    path[path_len] = current;
    path_len++;

    bool is_end = false;
    for(int i = 0; i < num_ends; i++) {
        if(current == ends[i]) is_end = true;
    }

    if (is_end) {
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
                ShortestDFS(g, next, ends, num_ends, path, path_len, shortest, shortest_len, visited, visited_count);
            }
        }
    }
    visited[current] = 0;
}

vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count) {
    if (!g || start >= g->V) return NULL;

    vertex_t *path = malloc(sizeof(vertex_t) * g->V);
    char *visited = calloc(g->V, sizeof(char));
    vertex_t *shortest = NULL;
    int shortest_l = -1;
    *visited_count = 0;

    ShortestDFS(g, start, ends, num_ends, path, 0, &shortest, &shortest_l, visited, visited_count);

    free(path);
    free(visited);
    *path_len = shortest_l == -1 ? 0 : shortest_l;
    return shortest;
}

void GraphDestroy(GraphPtr g) {
    for (int i = 0; i < g->V; i++) free(g->adj[i].neighbors);
    free(g->adj);
    free(g);
}