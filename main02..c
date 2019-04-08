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
void location();//��ǥ ǥ��
void gameover();
void flag(int x, int y);
void menu1();//���ӽ���
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
		printf("---���� ã�� ����---");
		gotoxy(40, 22);
		printf("1. ���ӽ���");
		gotoxy(40, 23);
		printf("2. ���ӹ��");
		gotoxy(40, 24);
		printf("3. ��������");
		gotoxy(40, 26);
		printf(">> ");
		scanf("%d", &cho_menu);
		switch (cho_menu) {
		case 1: menu1(); break;
		case 3: break;
		}
	}
}
void menu1() {//���ӽ���
	show_reset();
	system("cls");
	//���� ����
	srand((unsigned)time(NULL));
	int mine_x, mine_y;
	for (int i = 0; i < landmine; i++) {
		mine_x = rand() % size;
		mine_y = rand() % size;
		board[mine_x][mine_y] = 8;
	}

	//���� �ֱ�
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
	//�� ���� �׽�Ʈ
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
	//��,�� ���� ���
	while (1) {
		location();
		gotoxy(3, 2);
		int b = 3;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (showboard[i][j] == 0) {
					printf("��");
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
		//����
		int cho_x = 0, cho_y = 0;
		int cho_menu = 0;
		printf("��ǥ �Է� (x y) : ");
		scanf("%d %d", &cho_x, &cho_y);
		printf("1. Ȯ�� 2.��� ����� : ");
		scanf("%d", &cho_menu);

		switch (cho_menu) {
		case 1: board_remove(cho_y - 1, cho_x - 1); break;
		case 2: flag(cho_y - 1, cho_x - 1); break;
		}
		system("cls");
	}

}
void board_remove(int x, int y) {//�� ���� ���� �� �ֱ�

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
void flag(int x, int y) {//���
	gotoxy(x + 4, y + 3);
	showboard[x][y] = 3;
}
void gameover() {//���� ����� ��
	gotoxy(50, 20);
	printf("���ڸ� ��ҽ��ϴ� : GAME OVER");
	getch();
}
void location() {//��ǥǥ��
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

void gotoxy(int x, int y) {//��ǥ�̵�
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}