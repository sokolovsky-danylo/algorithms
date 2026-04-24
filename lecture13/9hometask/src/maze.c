#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

struct Maze {
    char **grid;
    int size;
    pair_t source;
    pair_t *lamps;
    int num_lamps;
    pair_t *teleports;
    int num_teleports;
};

MazePtr MazeInit(int size, float obstacles_density, int num_lamps, int num_teleport_pairs) {
    srand(time(NULL));
    MazePtr m = malloc(sizeof(struct Maze));
    m->size = size;
    m->num_lamps = num_lamps;
    m->num_teleports = num_teleport_pairs * 2;
    
    m->lamps = malloc(num_lamps * sizeof(pair_t));
    if(m->num_teleports > 0) m->teleports = malloc(m->num_teleports * sizeof(pair_t));

    m->grid = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        m->grid[i] = malloc(size);
        for (int j = 0; j < size; j++) m->grid[i][j] = PASSAGE;
    }

    m->source.x = 0; m->source.y = 0; m->grid[0][0] = SOURCE;

    for (int i = 0; i < num_lamps; i++) {
        m->lamps[i].x = rand() % size;
        m->lamps[i].y = rand() % size;
        m->grid[m->lamps[i].x][m->lamps[i].y] = DEST;
    }

    for (int i = 0; i < m->num_teleports; i++) {
        m->teleports[i].x = rand() % size;
        m->teleports[i].y = rand() % size;
        m->grid[m->teleports[i].x][m->teleports[i].y] = TELEPORT;
    }

    return m;
}

static inline int get_vertex(int x, int y, int size) {
    return x * size + y;
}

//Task 2
GraphPtr MazeToGraph(MazePtr m, vertex_t *start_node, vertex_t **end_nodes, int *num_ends) {
    int total_vertices = m->size * m->size;
    GraphPtr g = GraphInit(total_vertices);

    *start_node = get_vertex(m->source.x, m->source.y, m->size);
    *end_nodes = malloc(m->num_lamps * sizeof(vertex_t));
    *num_ends = m->num_lamps;
    
    for (int i = 0; i < m->num_lamps; i++) {
        (*end_nodes)[i] = get_vertex(m->lamps[i].x, m->lamps[i].y, m->size);
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int x = 0; x < m->size; x++) {
        for (int y = 0; y < m->size; y++) {
            if (m->grid[x][y] == OBSTACLE) continue;

            int u = get_vertex(x, y, m->size);
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < m->size && ny >= 0 && ny < m->size && m->grid[nx][ny] != OBSTACLE) {
                    int v = get_vertex(nx, ny, m->size);
                    GraphAddEdge(g, u, v);
                }
            }
        }
    }

//Additional task 2 (teleports logic)
    for (int i = 0; i < m->num_teleports; i += 2) {
        int u = get_vertex(m->teleports[i].x, m->teleports[i].y, m->size);
        int v = get_vertex(m->teleports[i+1].x, m->teleports[i+1].y, m->size);
        GraphAddEdge(g, u, v); //edge connecting portals
    }

    return g;
}

void MazePrintWithPath(MazePtr m, vertex_t *path, int length) {
    char **is_path = malloc(m->size * sizeof(char *));
    for (int i = 0; i < m->size; i++) is_path[i] = calloc(m->size, sizeof(char));

    for (int i = 0; i < length; i++) {
        int x = path[i] / m->size;
        int y = path[i] % m->size;
        is_path[x][y] = 1;
    }

    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            if (i == m->source.x && j == m->source.y) printf(RED "%c" RESET, SOURCE);
            else if (m->grid[i][j] == DEST) printf(RED "%c" RESET, DEST);
            else if (m->grid[i][j] == TELEPORT) printf(BLUE "%c" RESET, TELEPORT);
            else if (is_path[i][j]) printf(RED "%c" RESET, PATH);
            else putchar(m->grid[i][j]);
        }
        putchar('\n');
    }

    for (int i = 0; i < m->size; i++) free(is_path[i]);
    free(is_path);
}

void MazeDestroy(MazePtr m) {
    for (int i = 0; i < m->size; i++) free(m->grid[i]);
    free(m->grid);
    free(m->lamps);
    if(m->num_teleports > 0) free(m->teleports);
    free(m);
}