#include "maze.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int maze_size = 10;
    float obstacles = 0.2f;
    int num_lamps = 2; //additional task 1
    int num_teleports = 1; //additional task 2

    printf("Generating maze...\n");
    MazePtr maze = MazeInit(maze_size, obstacles, num_lamps, num_teleports);
    
    vertex_t start_node;
    vertex_t *end_nodes;
    int num_ends;

    GraphPtr g = MazeToGraph(maze, &start_node, &end_nodes, &num_ends);

    int path_len_bfs, visited_bfs;
    int path_len_dfs, visited_dfs;

    printf("\nRunning BFS \n");
    vertex_t *path_bfs = GraphShortestBFS(g, start_node, end_nodes, num_ends, &path_len_bfs, &visited_bfs);
    if (path_bfs) {
        printf("BFS path found, length: %d, nodes visited: %d\n", path_len_bfs, visited_bfs);
        MazePrintWithPath(maze, path_bfs, path_len_bfs);
        free(path_bfs);
    } else {
        printf("no path found with BFS.\n");
    }

    printf("\nRunning DFS \n");
    vertex_t *path_dfs = GraphShortestDFS(g, start_node, end_nodes, num_ends, &path_len_dfs, &visited_dfs);
    if (path_dfs) {
        printf("DFS path found, length: %d, nodes visited: %d\n", path_len_dfs, visited_dfs);
        free(path_dfs);
    } else {
        printf("no path found with DFS.\n");
    }

    free(end_nodes);
    GraphDestroy(g);
    MazeDestroy(maze);
    
    return 0;
}