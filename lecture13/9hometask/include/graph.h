#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>

typedef int vertex_t;           //vertex type
typedef int edge_t;             //edge type
typedef struct Graph *GraphPtr; //graph structure declaration

GraphPtr GraphInit(int num_vertices);   //initialize graph with given number of vertices
void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w);  //add undirected edge between v and w
vertex_t GraphV(const GraphPtr g);                      //return number of vertices in the graph
edge_t GraphE(const GraphPtr g);                        //return number of edges in the graph
const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size);  //return array of adjacent vertices for vertex v, size is set to the number of adjacent vertices
void GraphDestroy(GraphPtr g);              //free memory allocated for the graph

vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count);  
//return shortest path from start to any of the end vertices using DFS

vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t *ends, int num_ends, int *path_len, int *visited_count);
//return shortest path from start to any of the end vertices using BFS
#endif