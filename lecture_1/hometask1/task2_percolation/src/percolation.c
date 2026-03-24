#include "percolation.h"
#include <stdlib.h>
#include <stdio.h>

int get_index(int n, int i, int j) {
    return i * n + j; // j - column
}

Percolation* create_percolation(int n) {
    Percolation* pc = (Percolation*)malloc(sizeof(Percolation)); //allocate memory for structure
    pc->n = n;  //size

    pc->opened_count = 0;   //no opened initially

    pc->grid = (bool*)calloc(n*n, sizeof(bool));    //allocate massive of status. calloc to 0 initially

    pc->virtual_top = n*n;      //virtual edges
    pc->virtual_bottom = n*n + 1;

    init_dynamic_connectivity(&pc->dc, n*n + 2);    //2 virtual edges, pointer cause dc is structure

    return pc;
}

void destroy_percolation(Percolation* pc) {
    free(pc->grid); //free inner massive
    free(pc);
}

int get_opened_count(Percolation* pc){
    return pc->opened_count; //return amount of oppened
}

void open_coordinate(Percolation* pc, int i, int j){
    if (i < 0 || i >= pc->n || j < 0 || j >= pc->n) return; //not to overpass limits of massive
    if (is_opened(pc, i, j)) return; //leave if oppened

    int index_now = get_index(pc->n, i, j);
    pc->grid[index_now] = true; 
    pc->opened_count++;

//connect to virtual edges  
    if (i==0) {
        add_union(&pc->dc, index_now, pc->virtual_top);

    }
    if (i == pc->n - 1) {
        add_union(&pc->dc, index_now, pc->virtual_bottom);
    }

    //connect to neighbours
    if (i > 0 && is_opened(pc, i - 1, j)) {         //neighbour above (i-1)
        add_union(&pc->dc, index_now, get_index(pc->n, i - 1, j));
    }
    if (i < pc->n - 1 && is_opened(pc, i + 1, j)) {     //neighbour under (i+1)
        add_union(&pc->dc, index_now, get_index(pc->n, i + 1, j));
    }
    if (j > 0 && is_opened(pc, i, j - 1)) {
        add_union(&pc->dc, index_now, get_index(pc->n, i, j - 1)); //neighbour left (j-1)
    }
    if (j < pc->n - 1 && is_opened(pc, i, j + 1)) {
        add_union(&pc->dc, index_now, get_index(pc->n, i, j + 1)); //neighbour right (j+1)
    }
}

bool is_opened(Percolation* pc, int i, int j) {
    if (i < 0 || i >= pc->n || j < 0 || j >= pc->n) return false; //if out of bond - closed
    return pc->grid[get_index(pc->n, i, j)]; //get index and return to massive
}
bool percolates(Percolation* pc){
    return connected(&pc->dc, pc->virtual_top, pc->virtual_bottom);
}