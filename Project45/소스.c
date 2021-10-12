//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//
//#define MAX_ROW 10
//#define MAX_COL 10
//#define MAX_STACK_SIZE 100 //스택의 최대 크기
//#define TRUE 1                //TRUE의 초기화
//#define FALSE 0                //false의 초기화
//#define EXIT_ROW MAX_ROW-1
//#define EXIT_COL MAX_COL-1
//
//typedef struct {                        //element 재정의
//    short int row;
//    short int col;
//    short int dir;
//}element;
//
//typedef struct {
//    short int vert;
//    short int horiz;
//}offsets;
//
//offsets move[8] = { {-1, 0},        //여덟 방향 이동에 대한 배열
//                                {-1,1},
//                                {0,1},
//                                {1,1},        //남동쪽
//                                {1,0},
//                                {1,-1},
//                                {0,-1},
//                                {-1,-1}        //북서쪽
//};
//
//
//element stack[MAX_STACK_SIZE];
//
//int maze[MAX_ROW][MAX_COL];                //미로선언
//int mark[MAX_ROW][MAX_COL];                //지나온 배열 선언
//
////사용될 함수 선언
//void path();
//element add(int* top, element position);
//element delete(int* top);
//
//int main(void) {
//    int i, j;
//
//    //미로 생성 사방을 벽으로 둘러싸고 시작지점인 maze[1][1] 은 0으로 설정
//    //commit 어디가 출구인지를 만들지 않았다.그부분을 수정해서 올려보겠다 
//    srand((unsigned)time(NULL));
//    for (i = 0; i < MAX_ROW; i++)
//        for (j = 0; j < MAX_COL; j++) {
//            if (i == 1 && j == 1)
//                maze[i][j] = 0;
//            else if (i == 0 || j == 0 || i == MAX_ROW - 1 || j == MAX_COL - 1)
//                maze[i][j] = 1;
//            else
//                maze[i][j] = rand() % 2;
//        }
//    //생성된 배열을 출력
//    printf("*********** create maze ***********\n");
//    printf("    ");
//    for (j = 0; j < MAX_COL; j++)
//        printf("%2d ", j);                        //보기 편하도록 COL 을 출력
//    printf("\n\n");
//    for (i = 0; i < MAX_ROW; i++) {
//        printf("%2d  ", i);                        //보기 편하도록 ROW 를 출력
//        for (j = 0; j < MAX_COL; j++)
//            printf(" %d ", maze[i][j]);
//        printf("\n");
//    }
//    printf("\n");
//
//    for (i = 0; i < MAX_ROW; i++)
//        for (j = 0; j <= MAX_COL; j++)
//            mark[i][j] = 0;
//    printf("******** maze road ********\n");
//    path();
//
//    return 0;
//}
//
//element add(int* top, element position)                        //스택에 삽입
//{
//    (*top)++;
//    stack[*top].row = position.row;
//    stack[*top].col = position.col;
//    stack[*top].dir = position.dir;
//}
//
//
//element delete(int* top)                                                //스택에서 꺼냄
//{
//    element result;
//    if (*top < 0) {
//        printf("Stack is Empty.\n");
//    }
//    else {
//        result = stack[*top];
//        (*top)--;
//    }
//    return result;
//}
//
//void path()
//{
//    //미로를 통과하는 경로가 있으면 그 경로를 출력한다
//    int i, row, col, next_row, next_col, dir, found = FALSE;
//    int top;
//    element position;
//    mark[1][1] = 1;
//    top = 0;
//    stack[0].row = 1;
//    stack[0].col = 1;
//    stack[0].dir = 1;
//
//    while (top > -1 && !found) {
//        position = delete(&top);                        //스택에서 꺼냄
//        row = position.row;
//        col = position.col;
//        dir = position.dir;
//        while (dir < 8 && !found) {                        //dir방향으로 이동
//            next_row = row + move[dir].vert;
//            next_col = col + move[dir].horiz;
//            if (next_row == EXIT_ROW && next_col == EXIT_COL)
//                found = TRUE;
//            else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
//                mark[next_row][next_col] = 1;
//                position.row = row;
//                position.col = col;
//                position.dir = ++dir;
//                add(&top, position);                //스택에 삽입
//                row = next_row;
//                col = next_col;
//                dir = 0;
//            }
//            else ++dir;
//        }
//    }
//    if (found) {                                                                //길을 찾으면 출력
//        printf("The path is : \n");
//        printf("row col\n");
//        for (i = 0; i <= top; i++)
//            printf("%2d%5d\n", stack[i].row, stack[i].col);
//        printf("%2d%5d\n", row, col);
//    }
//    else printf("The maze dose not have a path\n");
//}
//
//#include <stdio.h>
//struct pos {
//	int i;
//	int j;
//};
//
//struct pos stack[100];
//
//int top = -1;
//
//void pop() {
//	top--;
//}
//void push(int i, int j) {
//	top++;
//	stack[top].i = i;
//	stack[top].j = j;
//}
//int maze[5][5] = {
//	{1,0,1,1,1},
//	{0,0,0,0,0},
//	{1,0,1,1,0},
//	{1,0,0,0,0},
//	{1,1,2,1,1},
//};
//int check[5][5] = { 0, };
//
//void search(int i, int j) {
//	if (maze[i][j] == 1) {
//		return;
//	}
//	push(i, j);
//	check[i][j] = 1;
//	if (maze[i][j] == 2) {
//		printf("EXIT\n");
//		for (int k = 0; k <= top; k++) {
//			printf("(%d %d) ", stack[k].i, stack[k].j);
//		}
//		printf("\n");
//	}
//	if (check[i + 1][j] != 1 && i + 1 >= 0 && i + 1 <= 4 && j >= 0 && j <= 4) {
//		search(i + 1, j);
//	}
//	if (check[i][j + 1] != 1 && i >= 0 && i <= 4 && j + 1 >= 0 && j + 1 <= 4) {
//		search(i, j + 1);
//	}
//	if (check[i - 1][j] != 1 && i - 1 >= 0 && i - 1 <= 4 && j >= 0 && j <= 4) {
//		search(i - 1, j);
//	}
//	if (check[i][j - 1] != 1 && i >= 0 && i <= 4 && j - 1 >= 0 && j - 1 <= 4) {
//		search(i, j - 1);
//	}
//	check[i][j] = 0;
//	pop();
//	return;
//}
//
//int main() {
//	search(0, 1);
//	return 0;
//}
