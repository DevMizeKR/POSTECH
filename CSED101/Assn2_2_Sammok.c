/* 20200854 Ȳ����
��� ���� ���α׷��Դϴ�.
������ �����ϰ� �Ǹ� 3x3 ũ���� �� ��� ���� ����ϰ�, ��ǻ�Ϳ� ����� ���̿��� ���� �İ��� �������� ���մϴ�.
��������� ��� �� ��Ȳ�� ǥ���ϰ�, ��ǻ���� ���ʿ��� ���� �ڸ���, ������� ���ʿ��� ��ǥ�� �Է¹޾� ���� �����ϴ�.
��������� ��Ȳ���� �� ĭ�� '*'�� ǥ�õǰ�, ä���� ĭ�� �ش� �÷��̾��� ǥ�� ���ڷ� ��Ÿ���ϴ�.
�ߺ��� �ڸ��� �Է��� ��� ���� �޼����� ��µǸ� �ٽ� �ѹ� �Է��ϰ� �˴ϴ�.
����, ����, �밢������ ���� �� ���� �ϼ��ϴ� �÷��̾ �¸��ϸ�, 9ĭ�� ��� ä���� ���а� �������� ������ ���ºΰ� �˴ϴ�.
�� ���尡 ������ ���� ���带 �������� ���θ� ����, �̸� y/n�� ���ڷ� �Է� �޽��ϴ�.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //�ʿ��� ������� �߰�
#define MAX 3 //�迭 �ִ� ũ�� ����

void print_board(char board[MAX][MAX]); //��� ���� ����ϴ� �Լ�
int computer_or_user(); //��ǻ�Ϳ� ����� �� ���� �����ϴ� ���� ���ϴ� �Լ�
void computer_put(char board[MAX][MAX], char mark); //��ǻ�Ͱ� ���� ���� ���ϴ� �Լ�
void user_put(char board[MAX][MAX], char mark); //������� ���� �Է¹޾� ���� �Լ�
int check_board(char board[MAX][MAX], char mark_use, char mark_com); //���� ������ Ȯ���ϴ� �Լ�
void print_result(int win_lose); //����� ����ϴ� �Լ�

int main(void)
{
	int i, j, order, win_lose;
	char mark_com, mark_use, conti;
	char board[MAX][MAX]; //���� ����
	srand(time(NULL)); //���� �õ� ����

	while (1) { //���� �ݺ�
		for (i = 0; i < MAX; i++) {
			for (j = 0; j < MAX; j++) {
				board[i][j] = '*';
			}
		} //��� �迭 �ʱ�ȭ
	    print_board(board); //�� ��� �� ���
		order = computer_or_user(); //���� �������� ���ϱ�
		if (order == 1) { //��ǻ�Ͱ� ������ ���
			mark_use = 'X'; //������� �� ǥ�� ���� ����
			mark_com = 'O'; //��ǻ���� �� ǥ�� ���� ����
			while (1) { //�õ� �ݺ�
				computer_put(board, mark_com); //��ǻ���� ���� �޾� ǥ��
				win_lose = check_board(board, mark_use, mark_com); //���� ���� Ȯ��
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //���� ���ǿ� �ش��ϴ� ��찡 ������ �޼��� ��� �� ���� ����

				user_put(board, mark_use); //������� ���� �޾� ǥ��
				win_lose = check_board(board, mark_use, mark_com); //���� ���� Ȯ��
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //���� ���ǿ� �ش��ϴ� ��찡 ������ �޼��� ��� �� ���� ����
				continue; //�ش��� ���� ��� �ݺ��� ó������ ���ư�
			}
		}
		else { //����ڰ� ������ ���
			mark_use = 'O'; //������� �� ǥ�� ���� ����
			mark_com = 'X'; //��ǻ���� �� ǥ�� ���� ����
			while (1) { //�õ� �ݺ�
				user_put(board, mark_use); //������� ���� �޾� ǥ��
				win_lose = check_board(board, mark_use, mark_com); //���� ���� Ȯ��
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //���� ���ǿ� �ش��ϴ� ��찡 ������ �޼��� ��� �� ���� ����

				computer_put(board, mark_com); //��ǻ���� ���� �޾� ǥ��
				win_lose = check_board(board, mark_use, mark_com); //���� ���� Ȯ��
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //���� ���ǿ� �ش��ϴ� ��찡 ������ �޼��� ��� �� ���� ����
				continue; //�ش��� ���� ��� �ݺ��� ó������ ���ư�
			}
		}
		printf("Do you want to play again? (y/n) ");
		scanf("%c", &conti); //���� �̴��� ������ �� ������ ������ �� ���� �Է�

		if (conti == 'y') {
			printf("\n");
			getchar();
			continue;
		} //y�� �Է¹��� ��� ���� ���� ����
		else {
			getchar();
			break;
		} //n�� �Է¹��� ��� ���� ����
	}
	printf("Good bye!\n");
	return 0;
}

void print_board(char board[MAX][MAX])
{
	int i; //���� ����
	for (i = 0; i < MAX; i++) {
		printf("+---+---+---+\n");
		printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
	} //��� �� ���
	printf("+---+---+---+\n"); //���� ���� �Ʒ��κ� ���
	return;
}

int computer_or_user()
{
	int order;
	order = rand() % 2; //order ���� 0�� 1 �� �ϳ��� �������� ������ ������ ����.
	return order;
}

void computer_put(char board[MAX][MAX], char mark)
{
	int rand_place_x, rand_place_y; //���� ����

	while (1) {
		rand_place_x = rand() % 3;
		rand_place_y = rand() % 3; //��ǻ�Ͱ� ���� ���� �ڸ� �������� ����

		if (board[rand_place_x][rand_place_y] != '*') {
			continue;
		} //�̹� ���� �����ִ� ��� ó������ ���ư� �ٽ� �ڸ��� ����
		else {
			printf("\n[Computer] %d %d\n", rand_place_x, rand_place_y); //��ǻ�Ͱ� ������ �ڸ� ǥ��
			board[rand_place_x][rand_place_y] = mark; //��ǻ���� ���� ǥ���ϴ� ���ڷ� �ش� �ڸ��� ǥ��
			print_board(board); //��� �� ���
			break;
		} 
	}
	return;
}

void user_put(char board[MAX][MAX], char mark)
{
	int place_x, place_y; //���� ����

	while (1) {
		printf("\n[User] ");
		scanf("%d %d", &place_x, &place_y); //����ڰ� ���� ���� �ڸ��� �Է¹���.

		if (board[place_x][place_y] != '*' || place_x >= 3 || place_y >= 3) {
			getchar();
			printf("You can't put here.\n");
			continue;
		} //�ش� �ڸ��� �̹� ���� �ִ� ��� ���� �޼��� ��� �� �ٽ� �Է¹���.
		else {
			board[place_x][place_y] = mark; //������� ���� ǥ���ϴ� ���ڷ� �ش� �ڸ��� ǥ��
			print_board(board); //����� ���
			getchar(); //���� ����
			break;
		}
	}
	return;
}

int check_board(char board[MAX][MAX], char mark_use, char mark_com)
{
	int i, j, count = 0; //���� ����
	int mark_count_use1 = 0, mark_count_use2 = 0; //������� �¸� ������ Ȯ���ϱ� ���� ����
	int mark_count_com1 = 0, mark_count_com2 = 0; //��ǻ���� �¸� ������ Ȯ���ϱ� ���� ����
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (board[i][j] != '*')
				count++;
		}
	} //�ڸ��� ������� ���� ��� count ����
	for (i = 0; i < MAX; i++) {
		if (board[i][0] == mark_use && board[i][1] == mark_use && board[i][2] == mark_use)
			return 1; //����ڰ� ���η� �� ���� �ϼ��� ��� 1 ��ȯ
		else if (board[0][i] == mark_use && board[1][i] == mark_use && board[2][i] == mark_use)
			return 1; //����ڰ� ���η� �� ���� �ϼ��� ��� 1 ��ȯ
		for (j = 0; j < MAX; j++) {
			if (i == j && board[i][j] == mark_use)
				mark_count_use1++; //������ �Ʒ� ���� �밢���� �ϼ� ���� ī��Ʈ
			if (i + j == 2 && board[i][j] == mark_use)
				mark_count_use2++; //���� �Ʒ� ���� �밢���� �ϼ� ���� ī��Ʈ
		}
	}
	for (i = 0; i < MAX; i++) {
		if (board[i][0] == mark_com && board[i][1] == mark_com && board[i][2] == mark_com)
			return 2; //��ǻ�Ͱ� ���η� �� ���� �ϼ��� ��� 2 ��ȯ
		else if (board[0][i] == mark_com && board[1][i] == mark_com && board[2][i] == mark_com)
			return 2; //��ǻ�Ͱ� ���η� �� ���� �ϼ��� ��� 2 ��ȯ
		for (j = 0; j < MAX; j++) {
			if (i == j && board[i][j] == mark_com)
				mark_count_com1++; //������ �Ʒ� ���� �밢���� �ϼ� ���� ī��Ʈ
			if (i + j == 2 && board[i][j] == mark_com)
				mark_count_com2++; //���� �Ʒ� ���� �밢���� �ϼ� ���� ī��Ʈ
		}
	}

	if (mark_count_use1 == 3 || mark_count_use2 == 3)
		return 1; //������� ī��Ʈ�� 3�� �Ǹ� 1 ��ȯ
	else if (mark_count_com1 == 3 || mark_count_com2 == 3)
		return 2; //��ǻ���� ī��Ʈ�� 3�� �Ǹ� 2 ��ȯ
	else if (count == 9)
		return 0; //count ���� 9�� ���(��� �ڸ��� �� ���) 0 ��ȯ
	else
		return 3; //�̿��� ��� 3 ��ȯ
}

void print_result(int win_lose)
{
	if (win_lose == 0) {
		printf("\nDraw!\n");
		return;
	} //win_lose���� 0�� ��� ���º� �޼��� ���
	else if (win_lose == 1) {
		printf("\nYou Win!\n");
		return;
	} //win_lose���� 1�� ��� �¸� �޼��� ���
	else if (win_lose == 2) {
		printf("\nYou Lose!\n");
		return;
	} //win_lose���� 2�� ��� �й� �޼��� ���
	else
		return; //�̿��� ��� �ƹ� ���� ���� �Լ� ����
}