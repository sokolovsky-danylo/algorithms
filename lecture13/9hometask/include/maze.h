#ifndef MAZE_H
#define MAZE_H

#include "graph.h"
#include <stdbool.h>

#define OBSTACLE '#'
#define PASSAGE '.'
#define PATH '*'
#define SOURCE 'S'
#define DEST 'L'
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
GraphPtr MazeToGraph(MazePtr m, vertex_t *start_node, vertex_t **end_nodes, int *num_ends);
void MazePrintWithPath(MazePtr m, vertex_t *path, int length);

#endif