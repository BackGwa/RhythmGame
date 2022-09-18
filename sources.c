#define _CRT_SECURE_NO_WARNINGS
#define NOTE_COUNT 10

#pragma comment(lib, "winmm.lib")

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include<mmsystem.h>

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CursorView() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void scolor(unsigned short text, unsigned short back){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

int mainmemu();
void wepcrt();
void setting();
void CountDown();
void rank();
void rplay(int nanidoA);
void selectMain();
void refrash_Array();
void pj(int valueA);
void rankrefrash();
void randomnanido();
void help();
void logooutput();
void playsoundA(int hz, int ms);
void scst();

char* rankname[6] = { "" };
int rankscore[6] = { 0 };
int gp_nanido = 0, themeBug = 0, beep_play = 1;

int main() {
	system("mode con cols=77 lines=25 | title Rhythm Game | color 0F");
	CursorView(0);

	logooutput();
	mainmemu();

	return 0;
}

void wepcrt() {

	char PlayerNamed[16] = "";
	int nanido = 0;

	gotoxy(19, 12); printf("플레이어의 이름을 입력하세요. ▷ ____\b\b\b\b");
	scanf("%s", PlayerNamed);
	rankname[5] = PlayerNamed;
	playsoundA(4, 250);

	gotoxy(25, 13); printf("난이도를 입력하세요. ▷ __\b\b");
	scanf("%d", &nanido);
	playsoundA(5, 1000);

	if (nanido > 10) {
		gotoxy(22, 13);
		scolor(15, 12);
		printf("난이도가 10을 넘을 수 없습니다!");
		playsoundA(2, 250);
		Sleep(2000);
		if (themeBug == 0) {
			scolor(15, 0);
		}
		else {
			scolor(0, 15);
		}
		mainmemu();
	}
	else if (nanido == 0) {
		gotoxy(22, 13);
		scolor(0, 10);
		printf("난이도가 무작위로 선택됩니다!!");
		playsoundA(2, 250);
		Sleep(2000);
		if (themeBug == 0) {
			scolor(15, 0);
		}
		else {
			scolor(0, 15);
		}
		randomnanido();
	}
	else if (nanido < 0) {
		gotoxy(22, 13);
		scolor(15, 12);
		printf("난이도가 0보다 작을 수 없습니다!");
		playsoundA(2, 250);
		Sleep(2000);
		if (themeBug == 0) {
			scolor(15, 0);
		}
		else {
			scolor(0, 15);
		}
		mainmemu();
	}
	else if (nanido != 0) {
		gp_nanido = nanido;
		system("cls");
		CountDown();
	}
}

void setting() {

	system("cls");
	char keyboardMove = ' ';
	int y = 4;

	gotoxy(18, 2); printf("┌─────┤  환경설정  ├─────┐");
	gotoxy(18, 4); printf("\t   [ ① ]  테마 : 화이트");
	gotoxy(18, 5); printf("\t   [ ② ]   테마 : 블랙");
	gotoxy(18, 6); printf("\t   [ ③ ]  소리 켜기/끄기");
	gotoxy(18, 7); printf("\t   [ ⓧ ]    뒤로가기");
	gotoxy(18, 9); printf("└──────────────────┘");
	gotoxy(29, y); printf("●");

	while (1) {

		keyboardMove = _getch();

		gotoxy(29, 4); printf("①");
		gotoxy(29, 5); printf("②");
		gotoxy(29, 6); printf("③");
		gotoxy(29, 7); printf("ⓧ");

		if (keyboardMove == 72) {
			if (y != 4) {
				y = y - 1;
				gotoxy(29, y);
				printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
			gotoxy(29, y);
			printf("●");
		}
		else if (keyboardMove == 80) {
			if (y != 7) {
				y = y + 1;
				gotoxy(29, y);
				printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
			gotoxy(29, y);
			printf("●");
		}

		else if (keyboardMove == 13) {

			gotoxy(29, y);
			printf("●");
			playsoundA(2, 400);

			switch (y) {
			case 4: system("color F0"); themeBug = 1;  continue;
			case 5: system("color 0F"); themeBug = 0; continue;
			case 6: scst(); continue;
			case 7: mainmemu(); break;
			}
			break;
		}
		gotoxy(29, y);
		printf("●");
	}
}

int mainmemu() {

	system("cls");
	char keyboardMove = ' ';
	int y = 4;

	gotoxy(18, 2); printf("┌─────┤  리듬게임  ├─────┐");
	gotoxy(18, 4); printf("\t   [ ① ]  플레이 게임");
	gotoxy(18, 5); printf("\t   [ ② ]     랭크");
	gotoxy(18, 6); printf("\t   [ ③ ]   환경 설정");
	gotoxy(18, 7); printf("\t   [ ⓧ ]   게임 종료");
	gotoxy(18, 9); printf("└──────────────────┘");

	gotoxy(29, y); printf("●");
	gotoxy(16, 20); printf("[ H ] 키를 눌러 도움말에 진입할 수 있습니다!");

	while (1) {

		keyboardMove = _getch();

		gotoxy(29, 4); printf("①");
		gotoxy(29, 5); printf("②");
		gotoxy(29, 6); printf("③");
		gotoxy(29, 7); printf("ⓧ");

		if (keyboardMove == 72) {
			if (y != 4) {
				y = y - 1;
				gotoxy(29, y);
				printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
			gotoxy(29, y);
			printf("●");
		}
		else if (keyboardMove == 80) {
			if (y != 7) {
				y = y + 1;
				gotoxy(29, y);
				printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
			gotoxy(29, y);
			printf("●");
		}

		else if (keyboardMove == 13) {

			gotoxy(29, y);
			printf("●");

			switch (y) {
			case 4: playsoundA(3, 300); wepcrt(); break;
			case 5: playsoundA(2, 300); rank();  break;
			case 6: playsoundA(2, 300); setting(); break;
			case 7: playsoundA(2, 300); system("cls"); return 0;  break;
			}
			break;
		}

		else if (keyboardMove == 'h' || keyboardMove == 'H') {
			playsoundA(2, 300);
			help();
			break;
		}

		gotoxy(29, y);
		printf("●");
	}
	return 0;
}

void rank() {

	system("cls");
	refrash_Array();
	rankrefrash();
	char keyboardMove = ' ';
	int x = 22;

	gotoxy(x, 20); printf("●");

	while (1) {
		keyboardMove = _getch();

		if (keyboardMove == 75) {
			if (x != 22) {
				x = 22;
				gotoxy(20, 20); printf("[ ① ]  메인 메뉴");
				gotoxy(40, 20); printf("[ ② ]  랭크 초기화");
				gotoxy(x, 20); printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
		}
		else if (keyboardMove == 77) {
			if (x != 42) {
				x = 42;
				gotoxy(20, 20); printf("[ ① ]  메인 메뉴");
				gotoxy(40, 20); printf("[ ② ]  랭크 초기화");
				gotoxy(x, 20); printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
		}
		else if (keyboardMove == 13) {

			gotoxy(x, 20); printf("●");
			playsoundA(2, 300);

			switch (x) {
			case 22: system("cls"); mainmemu(); break;
			case 42:

				for (int i = 0; i < 6; i++) {
					rankscore[i] = 0;
				}

				system("cls");
				rankrefrash();
				gotoxy(x, 20); printf("●");

				continue;
			}
			break;
		}
	}
}

void CountDown() {

	system("cls");

	gotoxy(10, 9);  printf("　■■■■"); gotoxy(22, 9);  printf("　■■■　"); gotoxy(34, 9);  printf("■　　　■"); gotoxy(46, 9);  printf("■■　　■"); gotoxy(58, 9);  printf("■■■■■");
	gotoxy(10, 10); printf("■　　　　"); gotoxy(22, 10);  printf("■　　　■"); gotoxy(34, 10);  printf("■　　　■"); gotoxy(46, 10); printf("■■　　■"); gotoxy(58, 10); printf("　　■　　");
	gotoxy(10, 11); printf("■　　　　"); gotoxy(22, 11);  printf("■　　　■"); gotoxy(34, 11);  printf("■　　　■"); gotoxy(46, 11); printf("■　■　■"); gotoxy(58, 11); printf("　　■　　");
	gotoxy(10, 12); printf("■　　　　"); gotoxy(22, 12);  printf("■　　　■"); gotoxy(34, 12);  printf("■　　　■"); gotoxy(46, 12); printf("■　■　■"); gotoxy(58, 12); printf("　　■　　");
	gotoxy(10, 13); printf("　■■■■"); gotoxy(22, 13);  printf("　■■■　"); gotoxy(34, 13);  printf("　■■■　"); gotoxy(46, 13); printf("■　　■■"); gotoxy(58, 13); printf("　　■　　");

	if (themeBug == 0) {
		system("color F0"); playsoundA(1, 400); Sleep(150); system("color 0F");
	}
	else {
		system("color 0F"); playsoundA(1, 400); Sleep(150); system("color F0");
	}

	Sleep(1000);
	system("cls");

	gotoxy(32, 9);  printf("■■■■■");
	gotoxy(32, 10);  printf("　　　　■");
	gotoxy(32, 11);  printf("■■■■■");
	gotoxy(32, 12);  printf("　　　　■");
	gotoxy(32, 13);  printf("■■■■■");
	playsoundA(2, 200);
	Sleep(700);
	gotoxy(32, 9);  printf("■■■■■");
	gotoxy(32, 10);  printf("　　　　■");
	gotoxy(32, 11);  printf("■■■■■");
	gotoxy(32, 12);  printf("■　　　　");
	gotoxy(32, 13);  printf("■■■■■");
	playsoundA(2, 200);
	Sleep(700);
	gotoxy(32, 9);  printf("　　■　　");
	gotoxy(32, 10);  printf("　　■　　");
	gotoxy(32, 11);  printf("　　■　　");
	gotoxy(32, 12);  printf("　　■　　");
	gotoxy(32, 13);  printf("　　■　　");
	playsoundA(2, 200);
	Sleep(700);
	rplay(gp_nanido);
}

void rplay(int nanidoA) {

	int set = 110 - (nanidoA * 10);
	int note = NOTE_COUNT, score = 0;
	char inputA = 'A';
	system("cls");

	gotoxy(15, 10); printf("┌──┰──────────────────┐");
	gotoxy(15, 11); printf("│　　┃　　　　　　　　　　　　　　　　　　│");
	gotoxy(15, 12); printf("│　　┃　　　　　　　　　　　　　　　　　　│");
	gotoxy(15, 13); printf("└──┸──────────────────┘");
	gotoxy(16, 15); printf("남은 노트 : %2d개", note);
	gotoxy(48, 15); printf("점수 :                     ");
	gotoxy(48, 15); printf("점수 : %4d", score);

	while (note != 0) {
		int x = 0, outline = 1;

		outline = 1;
		x = 0;

		for (int j = 58; j > 0; j--) {
			if (outline == 0) {
				break;
			}
			else {
				x = j;
				gotoxy(15, 10); printf("┌──┰──────────────────┐");
				gotoxy(15, 11); printf("│　　┃　　　　　　　　　　　　　　　　　　│");
				gotoxy(15, 12); printf("│　　┃　　　　　　　　　　　　　　　　　　│");
				gotoxy(15, 13); printf("└──┸──────────────────┘");

				gotoxy(x, 11); printf("◆"); gotoxy(x - 2, 11); printf("　");
				gotoxy(x, 12); printf("◆"); gotoxy(x - 2, 12); printf("　");

				gotoxy(16, 15); printf("남은 노트 : %2d개", note);
				gotoxy(48, 15); printf("점수 :                     ");
				gotoxy(48, 15); printf("점수 : %4d", score);

				if (j % 10 == 0 && x > 16) {
					playsoundA(1, 300);
				}

				Sleep(set);

				while (1) {
					if (_kbhit()) {
						_getch();
						if (x > 17 && x < 30) {
							if (x > 10 && x < 24) {
								playsoundA(2, 200);
								score += (nanidoA * 100);
								pj(3);
							}
							else {
								playsoundA(2, 200);
								score += (nanidoA * 50);
								pj(2);
							}
						}
						else {
							playsoundA(1, 200);
							score -= (nanidoA * 50);
							pj(1);
						}
						outline = 0;
						break;
					}
					else {
						break;
					}
					gotoxy(16, 15); printf("남은 노트 : %2d개", note);
					gotoxy(48, 15); printf("점수 :                     ");
					gotoxy(48, 15); printf("점수 : %4d", score);
				}

				if (x == 16) {
					score -= (nanidoA * 50);
					playsoundA(1, 300);
					outline = 0;
					pj(1);
					break;
				}
			}
		}
		note -= 1;
	}

	system("cls");
	gotoxy(31, 8); printf("[ 게임 종료! ]");
	playsoundA(1, 250);
	Sleep(500);
	gotoxy(30, 10); printf("최종 점수 : %4d", score);
	playsoundA(1, 250);

	rankscore[5] = score;
	refrash_Array();

	Sleep(500);
	playsoundA(2, 250);
	selectMain();
}

void selectMain() {

	char keyboardMove = ' ';
	int x = 22;

	gotoxy(16, 12); printf("┌─────────────────────┐");
	gotoxy(16, 13); printf("│"); gotoxy(20, 13); printf("[ ① ]  메인 메뉴"); gotoxy(40, 13); printf("[ ② ]  게임 종료"); gotoxy(60, 13); printf("│");
	gotoxy(16, 14); printf("└─────────────────────┘");
	gotoxy(x, 13); printf("●");

	while (1) {
		keyboardMove = _getch();

		if (keyboardMove == 75) {
			if (x != 22) {
				x = 22;
				gotoxy(20, 13); printf("[ ① ]  메인 메뉴");
				gotoxy(40, 13); printf("[ ② ]  게임 종료");
				gotoxy(x, 13); printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
		}
		else if (keyboardMove == 77) {
			if (x != 42) {
				x = 42;
				gotoxy(20, 13); printf("[ ① ]  메인 메뉴");
				gotoxy(40, 13); printf("[ ② ]  게임 종료");
				gotoxy(x, 13); printf("●");
				playsoundA(1, 300);
			}
			else {
				playsoundA(1, 300);
			}
		}
		else if (keyboardMove == 13) {

			gotoxy(x, 13); printf("●");
			playsoundA(2, 400);

			switch (x) {
			case 22: system("cls"); mainmemu(); break;
			case 42: system("cls"); break;
			}
			break;
		}
	}
}

void refrash_Array() {
	int temp = 0;
	char* name_temp = "";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6 - i - 1; j++) {
			if (rankscore[j] < rankscore[j + 1]) {
				temp = rankscore[j];
				name_temp = rankname[j];
				rankscore[j] = rankscore[j + 1];
				rankname[j] = rankname[j + 1];
				rankscore[j + 1] = temp;
				rankname[j + 1] = name_temp;
			}
		}
	}
}

void pj(int valueA) {

	if (valueA == 1) {
		gotoxy(14, 2); printf("■　　　■"); gotoxy(26, 2); printf("　　■　　"); gotoxy(38, 2); printf("■■■■■"); gotoxy(50, 2); printf("■■■■■");
		gotoxy(14, 3); printf("■■　■■"); gotoxy(26, 3); printf("　　■　　"); gotoxy(38, 3); printf("■　　　　"); gotoxy(50, 3); printf("■　　　　");
		gotoxy(14, 4); printf("■　■　■"); gotoxy(26, 4); printf("　　■　　"); gotoxy(38, 4); printf("■■■■■"); gotoxy(50, 4); printf("■■■■■");
		gotoxy(14, 5); printf("■　■　■"); gotoxy(26, 5); printf("　　■　　"); gotoxy(38, 5); printf("　　　　■"); gotoxy(50, 5); printf("　　　　■");
		gotoxy(14, 6); printf("■　■　■"); gotoxy(26, 6); printf("　　■　　"); gotoxy(38, 6); printf("■■■■■"); gotoxy(50, 6); printf("■■■■■");

		if (themeBug == 0) {
			system("color 4F"); Sleep(150); system("color 0F");
		}
		else {
			system("color 4F"); Sleep(150); system("color F0");
		}

	}

	else if (valueA == 2) {
		gotoxy(14, 2); printf("　■■■■"); gotoxy(26, 2); printf("　■■■　"); gotoxy(38, 2); printf("　■■■　"); gotoxy(50, 2); printf("■■■■　");
		gotoxy(14, 3); printf("■　　　　"); gotoxy(26, 3); printf("■　　　■"); gotoxy(38, 3); printf("■　　　■"); gotoxy(50, 3); printf("■　　　■");
		gotoxy(14, 4); printf("■　　■■"); gotoxy(26, 4); printf("■　　　■"); gotoxy(38, 4); printf("■　　　■"); gotoxy(50, 4); printf("■　　　■");
		gotoxy(14, 5); printf("■　　　■"); gotoxy(26, 5); printf("■　　　■"); gotoxy(38, 5); printf("■　　　■"); gotoxy(50, 5); printf("■　　　■");
		gotoxy(14, 6); printf("　■■■■"); gotoxy(26, 6); printf("　■■■　"); gotoxy(38, 6); printf("　■■■　"); gotoxy(50, 6); printf("■■■■　");

		if (themeBug == 0) {
			system("color 02"); Sleep(150); system("color 0F");
		}
		else {
			system("color F2"); Sleep(150); system("color F0");
		}

	}

	else if (valueA == 3) {
		gotoxy(14, 2); printf("■■　　■"); gotoxy(26, 2); printf("　　■　　"); gotoxy(38, 2); printf("■■■■■"); gotoxy(50, 2); printf("■■■■■");
		gotoxy(14, 3); printf("■　■　■"); gotoxy(26, 3); printf("　　■　　"); gotoxy(38, 3); printf("■　　　　"); gotoxy(50, 3); printf("■　　　　");
		gotoxy(14, 4); printf("■　■　■"); gotoxy(26, 4); printf("　　■　　"); gotoxy(38, 4); printf("■　　　　"); gotoxy(50, 4); printf("■■■■■");
		gotoxy(14, 5); printf("■　■　■"); gotoxy(26, 5); printf("　　■　　"); gotoxy(38, 5); printf("■　　　　"); gotoxy(50, 5); printf("■　　　　");
		gotoxy(14, 6); printf("■　　■■"); gotoxy(26, 6); printf("　　■　　"); gotoxy(38, 6); printf("■■■■■"); gotoxy(50, 6); printf("■■■■■");

		if (themeBug == 0) {
			system("color 03"); Sleep(150); system("color 0F");
		}
		else {
			system("color F3"); Sleep(150); system("color F0");
		}

	}
}

void rankrefrash() {

	gotoxy(16, 2); printf("┌──────┤ 플레이어 랭크 ├──────┐");

	if (rankscore[0] != 0) {
		gotoxy(24, 4); printf("[1]  %s님\t|\t%3d점", rankname[0], rankscore[0]);
	}
	if (rankscore[1] != 0) {
		gotoxy(24, 5); printf("[2]  %s님\t|\t%3d점", rankname[1], rankscore[1]);
	}
	if (rankscore[2] != 0) {
		gotoxy(24, 6); printf("[3]  %s님\t|\t%3d점", rankname[2], rankscore[2]);
	}
	if (rankscore[3] != 0) {
		gotoxy(24, 7); printf("[4]  %s님\t|\t%3d점", rankname[3], rankscore[3]);
	}
	if (rankscore[4] != 0) {
		gotoxy(24, 8); printf("[5]  %s님\t|\t%3d점", rankname[4], rankscore[4]);
	}

	gotoxy(16, 17); printf("└─────────────────────┘");

	gotoxy(21, 12); printf("[ 랭크는 최대 5위까지 표시됩니다! ]");

	gotoxy(16, 19); printf("┌─────────────────────┐");
	gotoxy(16, 20); printf("│"); gotoxy(20, 20); printf("[ ① ]  메인 메뉴"); gotoxy(40, 20); printf("[ ② ]  랭크 초기화"); gotoxy(60, 20); printf("│");
	gotoxy(16, 21); printf("└─────────────────────┘");

}

void randomnanido() {

	system("cls");
	int sleeptime = 100, randomint = 0, realValue = 0;
	srand(time(NULL));
	int randomValue = 0;
	randomValue = rand() % 40;

	while (1) {
		gotoxy(32, 9);  printf("　　■　　");
		gotoxy(32, 10);  printf("　　■　　");
		gotoxy(32, 11);  printf("　　■　　");
		gotoxy(32, 12);  printf("　　■　　");
		gotoxy(32, 13);  printf("　　■　　");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■■■■■");
		gotoxy(32, 10);  printf("　　　　■");
		gotoxy(32, 11);  printf("■■■■■");
		gotoxy(32, 12);  printf("■　　　　");
		gotoxy(32, 13);  printf("■■■■■");
		Beep(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■■■■■");
		gotoxy(32, 10);  printf("　　　　■");
		gotoxy(32, 11);  printf("■■■■■");
		gotoxy(32, 12);  printf("　　　　■");
		gotoxy(32, 13);  printf("■■■■■");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■　　■　");
		gotoxy(32, 10);  printf("■　　■　");
		gotoxy(32, 11);  printf("■■■■■");
		gotoxy(32, 12);  printf("　　　■　");
		gotoxy(32, 13);  printf("　　　■　");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■■■■■");
		gotoxy(32, 10);  printf("■　　　　");
		gotoxy(32, 11);  printf("■■■■■");
		gotoxy(32, 12);  printf("　　　　■");
		gotoxy(32, 13);  printf("■■■■■");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■■■■■");
		gotoxy(32, 10);  printf("■　　　　");
		gotoxy(32, 11);  printf("■■■■■");
		gotoxy(32, 12);  printf("■　　　■");
		gotoxy(32, 13);  printf("■■■■■");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■■■■■");
		gotoxy(32, 10);  printf("■　　　■");
		gotoxy(32, 11);  printf("■　　　■");
		gotoxy(32, 12);  printf("　　　　■");
		gotoxy(32, 13);  printf("　　　　■");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■■■■■");
		gotoxy(32, 10);  printf("■　　　■");
		gotoxy(32, 11);  printf("■■■■■");
		gotoxy(32, 12);  printf("■　　　■");
		gotoxy(32, 13);  printf("■■■■■");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■■■■■");
		gotoxy(32, 10);  printf("■　　　■");
		gotoxy(32, 11);  printf("■■■■■");
		gotoxy(32, 12);  printf("　　　　■");
		gotoxy(32, 13);  printf("■■■■■");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;
		gotoxy(32, 9);  printf("■　■■■");
		gotoxy(32, 10);  printf("■　■　■");
		gotoxy(32, 11);  printf("■　■　■");
		gotoxy(32, 12);  printf("■　■　■");
		gotoxy(32, 13);  printf("■　■■■");
		playsoundA(1, 250); Sleep(sleeptime); ++randomint;
		if (randomint == randomValue) break;

		sleeptime += 100;
	}

	if (themeBug == 0) {
		system("color F0"); playsoundA(1, 250); Sleep(250);  system("color 0F"); playsoundA(2, 250);
	}
	else {
		system("color 0F"); playsoundA(1, 250); Sleep(250); system("color F0"); playsoundA(2, 250);
	}

	Sleep(1000);

	realValue = (randomint % 10);

	if (realValue == 0) {
		gp_nanido = 10;
		CountDown();
	}
	else {
		gp_nanido = realValue;
		CountDown();
	}
}

void help() {

	system("cls");
	char keyboardMove = ' ';

	gotoxy(4, 2); printf("┌───────────┤ 인게임 도움말 ├───────────┐");

	Sleep(700);
	playsoundA(1, 300);
	gotoxy(20, 4); printf("Rhythm Game에 오신 것을 환영합니다!");
	Sleep(1500);
	playsoundA(1, 300);
	gotoxy(13, 6); printf("메뉴 조작은 상 / 하 방향키와 'Enter'로 이루어집니다!");
	gotoxy(7, 8); printf("게임을 시작하기 전 '난이도' 설정은 최대 10까지 설정이 가능하며");
	gotoxy(12, 9); printf("0을 입력하면 게임 내에서 랜덤으로 난이도를 설정합니다.");
	Sleep(7500);
	playsoundA(1, 300);
	gotoxy(14, 11); printf("게임이 시작되고 노트가 판정선에 근접하게 될 때");
	gotoxy(10, 12); printf("'아무 키'나 눌러 판정선에 근접한 노트를 쳐서 제거하세요!");
	gotoxy(12, 13); printf("노트를 놓치거나 판정선에 근접하지 않았을 때 제거하면");
	gotoxy(14, 14); printf("해당 노트는 'MISS' 판정과 함께 점수가 내려갑니다!");
	gotoxy(4, 17); printf("└────────────────────────────────┘");

	gotoxy(16, 19); printf("┌─────────────────────┐");
	gotoxy(16, 20); printf("│"); gotoxy(28, 20); printf("[ ENTER ]  메인 메뉴"); gotoxy(60, 20); printf("│");
	gotoxy(16, 21); printf("└─────────────────────┘");

	while (1) {
		keyboardMove = _getch();
		if (keyboardMove == 13) {
			playsoundA(2, 400);
			mainmemu();
			break;
		}
	}
}

void logooutput() {
	gotoxy(32, 11); printf("R Production");
	Sleep(1000);
}

void playsoundA(int hz, int ms) {
	if (beep_play == 1) {
		if (hz == 1) {
			PlaySound(TEXT("taiko1.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(ms);
		}
		else if(hz == 2) {
			PlaySound(TEXT("taiko2.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(ms);
		}
		else if (hz == 3) {
			PlaySound(TEXT("playgame.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(ms);
		}
		else if (hz == 4) {
			PlaySound(TEXT("nameselect.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(ms);
		}
		else if (hz == 5) {
			PlaySound(TEXT("countdown.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(ms);
		}
	}
	else {
		Sleep(ms);
	}
}

void scst() {
	if (beep_play == 1) {
		beep_play = 0;
	}
	else {
		beep_play = 1;
	}
}