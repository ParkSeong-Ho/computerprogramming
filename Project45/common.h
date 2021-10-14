#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAZE_SIZE 10

typedef struct Mouse {
	int row;
	int col;
} Mouse;
typedef struct Stack {
	Mouse data[MAX_SIZE];
	int top;
} Stack;
char maze[MAZE_SIZE][MAZE_SIZE];
int mazeRow = 0; int mazeCol = 0;