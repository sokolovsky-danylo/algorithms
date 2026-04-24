#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <string.h>

typedef struct {            //dynamic array for neighbors
    vertex_t *neighbors;    //array of neighboring vertices
    int size;               //current number of neighbors
    int capacity;           //capacity of the neighbors array
} Vector;

struct Graph {          //graph structure   
    vertex_t V;         //number of vertices (size*size for maze graph)
    edge_t E;           //number of edges
    Vector *adj;        //array of neighbor lists
};

static int add_adjacent_vertex(Vector *list, vertex_t v) {      //add vertex v to the adjacency list, resizing if necessary
    if (list->size >= list->capacity) {                               //if no space
        int new_cap = list->capacity == 0 ? 4 : list->capacity * 2; //double the capacity
        vertex_t *new_data = realloc(list->neighbors, new_cap * sizeof(vertex_t));  //resize the neighbors array
        if (!new_data) return 0;
        list->neighbors = new_data;
        list->capacity = new_cap;
    }
    list->neighbors[list->size++] = v;              //add vertex to the list and increment size
    return 1;
}

GraphPtr GraphInit(int num_vertices) {              //initialize graph with given number of vertices
    GraphPtr g = malloc(sizeof(struct Graph));      //allocate memory for the graph structure
    g->V = num_vertices;                            //set the number of vertices
    g->E = 0;                                       //initialize edge count to 0
    g->adj = calloc(num_vertices, sizeof(Vector));  //allocate and zero-initialize the adjacency list array
    return g;
}

void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w) { //add undirected edge between v and w
    if (v < g->V && w < g->V) {                         //check if vertices are valid
        add_adjacent_vertex(&g->adj[v], w);             //add w to v's adjacency list
        add_adjacent_vertex(&g->adj[w], v);             //add v to w's adjacency lis
        g->E++;                                         //increment edge count                         
    }
}

const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size) { //return array of adjacent vertices
    *size = g->adj[v].size;                             //set size to the number of adjacent vertices
    return g->adj[v].neighbors;                   //return pointer to the adjacency list for vertex v                               
}

//BFS implementation (shortest path from start to any of the end vertices)
vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count) {
    if (!g || start >= g->V) return NULL;       //invalid graph or start vertex

    bool *visited = calloc(g->V, sizeof(bool));             //array to track visited vertices
    vertex_t *parent = malloc(g->V * sizeof(vertex_t));     //array to reconstruct the path
    for(int i = 0; i < g->V; i++) parent[i] = -1;           //initialize parent array with -1 (no parent)

    Queue *q = QueueInit(g->V);                     //initialize queue with capacity equal to number of vertices
    QueueEnqueue(q, start);                         //start to the first vertex
    visited[start] = true;                          //mark start vertex as visited
    *visited_count = 1;                             //initialize visited count

    vertex_t found_end = -1;                        //variable to store the found end vertex (lamp)


    //BFS main loop
    while (!QueueIsEmpty(q)) {                  //while there are vertices to explore
        vertex_t current = QueueDequeue(q);     //get the next vertex from the queue
        for (int i = 0; i < num_ends; i++) {    //check if current vertex is one of the end vertices
            if (current == ends[i]) {           //if it's an end vertex, we found our target
                found_end = current;            //store the found end vertex
                break;
            }
        }
        if (found_end != -1) break;             //if we found the lamp, exit the loop

        //explore adjacent vertices
        int size = 0;                                       //get the number of adjacent vertices
        const vertex_t *adj = GraphAdj(g, current, &size);  //iterate through adjacent vertices
        for (int i = 0; i < size; i++) {                    //for each adjacent vertex
            vertex_t next = adj[i];                         //if it hasn't been visited, mark it and add to the queue
            if (!visited[next]) {                           //if not visited
                visited[next] = true;                       //mark as visited
                parent[next] = current;                     //set parent for path reconstruction
                (*visited_count)++;
                QueueEnqueue(q, next);                      //add to the queue for further exploration
            }
        }
    }

    QueueDestroy(q);                                        //clean up the queue
    free(visited);                                          //free the visited array

    if (found_end == -1) {                  //if we didn't find any of the end vertices, return NULL
        free(parent);                       //free the parent array
        *path_len = 0;                      //set path length to 0
        return NULL;                        //no path
    }

//reconstruct the path
    int temp_len = 0;           //length of the path initially 0
    vertex_t curr = found_end;  //start from the found end vertex and follow the parent links back to the start vertex
    while (curr != -1) {        //while we haven't reached the start vertex (which has no parent)
        temp_len++;             //increment the path length for each vertex in the path
        curr = parent[curr];    //move to the parent vertex
    }

    //final path array to return, allocated with the correct length
    vertex_t *path = malloc(temp_len * sizeof(vertex_t));  //fill the path array in reverse order (from end to start) using the parent links
    curr = found_end;                               //start from the found end vertex again
    for (int i = temp_len - 1; i >= 0; i--) {       //fill the path array from the end to the start
        path[i] = curr;                             //set the current vertex in the path
        curr = parent[curr];                        //move to the parent vertex
    }

    *path_len = temp_len;           //set the output path length
    free(parent);                   //free the parent array/
    return path;                    //return the reconstructed path from start to the found end vertex
}

//DFS imlementation 
static void ShortestDFS(const GraphPtr g, vertex_t current, vertex_t *ends, int num_ends, 
                        vertex_t *path, int path_len, 
                        vertex_t **shortest, int *shortest_len, 
                        char *visited, int *visited_count) {
    
    visited[current] = 1;       //mark the current vertex as visited
    (*visited_count)++;         //increment the count of visited vertices
    path[path_len] = current;   //set the current vertex in the path array at the current path length index
    path_len++;                 //increment the path length for the next vertex
                            
    //check if current vertex is one of the end vertices
    bool is_end = false;                    //check if the current vertex is one of the end vertices
    for(int i = 0; i < num_ends; i++) {     //iterate through the end vertices to see if we reached one
        if(current == ends[i]) is_end = true;   //if current vertex is an end vertex, set is_end to true
    }

    if (is_end) {           //if we reached an end vertex, compare with previous shortest
        if (*shortest_len == -1 || path_len < *shortest_len) {  
            *shortest_len = path_len;
            if (*shortest) free(*shortest);
            *shortest = malloc(sizeof(vertex_t) * path_len);
            memcpy(*shortest, path, sizeof(vertex_t) * path_len);
        }
    } else {            //if not an end vertex, continue DFS on adjacent vertices
        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);  //get adjacent vertices
        for (int i = 0; i < size; i++) {                    
            vertex_t next = adj[i];
            //only continue DFS if the next vertex hasn't been visited and the current path length is less than the shortest found so far (pruning)
            if (!visited[next] && (*shortest_len == -1 || path_len + 1 < *shortest_len)) {
                ShortestDFS(g, next, ends, num_ends, path, path_len, shortest, shortest_len, visited, visited_count);
            }
        }
    }
    visited[current] = 0;       //unmark the current vertex as visited before backtracking
}
//DFS wrapper function to initialize necessary data structures and call the recursive DFS function
vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count) {
    if (!g || start >= g->V) return NULL;   //invalid graph or start vertex

    vertex_t *path = malloc(sizeof(vertex_t) * g->V);   //temporary path array to store the current path during DFS
    char *visited = calloc(g->V, sizeof(char));        //array to track visited vertices during DFS (using char for memory efficiency)/
    vertex_t *shortest = NULL;
    int shortest_l = -1;
    *visited_count = 0;

    ShortestDFS(g, start, ends, num_ends, path, 0, &shortest, &shortest_l, visited, visited_count); //call the recursive DFS function to find the shortest path

    free(path);
    free(visited);
    *path_len = shortest_l == -1 ? 0 : shortest_l;
    return shortest;
}

void GraphDestroy(GraphPtr g) {                 //free memory allocated for the graph
    for (int i = 0; i < g->V; i++) free(g->adj[i].neighbors);
    free(g->adj);
    free(g);
}