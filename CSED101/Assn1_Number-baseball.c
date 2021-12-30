/* 20200854 황찬기
숫자야구 게임 프로그램입니다.
중복 숫자 입력 시 기회가 1회 차감됩니다.
매 이닝이 끝날 때 마다 새로운 이닝을 시작할지 게임을 종료할 지 선택할 수 있으며, 게임 종료 시 이때까지 했던 이닝들의 평균 점수가 표시됩니다.
한 이닝 당 총 기회는 10번이며, 점수는 100점 만점에서 기회가 1회씩 줄어들수록 10점씩 줄어듭니다.
10번의 기회 안에 숫자를 맞추어야 하며, 그러지 못하거나 3번의 아웃(숫자가 모두 틀림)을 당할 시 점수는 0점이 됩니다.
-1을 입력하여 이닝을 즉시 종료할 수 있습니다. 이때의 점수는 0점으로 표기됩니다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //코드에 필요한 헤더 파일 불러오기

void get_rand_num(int* answer); //매 게임마다 랜덤한 숫자(답)를 생성하는 함수
void get_hidden_num(int* hid_num); //매 게임마다 각 자리의 숫자가 모두 같은 숨겨진 숫자 생성
int is_valid_num(int number); //생성된 숫자나 사용자가 입력한 숫자가 유효한지(중복이 없는지) 판단하는 함수
void draw_line(); //31개의 #(구분선 용도)을 출력하는 함수
void print_tries_status(int tries); //매 기회마다 남은 기회를 □와 ■를 이용하여 표시하는 함수
void compare(int answer, int input, int* strike, int* ball, int* out); //답과 사용자가 입력한 숫자를 비교하여 스트라이크, 볼, 아웃의 여부를 판단하는 함수
void print_comparison_results(int strike, int ball, int out); //스트라이크와 볼의 개수, 아웃 횟수를 출력하는 함수

int main(void)
{
	int answer, input, tries, inning, strike, ball, out, score, sum, hid_num;
	char rnd_continue;
	inning = 0;
	sum = 0; //코드에 필요한 변수들 정의

	draw_line();
	printf("         Baseball Game         \n");
	draw_line();
	printf("\n"); //게임 제목 표시

	while (1) //이닝 반복을 위한 구조
	{
		++inning; //반복할 때마다 이닝을 1씩 증가
		get_rand_num(&answer); //랜덤한 수(답)를 생성
		get_hidden_num(&hid_num); //숨겨진 숫자 생성

		tries = 0; 
		score = 0;
		out = 0; //기회와 점수, 아웃 수 초기화
		printf("\n<<< Inning #%d >>>\n", inning); //이닝 표시 출력
		draw_line();
		while (1) //한 이닝에서 시도 반복을 위한 구조
		{
			tries++; //반복할 때마다 시도 횟수를 1씩 증가
			strike = 0;
			ball = 0; //스트라이크, 볼 초기화

			if (tries == 11) {
				score = 0;
				printf("\nThe answer is %d.\n", answer);
				printf("Your score is %d points.\n", score);
				break;
			} //시도 횟수가 11(10보다 큰 수)이 되면 점수 0점 처리 후 출력 및 이닝 종료

			print_tries_status(tries); //현재 시도 횟수와 남은 횟수 표시
			printf("Enter your guess(-1 to quit): ");
			scanf("%d", &input); //사용자가 수 입력
			if (input == -1) {
				printf("[0 Strike 0 Ball]\n\n");
				break;
			} //-1을 입력할 경우 해당 이닝 종료
			else if (input == hid_num && tries >= 6 && tries <=9) {
				printf("You found Hidden Number.\n");
				printf("The first number of answer is... %d.\n", answer / 100);
				printf("Good Luck.\n\n");
			} //절반 이상의 기회를 소모한 상태(마지막 기회에서는 제외)에서 숨겨진 숫자를 입력할 경우 답의 맨 앞 숫자 출력(힌트)
			else if (is_valid_num(input) == 0 || input / 100 == 0) {
				printf("[0 Strike 0 Ball] Wrong Input!!\n\n");
				continue;
			} //중복되는 숫자가 있거나 앞자리에 0이 오는 경우 오류 메세지 출력 및 다음 시도 진행
			else {
				compare(answer, input, &strike, &ball, &out);
				if (strike == 3) {
					score = 100 - 10 * (tries - 1); //점수 계산
					printf("\nRight!!\n");
					printf("Your score is %d points.\n", score);
					break;
				} //스트라이크가 3(모든 숫자를 맞힘)인 경우 점수 출력 및 이닝 종료
				else if (out != 0) {
					print_comparison_results(strike, ball, out);
					if (out == 3) {
						score = 0;
						printf("\nThe answer is %d.\n", answer);
						printf("Your score is %d points.\n", score);
						break;
					} //아웃이 3회인 경우 점수 출력 및 이닝 종료
					continue;
				} //아웃 횟수가 0이 아닐 경우 현재까지 아웃 횟수 출력
				else {
					print_comparison_results(strike, ball, out);
					continue;
				} //일반적인 경우 스트라이크와 볼의 갯수를 출력 후 다음 시도 진행
			} //정상적인 수가 입력되는 경우
		}
		sum += score; //매 이닝마다의 점수를 합산

		printf("Do you want to play again? (y/n) ");
		scanf(" %c", &rnd_continue); //다음 이닝을 진행할 지 게임을 종료할 지 문자 입력

		if (rnd_continue == 'Y' || rnd_continue == 'y')
			continue; //입력값이 Y나 y인 경우 다음 이닝 진행
		else
			break; //입력값이 N이나 n인 경우 게임 종료
	}

	printf("\n\nYour average score is %.1f points.\n", (float)sum / inning); //전체 게임의 평균점수를 소수점 첫째자리까지 출력
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
		rnd3 = rand() % 10; //랜덤한 숫자 생성
		*answer = rnd1 * 100 + rnd2 * 10 + rnd3; //세 숫자를 합쳐 세자리 수로 만듦
	} while (is_valid_num(*answer) == 0); //is_valid_num이 0일 경우 다시 숫자 생성
	
	return;
}
void get_hidden_num(int* hid_num)
{
	int rnd;
	srand(time(NULL)+20);
	rnd = rand() % 9 + 1; //랜덤한 숫자 생성
	*hid_num = rnd * 111; //생성된 숫자에 111을 곱해 세자리 수로 만듦

	return;
}

int is_valid_num(int number)
{
	int num1, num2, num3;
	num1 = number / 100;
	num2 = (number - num1*100) / 10;
	num3 = number % 10; //세자리 수의 각 자리의 숫자를 따로 나타냄
	if (num1 == num2 || num2 == num3 || num3 == num1)
		return 0; //중복되는 수가 있을 경우 0을 반환
	else
		return 1; //이외의 경우 1을 반환
}

void draw_line()
{
	for (int i = 1; i < 32; i++){
		printf("#");
	} //#을 31개 출력
	printf("\n");
	return;
}

void print_tries_status(int tries)
{
	int left, cnt; //변수 선언
	left = 10 - tries; //남은 횟수를 현재 시도 횟수를 이용해 표시
	for (cnt=1 ; cnt < tries ; cnt++)
		printf("□"); //시도 횟수만큼 □ 출력
	for (cnt = 1; cnt <= left+1; cnt++)
		printf("■"); //남은 횟수만큼 ■ 출력
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
	inp_num3 = input % 10; //세자리 수의 각 자릿수를 따로 나타냄

	if (ans_num1 == inp_num1) *strike += 1;
	if (ans_num2 == inp_num2) *strike += 1;
	if (ans_num3 == inp_num3) *strike += 1; //각 자리의 숫자가 서로 같을 경우 strike 값 1 증가

	if (ans_num1 == inp_num2 || ans_num1 == inp_num3) *ball += 1;
	if (ans_num2 == inp_num1 || ans_num2 == inp_num3) *ball += 1;
	if (ans_num3 == inp_num1 || ans_num3 == inp_num2) *ball += 1; //전체 중 같은 숫자가 있다면 ball 값 1 증가

	if (ans_num1 != inp_num1 && ans_num1 != inp_num2 && ans_num1 != inp_num3 && ans_num2 != inp_num1 && ans_num2 != inp_num2 && ans_num2 != inp_num3 && ans_num3 != inp_num1 && ans_num3 != inp_num2 && ans_num3 != inp_num3) *out += 1; //숫자가 모두 불일치할 경우 out 횟수 1 증가

	return;
}

void print_comparison_results(int strike, int ball, int out)
{
	if (strike != 0 || ball != 0)
		printf("[%d Strike %d Ball]\n\n", strike, ball); //strike와 ball의 값이 0이 아닐 경우 스트라이크와 볼의 횟수를 출력
	else
		printf("[0 Strike 0 Ball] %d Out!!\n\n", out); //이외의 경우 아웃 횟수 출력
	return;
}