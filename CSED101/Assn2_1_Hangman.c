/* 20200854 황찬기
행맨게임 프로그램입니다.
게임을 시작하면 현재 맞힌 문자를 포함한 문자열, 사용한 문자의 문자열, 목숨이 표시되고 문자를 입력받습니다.
현재까지의 문자열에서 맞히지 못한 문자는 '_'로 표시되고, 맞힌 문자는 해당 문자로 표시됩니다.
입력받은 문자를 단어(답)과 비교하여 일치하는 문자가 있다면 그 자리를 '_'에서 해당 문자로 변경하고, 없다면 목숨이 하나 줄어듭니다.
중복된 문자를 입력할 경우 오류 메세지가 출력되며 목숨은 차감되지 않습니다.
10번의 기회 안에 단어를 맞추어야 하며, 그러지 못하면 실패 메세지가 출력됩니다.
한 라운드가 끝나면 다음 라운드를 진행할지 여부를 묻고, 이를 y/n의 문자로 입력 받습니다.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //필요한 헤더파일 추가
#define MAX 30 //배열 최대 크기 설정

void rand_word(char* word); //단어장에서 단어 하나를 가져오는 함수
int game_board(int* lifes,int* j, char* print_word, char* word, char* use); //게임 포멧을 출력하는 함수
int compare_answer(char* word, char* print_word, char ans); //입력받은 문자와 단어를 비교하는 함수

int main(void)
{
	int lifes, i, length, j;
	int count;
	char conti;
	char word[MAX], print_word[MAX], use[MAX] = { "" }; //변수 및 배열 선언
	printf("Let's play the hangman game!\n"); //제목 출력
	
	while (1) { //라운드 반복용
		j = 0; //입력받은 문자를 문자열로 옮기기 위한 변수 초기화
		count = 0; //문자 일치 개수 초기화
		lifes = 10; //행맨의 목숨을 10으로 초기화
		length = 0; //단어 길이 초기화
		for (i = 0; i < MAX; i++){
			print_word[i] = ' '; //출력용 배열 초기화
			use[i] = ' '; //입력받은 문자를 저장하는 배열 초기화
		}
		rand_word(word); //단어장에서 단어 하나 불러오기
		
		while (word[length] != '\n')
			length++; //단어의 길이 파악
		for (i = 0; i < length; i++) {
			print_word[i] = '_';
		} //출력되는 단어 설정

		while (1) { //라운드 내부에서 출력과 입력 반복
			if (lifes == 0) {
				printf("\nWord: ");
				for (i = 0; i < length; i++) {
					printf("%c ", print_word[i]);
				} //현재까지 맞춘 현황 출력

				printf("\nUsed: ");
				for (i = 0; i < MAX; i++) {
					printf("%c ", use[i]);
				} //이때까지 사용한 문자 출력
				printf("\nHangman (%d life)\n", lifes);
				printf("\nMission Failed!\n");
				printf("The answer was %s\n", word);
				break;
			} //목숨이 0이 될 경우 실패 메세지와 답 출력 후 라운드 종료
			else if (count == length) {
				printf("\nWord: ");
				for (i = 0; i < length; i++) {
					printf("%c ", print_word[i]);
				} //현재까지 맞춘 현황 출력

				printf("\nUsed: ");
				for (i = 0; i < MAX; i++) {
					printf("%c ", use[i]);
				} //이때까지 사용한 문자 출력
				printf("\nHangman (%d life)\n", lifes);
				printf("\nCongratulations!\n");
				printf("The answer was %s\n", word);
				break;
			} //count 값이 length값과 같은 경우(정답을 맞춘 경우) 성공 메세지와 답 출력 후 라운드 종료
			else {
				count=game_board(&lifes, &j, print_word, word, use);
				continue;
			} //그 외의 경우 게임 계속 수행
		}

		printf("Do you want to play again? (y/n) ");
		scanf("%c", &conti); //다시 플레이할 지 여부 확인

		if (conti == 'y') {
			getchar();
			continue;
		}//y를 입력 받으면 다음 라운드 진행
		else
			break; //n을 입력 받으면 게임 종료
	}
	printf("\nGood bye!\n");
	return 0;
}

void rand_word(char* word) 
{
	srand(time(NULL));
	int word_select, word_num;
	int count = 0; //변수 선언
	FILE* dic = fopen("dic.txt", "r"); //단어장 파일 열기
	if (!dic) {
		printf("Error opening dictionary.\n");
		exit(101);
	} //단어장 파일이 없을 시 오류 메세지 출력
	else {
		fscanf(dic, "%d", &word_num); //파일에서 단어 불러오기
		word_select = rand() % word_num + 2; //단어장에서 몇 번째 단어를 불러올지 랜덤으로 설정
		while (fgets(word, MAX, dic) != NULL) {
			count++;
			if (count == word_select)
				break;
		} //해당 단어를 불러오면 단어 불러오기 종료
	}
	fclose(dic); //파일 닫기
	return;
}

int game_board(int* lifes, int* j, char* print_word, char* word, char* use)
{
	int length = 0, a, i, count=0;
	char ans; //변수 선언
	while (word[length] != '\n')
		length++; //단어 길이 확인

	printf("\nWord: ");
	for (i = 0; i < length; i++) {
		printf("%c ", print_word[i]);
	} //현재까지 맞춘 현황 출력

	printf("\nUsed: ");
	for (i = 0; i < MAX; i++) {
		printf("%c ", use[i]);
	} //이때까지 사용한 문자 출력
	printf("\nHangman (%d life) - Input: ", *lifes); //행맨의 남은 목숨 출력

	scanf("%c", &ans); //문자 하나 입력받기
	a=compare_answer(word, print_word, ans); //문자와 단어를 비교

	for (i = 0; i < MAX; i++) {
		if (use[i] == ans) {
			printf("%c: Already inserted character.\n", ans);
			getchar();
			return;
		}
	}//중복된 문자 입력 시 오류 메세지 출력
	
	use[*j] = ans; //입력 받은 문자를 다른 문자열에 대입
	(*j)++;
	getchar(); //버퍼 비우기

	for (i = 0; i < length; i++) {
		if (word[i] == print_word[i]) {
			count++;
		}
	}//단어와 이때까지 맞춘 문자열의 문자가 같은 개수만큼 count 증가
	if (count == length)
		return count; //count가 length와 같으면(단어와 출력 문자열이 일치하면) count 반환

	if (a == 0)
		(*lifes)--; //단어에서 입력받은 문자와 일치하는 문자가 없으면 목숨 1씩 차감
	return;
}

int compare_answer(char* word, char* print_word, char ans)
{
	int length = 0;
	int count = 0;
	int i; //변수 선언
	while (word[length] != '\n')
		length++; //단어 길이 확인
	for (i = 0; i < length; i++) {
		if (word[i] == ans) {
			print_word[i] = ans;
			count++; //문자가 일치하는지 확인하는 용도
		}
	} //입력받은 문자와 단어의 문자가 같으면 출력 문자열에서 해당 문자로 바꾸어서 출력

	if (count == 0)
		return 0; //일치하는 문자가 없으면 0 반환
	else
		return 1; //일치하는 문자가 있으면 1 반환
}
