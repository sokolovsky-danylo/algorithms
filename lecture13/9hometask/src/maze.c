#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

struct Maze {      //maze structure
    char **grid;   //2D array representing the maze grid    
    int size;      //size of the maze (size x size)
    pair_t source;  //source coordinates
    pair_t *lamps;  //array of lamp coordinates (end vertices)
    int num_lamps;  //number of lamps (end vertices)
    pair_t *teleports;  //array of teleport coordinates (additional task 2)
    int num_teleports;  //number of teleports (must be even, pairs of teleports))
};

MazePtr MazeInit(int size, float obstacles_density, int num_lamps, int num_teleport_pairs) {  
    srand(time(NULL));  //seed the random number generator for maze generation
    MazePtr m = malloc(sizeof(struct Maze));    //allocate memory for the maze structure
    m->size = size;             //set the size of the maze
    m->num_lamps = num_lamps;   //set the number of lamps (end vertices)
    m->num_teleports = num_teleport_pairs * 2;  //set the number of teleports (must be even, pairs of teleports)
    
    //allocate memory for lamps and teleports arrays if needed
    m->lamps = malloc(num_lamps * sizeof(pair_t));  //allocate memory for the lamps array
    if(m->num_teleports > 0) m->teleports = malloc(m->num_teleports * sizeof(pair_t));
    //allocate memory for the teleports array if there are any teleports

    m->grid = malloc(size * sizeof(char *));    //allocate memory for the grid (array of pointers to rows)
    for (int i = 0; i < size; i++) {            //allocate memory for each row and initialize with passages
        m->grid[i] = malloc(size);              //allocate memory for the row
        for (int j = 0; j < size; j++) m->grid[i][j] = PASSAGE; //initialize all cells as free passages
    }
    int total_cells = size * size;
    int obstacles_count = (int)(total_cells * obstacles_density);
    int count = 0;
    while (count < obstacles_count) {
        int x = rand() % size;
        int y = rand() % size;
        // Ставимо стіну тільки якщо там порожньо і це не старт (0,0)
        if (m->grid[x][y] == PASSAGE && (x != 0 || y != 0)) {
            m->grid[x][y] = OBSTACLE;
            count++;
        }
    }
    m->source.x = 0; m->source.y = 0; m->grid[0][0] = SOURCE;   //start to top left corner

    //random placement of lamps (end vertices) and teleports
    for (int i = 0; i < num_lamps; i++) {
        m->lamps[i].x = rand() % size;
        m->lamps[i].y = rand() % size;
        m->grid[m->lamps[i].x][m->lamps[i].y] = DEST;
    }
    //additional task 2: random placement of teleports (must be in pairs
    for (int i = 0; i < m->num_teleports; i++) {
        m->teleports[i].x = rand() % size;
        m->teleports[i].y = rand() % size;
        m->grid[m->teleports[i].x][m->teleports[i].y] = TELEPORT;
    }

    return m;
}

static inline int get_vertex(int x, int y, int size) {  //helper function to convert 2D coordinates to vertex index for graph representation
    return x * size + y;
}

//Task 2
GraphPtr MazeToGraph(MazePtr m, vertex_t *start_node, vertex_t **end_nodes, int *num_ends) {
    int total_vertices = m->size * m->size; //number of vertices in the graph representation of the maze (each cell is a vertex)
    GraphPtr g = GraphInit(total_vertices); //create an empty graph with total_vertices vertices
    
    *start_node = get_vertex(m->source.x, m->source.y, m->size);    //set the start node index based on the source coordinates
    //set the end nodes based on the lamp coordinates
    *end_nodes = malloc(m->num_lamps * sizeof(vertex_t));
    *num_ends = m->num_lamps;
    
    for (int i = 0; i < m->num_lamps; i++) {
        (*end_nodes)[i] = get_vertex(m->lamps[i].x, m->lamps[i].y, m->size);
    }
    //massive to fast check of neighboring vertices
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    //cycle through each cell
    for (int x = 0; x < m->size; x++) { //
        for (int y = 0; y < m->size; y++) {
            if (m->grid[x][y] == OBSTACLE) continue;    //skip obstacles, they are not vertices in the graph

            int u = get_vertex(x, y, m->size);      //get the vertex index for the current cell
            for (int d = 0; d < 4; d++) {   //check neighboring vertices
                int nx = x + dx[d];
                int ny = y + dy[d];

                //check if it has neighbor, if so add vertical edge between them in the graph
                if (nx >= 0 && nx < m->size && ny >= 0 && ny < m->size && m->grid[nx][ny] != OBSTACLE) {
                    int v = get_vertex(nx, ny, m->size);
                    GraphAddEdge(g, u, v);
                }
            }
        }
    }

//Additional task 2 (teleports logic)
    for (int i = 0; i < m->num_teleports; i += 2) {     //teleports are in pairs, so we take two at a time
        int u = get_vertex(m->teleports[i].x, m->teleports[i].y, m->size);  //get the vertex index for the first teleport in the pair
        int v = get_vertex(m->teleports[i+1].x, m->teleports[i+1].y, m->size);  //get the vertex index for the second teleport in the pair
        GraphAddEdge(g, u, v); //edge connecting portals
    }

    return g;
}

void MazePrintWithPath(MazePtr m, vertex_t *path, int length) {
    //create a 2D array to mark the path cells for easy printing
    char **is_path = malloc(m->size * sizeof(char *));
    for (int i = 0; i < m->size; i++) is_path[i] = calloc(m->size, sizeof(char));

    //mark the path cells in the is_path array based on the vertex indices in the path
    for (int i = 0; i < length; i++) {
        int x = path[i] / m->size;
        int y = path[i] % m->size;
        is_path[x][y] = 1;
    }
    //print the maze grid, using different colors for source, destination, teleports, and path cells
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

void MazeDestroy(MazePtr m) {       //destroy the maze and free all allocated memory
    for (int i = 0; i < m->size; i++) free(m->grid[i]);
    free(m->grid);
    free(m->lamps);
    if(m->num_teleports > 0) free(m->teleports);
    free(m);
}