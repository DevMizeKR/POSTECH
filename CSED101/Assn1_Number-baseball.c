/* 20200854 Ȳ����
���ھ߱� ���� ���α׷��Դϴ�.
�ߺ� ���� �Է� �� ��ȸ�� 1ȸ �����˴ϴ�.
�� �̴��� ���� �� ���� ���ο� �̴��� �������� ������ ������ �� ������ �� ������, ���� ���� �� �̶����� �ߴ� �̴׵��� ��� ������ ǥ�õ˴ϴ�.
�� �̴� �� �� ��ȸ�� 10���̸�, ������ 100�� �������� ��ȸ�� 1ȸ�� �پ����� 10���� �پ��ϴ�.
10���� ��ȸ �ȿ� ���ڸ� ���߾�� �ϸ�, �׷��� ���ϰų� 3���� �ƿ�(���ڰ� ��� Ʋ��)�� ���� �� ������ 0���� �˴ϴ�.
-1�� �Է��Ͽ� �̴��� ��� ������ �� �ֽ��ϴ�. �̶��� ������ 0������ ǥ��˴ϴ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //�ڵ忡 �ʿ��� ��� ���� �ҷ�����

void get_rand_num(int* answer); //�� ���Ӹ��� ������ ����(��)�� �����ϴ� �Լ�
void get_hidden_num(int* hid_num); //�� ���Ӹ��� �� �ڸ��� ���ڰ� ��� ���� ������ ���� ����
int is_valid_num(int number); //������ ���ڳ� ����ڰ� �Է��� ���ڰ� ��ȿ����(�ߺ��� ������) �Ǵ��ϴ� �Լ�
void draw_line(); //31���� #(���м� �뵵)�� ����ϴ� �Լ�
void print_tries_status(int tries); //�� ��ȸ���� ���� ��ȸ�� ��� �Ḧ �̿��Ͽ� ǥ���ϴ� �Լ�
void compare(int answer, int input, int* strike, int* ball, int* out); //��� ����ڰ� �Է��� ���ڸ� ���Ͽ� ��Ʈ����ũ, ��, �ƿ��� ���θ� �Ǵ��ϴ� �Լ�
void print_comparison_results(int strike, int ball, int out); //��Ʈ����ũ�� ���� ����, �ƿ� Ƚ���� ����ϴ� �Լ�

int main(void)
{
	int answer, input, tries, inning, strike, ball, out, score, sum, hid_num;
	char rnd_continue;
	inning = 0;
	sum = 0; //�ڵ忡 �ʿ��� ������ ����

	draw_line();
	printf("         Baseball Game         \n");
	draw_line();
	printf("\n"); //���� ���� ǥ��

	while (1) //�̴� �ݺ��� ���� ����
	{
		++inning; //�ݺ��� ������ �̴��� 1�� ����
		get_rand_num(&answer); //������ ��(��)�� ����
		get_hidden_num(&hid_num); //������ ���� ����

		tries = 0; 
		score = 0;
		out = 0; //��ȸ�� ����, �ƿ� �� �ʱ�ȭ
		printf("\n<<< Inning #%d >>>\n", inning); //�̴� ǥ�� ���
		draw_line();
		while (1) //�� �̴׿��� �õ� �ݺ��� ���� ����
		{
			tries++; //�ݺ��� ������ �õ� Ƚ���� 1�� ����
			strike = 0;
			ball = 0; //��Ʈ����ũ, �� �ʱ�ȭ

			if (tries == 11) {
				score = 0;
				printf("\nThe answer is %d.\n", answer);
				printf("Your score is %d points.\n", score);
				break;
			} //�õ� Ƚ���� 11(10���� ū ��)�� �Ǹ� ���� 0�� ó�� �� ��� �� �̴� ����

			print_tries_status(tries); //���� �õ� Ƚ���� ���� Ƚ�� ǥ��
			printf("Enter your guess(-1 to quit): ");
			scanf("%d", &input); //����ڰ� �� �Է�
			if (input == -1) {
				printf("[0 Strike 0 Ball]\n\n");
				break;
			} //-1�� �Է��� ��� �ش� �̴� ����
			else if (input == hid_num && tries >= 6 && tries <=9) {
				printf("You found Hidden Number.\n");
				printf("The first number of answer is... %d.\n", answer / 100);
				printf("Good Luck.\n\n");
			} //���� �̻��� ��ȸ�� �Ҹ��� ����(������ ��ȸ������ ����)���� ������ ���ڸ� �Է��� ��� ���� �� �� ���� ���(��Ʈ)
			else if (is_valid_num(input) == 0 || input / 100 == 0) {
				printf("[0 Strike 0 Ball] Wrong Input!!\n\n");
				continue;
			} //�ߺ��Ǵ� ���ڰ� �ְų� ���ڸ��� 0�� ���� ��� ���� �޼��� ��� �� ���� �õ� ����
			else {
				compare(answer, input, &strike, &ball, &out);
				if (strike == 3) {
					score = 100 - 10 * (tries - 1); //���� ���
					printf("\nRight!!\n");
					printf("Your score is %d points.\n", score);
					break;
				} //��Ʈ����ũ�� 3(��� ���ڸ� ����)�� ��� ���� ��� �� �̴� ����
				else if (out != 0) {
					print_comparison_results(strike, ball, out);
					if (out == 3) {
						score = 0;
						printf("\nThe answer is %d.\n", answer);
						printf("Your score is %d points.\n", score);
						break;
					} //�ƿ��� 3ȸ�� ��� ���� ��� �� �̴� ����
					continue;
				} //�ƿ� Ƚ���� 0�� �ƴ� ��� ������� �ƿ� Ƚ�� ���
				else {
					print_comparison_results(strike, ball, out);
					continue;
				} //�Ϲ����� ��� ��Ʈ����ũ�� ���� ������ ��� �� ���� �õ� ����
			} //�������� ���� �ԷµǴ� ���
		}
		sum += score; //�� �̴׸����� ������ �ջ�

		printf("Do you want to play again? (y/n) ");
		scanf(" %c", &rnd_continue); //���� �̴��� ������ �� ������ ������ �� ���� �Է�

		if (rnd_continue == 'Y' || rnd_continue == 'y')
			continue; //�Է°��� Y�� y�� ��� ���� �̴� ����
		else
			break; //�Է°��� N�̳� n�� ��� ���� ����
	}

	printf("\n\nYour average score is %.1f points.\n", (float)sum / inning); //��ü ������ ��������� �Ҽ��� ù°�ڸ����� ���
	printf("Thanks for playing!\n");
	return 0;
}

void get_rand_num(int* answer)
{
	int rnd1, rnd2, rnd3;
	do {
		srand(time(NULL));
		rnd1 = rand() % 9 + 1; 
		rnd2 = rand() % 10;
		rnd3 = rand() % 10; //������ ���� ����
		*answer = rnd1 * 100 + rnd2 * 10 + rnd3; //�� ���ڸ� ���� ���ڸ� ���� ����
	} while (is_valid_num(*answer) == 0); //is_valid_num�� 0�� ��� �ٽ� ���� ����
	
	return;
}
void get_hidden_num(int* hid_num)
{
	int rnd;
	srand(time(NULL)+20);
	rnd = rand() % 9 + 1; //������ ���� ����
	*hid_num = rnd * 111; //������ ���ڿ� 111�� ���� ���ڸ� ���� ����

	return;
}

int is_valid_num(int number)
{
	int num1, num2, num3;
	num1 = number / 100;
	num2 = (number - num1*100) / 10;
	num3 = number % 10; //���ڸ� ���� �� �ڸ��� ���ڸ� ���� ��Ÿ��
	if (num1 == num2 || num2 == num3 || num3 == num1)
		return 0; //�ߺ��Ǵ� ���� ���� ��� 0�� ��ȯ
	else
		return 1; //�̿��� ��� 1�� ��ȯ
}

void draw_line()
{
	for (int i = 1; i < 32; i++){
		printf("#");
	} //#�� 31�� ���
	printf("\n");
	return;
}

void print_tries_status(int tries)
{
	int left, cnt; //���� ����
	left = 10 - tries; //���� Ƚ���� ���� �õ� Ƚ���� �̿��� ǥ��
	for (cnt=1 ; cnt < tries ; cnt++)
		printf("��"); //�õ� Ƚ����ŭ �� ���
	for (cnt = 1; cnt <= left+1; cnt++)
		printf("��"); //���� Ƚ����ŭ �� ���
	printf("\n");
	return;
}

void compare(int answer, int input, int* strike, int* ball, int* out)
{
	int ans_num1, ans_num2, ans_num3, inp_num1, inp_num2, inp_num3;
	ans_num1 = answer / 100;
	ans_num2 = (answer - ans_num1*100) / 10;
	ans_num3 = answer % 10;
	inp_num1 = input / 100;
	inp_num2 = (input - inp_num1*100) / 10;
	inp_num3 = input % 10; //���ڸ� ���� �� �ڸ����� ���� ��Ÿ��

	if (ans_num1 == inp_num1) *strike += 1;
	if (ans_num2 == inp_num2) *strike += 1;
	if (ans_num3 == inp_num3) *strike += 1; //�� �ڸ��� ���ڰ� ���� ���� ��� strike �� 1 ����

	if (ans_num1 == inp_num2 || ans_num1 == inp_num3) *ball += 1;
	if (ans_num2 == inp_num1 || ans_num2 == inp_num3) *ball += 1;
	if (ans_num3 == inp_num1 || ans_num3 == inp_num2) *ball += 1; //��ü �� ���� ���ڰ� �ִٸ� ball �� 1 ����

	if (ans_num1 != inp_num1 && ans_num1 != inp_num2 && ans_num1 != inp_num3 && ans_num2 != inp_num1 && ans_num2 != inp_num2 && ans_num2 != inp_num3 && ans_num3 != inp_num1 && ans_num3 != inp_num2 && ans_num3 != inp_num3) *out += 1; //���ڰ� ��� ����ġ�� ��� out Ƚ�� 1 ����

	return;
}

void print_comparison_results(int strike, int ball, int out)
{
	if (strike != 0 || ball != 0)
		printf("[%d Strike %d Ball]\n\n", strike, ball); //strike�� ball�� ���� 0�� �ƴ� ��� ��Ʈ����ũ�� ���� Ƚ���� ���
	else
		printf("[0 Strike 0 Ball] %d Out!!\n\n", out); //�̿��� ��� �ƿ� Ƚ�� ���
	return;
}