#include "digraph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    DigraphPtr g = DigraphInit(7);
    
    DigraphAddEdge(g, 0, 5); DigraphAddEdge(g, 0, 2); DigraphAddEdge(g, 0, 1);
    DigraphAddEdge(g, 3, 6); DigraphAddEdge(g, 3, 5); DigraphAddEdge(g, 3, 4);
    DigraphAddEdge(g, 5, 2); DigraphAddEdge(g, 6, 4); DigraphAddEdge(g, 6, 0);
    DigraphAddEdge(g, 3, 2); DigraphAddEdge(g, 1, 4);

    printf("topological sort:\n");
    vertex_t *order = topological_sort(g);
    
    for (int i = 0; i < DigraphV(g); i++) {
        printf("%d%s", order[i], (i == DigraphV(g) - 1) ? "" : " -> ");
    }
    printf("\n");

    free(order);
    DigraphDestroy(g);
    return 0;
}