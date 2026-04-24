#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>

void printPath(vertex_t *path, int len) {
    if (!path) {
        printf("error, no path found\n");
        return;
    }
    for (int i = 0; i < len; i++) {
        printf("%d%s", path[i], (i == len - 1) ? "" : "->");
    }
    printf("\n");
}

int main() {
    GraphPtr g = GraphInit(6);
    
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 3);
    GraphAddEdge(g, 2, 4);
    GraphAddEdge(g, 3, 4);
    GraphAddEdge(g, 3, 5);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 1, 0);
    GraphAddEdge(g, 3, 1);
    GraphAddEdge(g, 4, 0);

    int path_len;
    printf("searching shortest path from 0 to 5\n");
    vertex_t *path = GraphShortestDFS(g, 0, 5, &path_len);
    
    printf("shortest path found:\n");
    printPath(path, path_len);

    free(path);
    GraphDestroy(g);
    return 0;
}