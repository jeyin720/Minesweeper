//
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#pragma warning (disable : 4996)
#define size 9
#define landmine 10

int board[size][size] = { 0 };
int showboard[size][size] = { 0 };
int mine_count = landmine;
int game = 0;

void gotoxy(int x, int y);
void board_remove(int xx, int yy);
void location();//��ǥ ǥ��
void gameover();
void flag(int x, int y);
void success();
void menu1();//���ӽ���
void menu2();//���Ӽ���
void show_reset() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			showboard[i][j] = 0;
		}
	}
	mine_count = landmine;
}
int main() {
	int cho_menu;
	while (1) {
		system("cls");
		game = 0;
		gotoxy(25, 10);
		printf("---���� ã�� ����---");
		gotoxy(25, 11);
		printf("1. ���ӽ���");
		gotoxy(25, 12);
		printf("2. ���ӹ��");
		gotoxy(25, 13);
		printf("3. ��������");
		gotoxy(25, 15);
		printf(">> ");
		scanf("%d", &cho_menu);
		switch (cho_menu) {
		case 1: menu1(); break;
		case 2: menu2(); break;
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
				if (i + 1 != size && j - 1 != -1) { if (board[i + 1][j - 1] == 8) count++; }
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
		gotoxy(35, 2);
		printf("���� ������ �� : %d", mine_count);
		//����
		success();
		if (game == 1) {
			system("cls");
			break;
		}

		int cho_x = 0, cho_y = 0;
		int cho_menu = 0;
		gotoxy(3, b);
		printf("��ǥ �Է� (x y) : ");
		scanf("%d %d", &cho_x, &cho_y);
		printf("1. �� �ı� 2.��� ����� : ");
		scanf("%d", &cho_menu);

		switch (cho_menu) {
		case 1: board_remove(cho_y - 1, cho_x - 1); break;
		case 2: flag(cho_y - 1, cho_x - 1); break;
		}

		system("cls");
		if (game == 1) {
			break;
		}
	}

}
void menu2() {
	gotoxy(30, 10);
	system("cls");
	printf("1. ��ǥ�� �Է��ϼ���. ex)3 4(ENTER)");
	getch();

}
void board_remove(int x, int y) {//�� ���� ���� �� �ֱ�
	if (showboard[x][y] == 0) {
		if (board[x][y] == 0) {
			showboard[x][y] = 1;
			if (x - 1 != -1 && y - 1 != -1)board_remove(x - 1, y - 1);
			if (y - 1 != -1)board_remove(x, y - 1);
			if (x + 1 != size && y - 1 != -1)board_remove(x + 1, y - 1);
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
		}
	}
}
void flag(int x, int y) {//���
	if (showboard[x][y] == 3) {
		showboard[x][y] = 0;
		mine_count++;
	}
	else {
		showboard[x][y] = 3;
		mine_count--;
	}
}
void gameover() {//���� ����� ��
	gotoxy(35, 10);
	game = 1;
	gotoxy(3, 2);
	int b = 3;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == 8) {
				printf("%d ", board[i][j]);
			}
		}
		gotoxy(3, b);
		b++;
	}
	printf("���ڸ� ��ҽ��ϴ� : GAME OVER");
	getch();
}
void success() {
	if (mine_count == 0) {
		gotoxy(35, 10);
		printf("���ڸ� ��� ã�Ƴ½��ϴ� : GAME CLEAR!");

		gotoxy(3, 2);
		int b = 3;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("%d ", board[i][j]);
			}
			gotoxy(3, b);
			b++;
		}
		game = 1;
		getch();
	}
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