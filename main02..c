#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#pragma warning (disable : 4996)
#define size 9
#define landmine 10

int board[size][size] = { 0 };
int showboard[size][size] = { 0 };

void gotoxy(int x, int y);
void board_remove(int xx, int yy);
void location();//좌표 표시
void gameover();
void flag(int x, int y);
void menu1();//게임시작
void show_reset() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			showboard[i][j] = 0;
		}
	}
}
int main() {
	system("cls");
	int cho_menu;
	while (1) {
		gotoxy(40, 20);
		printf("---지뢰 찾기 게임---");
		gotoxy(40, 22);
		printf("1. 게임시작");
		gotoxy(40, 23);
		printf("2. 게임방법");
		gotoxy(40, 24);
		printf("3. 게임종료");
		gotoxy(40, 26);
		printf(">> ");
		scanf("%d", &cho_menu);
		switch (cho_menu) {
		case 1: menu1(); break;
		case 3: break;
		}
	}
}
void menu1() {//게임시작
	show_reset();
	system("cls");
	//지뢰 배정
	srand((unsigned)time(NULL));
	int mine_x, mine_y;
	for (int i = 0; i < landmine; i++) {
		mine_x = rand() % size;
		mine_y = rand() % size;
		board[mine_x][mine_y] = 8;
	}

	//숫자 넣기
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int count = 0;
			if (board[i][j] != 8) {
				if (i - 1 != -1 && j - 1 != -1) { if (board[i - 1][j - 1] == 8) count++; }
				if (j - 1 != -1) { if (board[i][j - 1] == 8) count++; }
				if (i + 1 != size) { if (board[i + 1][j - 1] == 8) count++; }
				if (i - 1 != -1) { if (board[i - 1][j] == 8) count++; }
				if (i + 1 != size) { if (board[i + 1][j] == 8) count++; }
				if (i - 1 != -1 && j + 1 != size) { if (board[i - 1][j + 1] == 8) count++; }
				if (j + 1 != size) { if (board[i][j + 1] == 8) count++; }
				if (i + 1 != size && j + 1 != size) { if (board[i + 1][j + 1] == 8) count++; }
				board[i][j] = count;
			}
		}
	}
	//속 보드 테스트
	gotoxy(3, 2);
	int b = 3;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", board[i][j]);
		}
		gotoxy(3, b);
		b++;
	}
	getch();
	system("cls");
	//겉,속 보드 출력
	while (1) {
		location();
		gotoxy(3, 2);
		int b = 3;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (showboard[i][j] == 0) {
					printf("□");
				}
				else if (showboard[i][j] == 1) {
					printf("%d ", board[i][j]);
				}
				else {
					printf("@ ");
				}
			}
			gotoxy(3, b);
			b++;
		}
		//질문
		int cho_x = 0, cho_y = 0;
		int cho_menu = 0;
		printf("좌표 입력 (x y) : ");
		scanf("%d %d", &cho_x, &cho_y);
		printf("1. 확인 2.깃발 세우기 : ");
		scanf("%d", &cho_menu);

		switch (cho_menu) {
		case 1: board_remove(cho_y - 1, cho_x - 1); break;
		case 2: flag(cho_y - 1, cho_x - 1); break;
		}
		system("cls");
	}

}
void board_remove(int x, int y) {//겉 보드 지울 값 넣기

	if (showboard[x][y] == 0) {
		if (board[x][y] == 0) {
			showboard[x][y] = 1;
			if (x - 1 != -1 && y - 1 != -1)board_remove(x - 1, y - 1);
			if (y - 1 != -1)board_remove(x, y - 1);
			if (x + 1 != size)board_remove(x + 1, y - 1);
			if (x - 1 != -1)board_remove(x - 1, y);
			if (x + 1 != size)board_remove(x + 1, y);
			if (x - 1 != -1 && y + 1 != size)board_remove(x - 1, y + 1);
			if (y + 1 != size)board_remove(x, y + 1);
			if (x + 1 != size && y + 1 != size)board_remove(x + 1, y + 1);
		}
		else if (board[x][y] != 8 && board[x][y]>0) {
			showboard[x][y] = 1;
		}
		else if (board[x][y] == 8) {
			gameover();
			main();
		}
	}
}
void flag(int x, int y) {//깃발
	gotoxy(x + 4, y + 3);
	showboard[x][y] = 3;
}
void gameover() {//지뢰 밟았을 때
	gotoxy(50, 20);
	printf("지뢰를 밟았습니다 : GAME OVER");
	getch();
}
void location() {//좌표표시
	for (int i = 0; i <= size; i++) {
		printf("%d ", i);
	}
	int a = 2;
	for (int i = 1; i <= size; i++) {
		gotoxy(1, a);
		printf("%d ", i);
		a++;
	}

}

void gotoxy(int x, int y) {//좌표이동
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}