/* 20200854 황찬기
삼목 게임 프로그램입니다.
게임을 진행하게 되면 3x3 크기의 빈 삼목 판을 출력하고, 컴퓨터와 사용자 사이에서 선공 후공을 랜덤으로 정합니다.
현재까지의 삼목 판 상황을 표시하고, 컴퓨터의 차례에는 랜덤 자리에, 사용자의 차례에는 좌표를 입력받아 수를 놓습니다.
현재까지의 상황에서 빈 칸은 '*'로 표시되고, 채워진 칸은 해당 플레이어의 표시 문자로 나타납니다.
중복된 자리를 입력할 경우 오류 메세지가 출력되며 다시 한번 입력하게 됩니다.
가로, 세로, 대각선으로 먼저 한 줄을 완성하는 플레이어가 승리하며, 9칸을 모두 채워도 승패가 결정되지 않으면 무승부가 됩니다.
한 라운드가 끝나면 다음 라운드를 진행할지 여부를 묻고, 이를 y/n의 문자로 입력 받습니다.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //필요한 헤더파일 추가
#define MAX 3 //배열 최대 크기 정의

void print_board(char board[MAX][MAX]); //삼목 판을 출력하는 함수
int computer_or_user(); //컴퓨터와 사용자 중 먼저 시작하는 쪽을 정하는 함수
void computer_put(char board[MAX][MAX], char mark); //컴퓨터가 놓는 수를 정하는 함수
void user_put(char board[MAX][MAX], char mark); //사용자의 수를 입력받아 놓는 함수
int check_board(char board[MAX][MAX], char mark_use, char mark_com); //승패 조건을 확인하는 함수
void print_result(int win_lose); //결과를 출력하는 함수

int main(void)
{
	int i, j, order, win_lose;
	char mark_com, mark_use, conti;
	char board[MAX][MAX]; //변수 선언
	srand(time(NULL)); //랜덤 시드 설정

	while (1) { //라운드 반복
		for (i = 0; i < MAX; i++) {
			for (j = 0; j < MAX; j++) {
				board[i][j] = '*';
			}
		} //삼목 배열 초기화
	    print_board(board); //빈 삼목 판 출력
		order = computer_or_user(); //순서 랜덤으로 정하기
		if (order == 1) { //컴퓨터가 선공인 경우
			mark_use = 'X'; //사용자의 수 표시 문자 설정
			mark_com = 'O'; //컴퓨터의 수 표시 문자 설정
			while (1) { //시도 반복
				computer_put(board, mark_com); //컴퓨터의 수를 받아 표시
				win_lose = check_board(board, mark_use, mark_com); //승패 조건 확인
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //승패 조건에 해당하는 경우가 있으면 메세지 출력 후 라운드 종료

				user_put(board, mark_use); //사용자의 수를 받아 표시
				win_lose = check_board(board, mark_use, mark_com); //승패 조건 확인
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //승패 조건에 해당하는 경우가 있으면 메세지 출력 후 라운드 종료
				continue; //해당이 없는 경우 반복문 처음으로 돌아감
			}
		}
		else { //사용자가 선공인 경우
			mark_use = 'O'; //사용자의 수 표시 문자 설정
			mark_com = 'X'; //컴퓨터의 수 표시 문자 설정
			while (1) { //시도 반복
				user_put(board, mark_use); //사용자의 수를 받아 표시
				win_lose = check_board(board, mark_use, mark_com); //승패 조건 확인
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //승패 조건에 해당하는 경우가 있으면 메세지 출력 후 라운드 종료

				computer_put(board, mark_com); //컴퓨터의 수를 받아 표시
				win_lose = check_board(board, mark_use, mark_com); //승패 조건 확인
				if (win_lose != 3) {
					print_result(win_lose);
					break;
				} //승패 조건에 해당하는 경우가 있으면 메세지 출력 후 라운드 종료
				continue; //해당이 없는 경우 반복문 처음으로 돌아감
			}
		}
		printf("Do you want to play again? (y/n) ");
		scanf("%c", &conti); //다음 이닝을 진행할 지 게임을 종료할 지 문자 입력

		if (conti == 'y') {
			printf("\n");
			getchar();
			continue;
		} //y를 입력받은 경우 다음 라운드 진행
		else {
			getchar();
			break;
		} //n을 입력받은 경우 게임 종료
	}
	printf("Good bye!\n");
	return 0;
}

void print_board(char board[MAX][MAX])
{
	int i; //변수 선언
	for (i = 0; i < MAX; i++) {
		printf("+---+---+---+\n");
		printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
	} //삼목 판 출력
	printf("+---+---+---+\n"); //판의 가장 아랫부분 출력
	return;
}

int computer_or_user()
{
	int order;
	order = rand() % 2; //order 값을 0과 1 중 하나를 랜덤으로 결정해 순서를 정함.
	return order;
}

void computer_put(char board[MAX][MAX], char mark)
{
	int rand_place_x, rand_place_y; //변수 선언

	while (1) {
		rand_place_x = rand() % 3;
		rand_place_y = rand() % 3; //컴퓨터가 수를 놓을 자리 랜덤으로 설정

		if (board[rand_place_x][rand_place_y] != '*') {
			continue;
		} //이미 수가 놓여있는 경우 처음으로 돌아가 다시 자리를 받음
		else {
			printf("\n[Computer] %d %d\n", rand_place_x, rand_place_y); //컴퓨터가 결정한 자리 표시
			board[rand_place_x][rand_place_y] = mark; //컴퓨터의 수를 표시하는 문자로 해당 자리에 표시
			print_board(board); //삼목 판 출력
			break;
		} 
	}
	return;
}

void user_put(char board[MAX][MAX], char mark)
{
	int place_x, place_y; //변수 선언

	while (1) {
		printf("\n[User] ");
		scanf("%d %d", &place_x, &place_y); //사용자가 수를 놓을 자리를 입력받음.

		if (board[place_x][place_y] != '*' || place_x >= 3 || place_y >= 3) {
			getchar();
			printf("You can't put here.\n");
			continue;
		} //해당 자리에 이미 수가 있는 경우 오류 메세지 출력 후 다시 입력받음.
		else {
			board[place_x][place_y] = mark; //사용자의 수를 표시하는 문자로 해당 자리에 표시
			print_board(board); //삼목판 출력
			getchar(); //버퍼 비우기
			break;
		}
	}
	return;
}

int check_board(char board[MAX][MAX], char mark_use, char mark_com)
{
	int i, j, count = 0; //변수 선언
	int mark_count_use1 = 0, mark_count_use2 = 0; //사용자의 승리 조건을 확인하기 위한 변수
	int mark_count_com1 = 0, mark_count_com2 = 0; //컴퓨터의 승리 조건을 확인하기 위한 변수
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (board[i][j] != '*')
				count++;
		}
	} //자리가 비어있지 않은 경우 count 증가
	for (i = 0; i < MAX; i++) {
		if (board[i][0] == mark_use && board[i][1] == mark_use && board[i][2] == mark_use)
			return 1; //사용자가 가로로 한 줄을 완성한 경우 1 반환
		else if (board[0][i] == mark_use && board[1][i] == mark_use && board[2][i] == mark_use)
			return 1; //사용자가 세로로 한 줄을 완성한 경우 1 반환
		for (j = 0; j < MAX; j++) {
			if (i == j && board[i][j] == mark_use)
				mark_count_use1++; //오른쪽 아래 방향 대각선의 완성 정도 카운트
			if (i + j == 2 && board[i][j] == mark_use)
				mark_count_use2++; //왼쪽 아래 방향 대각선의 완성 정도 카운트
		}
	}
	for (i = 0; i < MAX; i++) {
		if (board[i][0] == mark_com && board[i][1] == mark_com && board[i][2] == mark_com)
			return 2; //컴퓨터가 가로로 한 줄을 완성한 경우 2 반환
		else if (board[0][i] == mark_com && board[1][i] == mark_com && board[2][i] == mark_com)
			return 2; //컴퓨터가 세로로 한 줄을 완성한 경우 2 반환
		for (j = 0; j < MAX; j++) {
			if (i == j && board[i][j] == mark_com)
				mark_count_com1++; //오른쪽 아래 방향 대각선의 완성 정도 카운트
			if (i + j == 2 && board[i][j] == mark_com)
				mark_count_com2++; //왼쪽 아래 방향 대각선의 완성 정도 카운트
		}
	}

	if (mark_count_use1 == 3 || mark_count_use2 == 3)
		return 1; //사용자의 카운트가 3이 되면 1 반환
	else if (mark_count_com1 == 3 || mark_count_com2 == 3)
		return 2; //컴퓨터의 카운트가 3이 되면 2 반환
	else if (count == 9)
		return 0; //count 값이 9인 경우(모든 자리가 찬 경우) 0 반환
	else
		return 3; //이외의 경우 3 반환
}

void print_result(int win_lose)
{
	if (win_lose == 0) {
		printf("\nDraw!\n");
		return;
	} //win_lose값이 0인 경우 무승부 메세지 출력
	else if (win_lose == 1) {
		printf("\nYou Win!\n");
		return;
	} //win_lose값이 1인 경우 승리 메세지 출력
	else if (win_lose == 2) {
		printf("\nYou Lose!\n");
		return;
	} //win_lose값이 2인 경우 패배 메세지 출력
	else
		return; //이외의 경우 아무 시행 없이 함수 종료
}