/* 20200854 Ȳ����
��ǰ��� ���α׷��Դϴ�.
������ �����ϸ� ���� ���� ���ڸ� ������ ���ڿ�, ����� ������ ���ڿ�, ����� ǥ�õǰ� ���ڸ� �Է¹޽��ϴ�.
��������� ���ڿ����� ������ ���� ���ڴ� '_'�� ǥ�õǰ�, ���� ���ڴ� �ش� ���ڷ� ǥ�õ˴ϴ�.
�Է¹��� ���ڸ� �ܾ�(��)�� ���Ͽ� ��ġ�ϴ� ���ڰ� �ִٸ� �� �ڸ��� '_'���� �ش� ���ڷ� �����ϰ�, ���ٸ� ����� �ϳ� �پ��ϴ�.
�ߺ��� ���ڸ� �Է��� ��� ���� �޼����� ��µǸ� ����� �������� �ʽ��ϴ�.
10���� ��ȸ �ȿ� �ܾ ���߾�� �ϸ�, �׷��� ���ϸ� ���� �޼����� ��µ˴ϴ�.
�� ���尡 ������ ���� ���带 �������� ���θ� ����, �̸� y/n�� ���ڷ� �Է� �޽��ϴ�.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //�ʿ��� ������� �߰�
#define MAX 30 //�迭 �ִ� ũ�� ����

void rand_word(char* word); //�ܾ��忡�� �ܾ� �ϳ��� �������� �Լ�
int game_board(int* lifes,int* j, char* print_word, char* word, char* use); //���� ������ ����ϴ� �Լ�
int compare_answer(char* word, char* print_word, char ans); //�Է¹��� ���ڿ� �ܾ ���ϴ� �Լ�

int main(void)
{
	int lifes, i, length, j;
	int count;
	char conti;
	char word[MAX], print_word[MAX], use[MAX] = { "" }; //���� �� �迭 ����
	printf("Let's play the hangman game!\n"); //���� ���
	
	while (1) { //���� �ݺ���
		j = 0; //�Է¹��� ���ڸ� ���ڿ��� �ű�� ���� ���� �ʱ�ȭ
		count = 0; //���� ��ġ ���� �ʱ�ȭ
		lifes = 10; //����� ����� 10���� �ʱ�ȭ
		length = 0; //�ܾ� ���� �ʱ�ȭ
		for (i = 0; i < MAX; i++){
			print_word[i] = ' '; //��¿� �迭 �ʱ�ȭ
			use[i] = ' '; //�Է¹��� ���ڸ� �����ϴ� �迭 �ʱ�ȭ
		}
		rand_word(word); //�ܾ��忡�� �ܾ� �ϳ� �ҷ�����
		
		while (word[length] != '\n')
			length++; //�ܾ��� ���� �ľ�
		for (i = 0; i < length; i++) {
			print_word[i] = '_';
		} //��µǴ� �ܾ� ����

		while (1) { //���� ���ο��� ��°� �Է� �ݺ�
			if (lifes == 0) {
				printf("\nWord: ");
				for (i = 0; i < length; i++) {
					printf("%c ", print_word[i]);
				} //������� ���� ��Ȳ ���

				printf("\nUsed: ");
				for (i = 0; i < MAX; i++) {
					printf("%c ", use[i]);
				} //�̶����� ����� ���� ���
				printf("\nHangman (%d life)\n", lifes);
				printf("\nMission Failed!\n");
				printf("The answer was %s\n", word);
				break;
			} //����� 0�� �� ��� ���� �޼����� �� ��� �� ���� ����
			else if (count == length) {
				printf("\nWord: ");
				for (i = 0; i < length; i++) {
					printf("%c ", print_word[i]);
				} //������� ���� ��Ȳ ���

				printf("\nUsed: ");
				for (i = 0; i < MAX; i++) {
					printf("%c ", use[i]);
				} //�̶����� ����� ���� ���
				printf("\nHangman (%d life)\n", lifes);
				printf("\nCongratulations!\n");
				printf("The answer was %s\n", word);
				break;
			} //count ���� length���� ���� ���(������ ���� ���) ���� �޼����� �� ��� �� ���� ����
			else {
				count=game_board(&lifes, &j, print_word, word, use);
				continue;
			} //�� ���� ��� ���� ��� ����
		}

		printf("Do you want to play again? (y/n) ");
		scanf("%c", &conti); //�ٽ� �÷����� �� ���� Ȯ��

		if (conti == 'y') {
			getchar();
			continue;
		}//y�� �Է� ������ ���� ���� ����
		else
			break; //n�� �Է� ������ ���� ����
	}
	printf("\nGood bye!\n");
	return 0;
}

void rand_word(char* word) 
{
	srand(time(NULL));
	int word_select, word_num;
	int count = 0; //���� ����
	FILE* dic = fopen("dic.txt", "r"); //�ܾ��� ���� ����
	if (!dic) {
		printf("Error opening dictionary.\n");
		exit(101);
	} //�ܾ��� ������ ���� �� ���� �޼��� ���
	else {
		fscanf(dic, "%d", &word_num); //���Ͽ��� �ܾ� �ҷ�����
		word_select = rand() % word_num + 2; //�ܾ��忡�� �� ��° �ܾ �ҷ����� �������� ����
		while (fgets(word, MAX, dic) != NULL) {
			count++;
			if (count == word_select)
				break;
		} //�ش� �ܾ �ҷ����� �ܾ� �ҷ����� ����
	}
	fclose(dic); //���� �ݱ�
	return;
}

int game_board(int* lifes, int* j, char* print_word, char* word, char* use)
{
	int length = 0, a, i, count=0;
	char ans; //���� ����
	while (word[length] != '\n')
		length++; //�ܾ� ���� Ȯ��

	printf("\nWord: ");
	for (i = 0; i < length; i++) {
		printf("%c ", print_word[i]);
	} //������� ���� ��Ȳ ���

	printf("\nUsed: ");
	for (i = 0; i < MAX; i++) {
		printf("%c ", use[i]);
	} //�̶����� ����� ���� ���
	printf("\nHangman (%d life) - Input: ", *lifes); //����� ���� ��� ���

	scanf("%c", &ans); //���� �ϳ� �Է¹ޱ�
	a=compare_answer(word, print_word, ans); //���ڿ� �ܾ ��

	for (i = 0; i < MAX; i++) {
		if (use[i] == ans) {
			printf("%c: Already inserted character.\n", ans);
			getchar();
			return;
		}
	}//�ߺ��� ���� �Է� �� ���� �޼��� ���
	
	use[*j] = ans; //�Է� ���� ���ڸ� �ٸ� ���ڿ��� ����
	(*j)++;
	getchar(); //���� ����

	for (i = 0; i < length; i++) {
		if (word[i] == print_word[i]) {
			count++;
		}
	}//�ܾ�� �̶����� ���� ���ڿ��� ���ڰ� ���� ������ŭ count ����
	if (count == length)
		return count; //count�� length�� ������(�ܾ�� ��� ���ڿ��� ��ġ�ϸ�) count ��ȯ

	if (a == 0)
		(*lifes)--; //�ܾ�� �Է¹��� ���ڿ� ��ġ�ϴ� ���ڰ� ������ ��� 1�� ����
	return;
}

int compare_answer(char* word, char* print_word, char ans)
{
	int length = 0;
	int count = 0;
	int i; //���� ����
	while (word[length] != '\n')
		length++; //�ܾ� ���� Ȯ��
	for (i = 0; i < length; i++) {
		if (word[i] == ans) {
			print_word[i] = ans;
			count++; //���ڰ� ��ġ�ϴ��� Ȯ���ϴ� �뵵
		}
	} //�Է¹��� ���ڿ� �ܾ��� ���ڰ� ������ ��� ���ڿ����� �ش� ���ڷ� �ٲپ ���

	if (count == 0)
		return 0; //��ġ�ϴ� ���ڰ� ������ 0 ��ȯ
	else
		return 1; //��ġ�ϴ� ���ڰ� ������ 1 ��ȯ
}
