
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

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

void readMaze(char string[]) {
	FILE* fp;
	fp = fopen(string, "r");

	while (!feof(fp)) {
		char c = fgetc(fp);
		if (c == '\n') {
			mazeRow++; mazeCol = 0;
		}
		else maze[mazeRow][mazeCol++] = c;
	}
	fclose(fp);
	mazeRow++; mazeCol--;
}

void init(Stack* p) {
	p->top = -1;
}

int isFull(Stack* p) {
	return (p->top == MAX_SIZE - 1);
}

int isEmpty(Stack* p) {
	return (p->top == -1);
}

void push(Stack* p, Mouse data) {
	if (isFull(p))
	{
		printf("Stack is full.\n");
		return;
	}
	else {
		p->top++;
		p->data[p->top].row = data.row;
		p->data[p->top].col = data.col;
	}
}

Mouse pop(Stack* p) {
	if (isEmpty(p)) {
		printf("Stack is empty.\n");
		exit(1);
	}
	return p->data[(p->top)--];
}

void pushTrace(Stack* s, int x, int y) {
	if (x<0 || y<0 || x>MAZE_SIZE || y>MAZE_SIZE) {
		return;
	}
	else if (maze[x][y] != '1' && maze[x][y] != '.') {
		Mouse tmp;
		tmp.row = x;
		tmp.col = y;

		push(s, tmp);
	}
}

void drawMap() {
	for (int row = 0; row < mazeRow; row++) {
		for (int col = 0; col < mazeCol; col++) {
			if (maze[row][col] == '0') {
				printf("□");
			}
			else if (maze[row][col] == '1') {
				printf("■");
			}
			else {
				printf("%c ", maze[row][col]);
			}
		}
		printf("\n");
	}
}

int init_mouse(Mouse* m) {
	for (int row = 0; row < MAZE_SIZE; row++) {
		for (int col = 0; col < MAZE_SIZE; col++) {
			if (maze[row][col] == 'M') {
				m->row = row;
				m->col = col;
				return 0;
			}
		}
	}
	printf("couldn't find an  entrance: fail\n");
	exit(1);
}

void appendMaze() {
	FILE* fp;
	fp = fopen("trace.txt", "a");
	if (fp == NULL) {
		puts("파일을 찾을 수 없습니다.");
		exit(1);
	}
	for (int row = 0; row < mazeRow; row++) {
		for (int col = 0; col < mazeCol; col++) {
			fputc(maze[row][col], fp);
		}
		fputc('\n', fp);
	}
	fclose(fp);
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		puts("파일 열기에 실패했습니다.\n");
		return 1;
	}
	Stack s;
	Mouse m;
	int col, row, x, y;
	FILE* fp;
	fp = fopen("trace.txt", "w");
	if (fp == NULL) {
		printf("파일을 만들 수 없습니다.\n");
		exit(1);
	}

	readMaze(argv[1]);

	init(&s);

	init_mouse(&m);

	printf("미로 \n");
	drawMap();

	printf("\n이동 경로\n");
	printf("시작 (%d, %d) -> ", m.row, m.col);
	fprintf(fp, "시작 (%d, %d) -> ", m.row, m.col);

	while (maze[m.row][m.col] != 'X') {
		x = m.row;
		y = m.col;

		maze[x][y] = '.';

		pushTrace(&s, x + 1, y);
		pushTrace(&s, x - 1, y);
		pushTrace(&s, x, y + 1);
		pushTrace(&s, x, y - 1);

		if (isEmpty(&s)) {
			printf("\n이동 경로를 찾을 수 없습니다. 실패\n");
			drawMap();
			return 0;
		}
		else {
			m = pop(&s);
			printf("(%d, %d) -> ", m.row, m.col);
			fprintf(fp, "(%d, %d) -> ", m.row, m.col);
		}
	}
	printf("도착\n");
	fprintf(fp, "도착\n");
	fclose(fp);

	drawMap();
	printf("탐색 성공\n");
	appendMaze();

	return 0;
}
