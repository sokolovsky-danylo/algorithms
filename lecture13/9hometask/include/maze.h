#ifndef MAZE_H
#define MAZE_H

#include "graph.h"
#include <stdbool.h>

#define OBSTACLE '#'
#define PASSAGE '.'
#define PATH '*'
#define SOURCE 'S'
#define DEST 'D'
#define TELEPORT 'T'

typedef struct {
    int x;
    int y;
} pair_t;

typedef struct Maze Maze;
typedef Maze *MazePtr;

MazePtr MazeInit(int size, float obstacles, int num_lamps, int num_teleport_pairs);
void MazePrint(MazePtr maze);
void MazeDestroy(MazePtr maze);

// Converts the Maze grid to a Graph object.
GraphPtr MazeToGraph(MazePtr m, vertex_t *start_node, vertex_t **end_nodes, int *num_ends);

// Utility to convert 1D graph path back to 2D coordinates for printing
void MazePrintWithPath(MazePtr m, vertex_t *path, int length);

#endif