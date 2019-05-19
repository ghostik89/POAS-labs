// ForGhost.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string.h>
#include "testing.h"

void cutString(char str[81], int beginPos, int endPos) {
	char str1[81];
	char str2[81];

	for(int i=0;i<strlen(str);i++)
	{
		str1[i]=0;
		str2[i]=0;
	}

	//запись частей до и после заданного слова исходного предложения в независимые строки
	strncpy(str1, str, beginPos);
	strcpy(str2, str+endPos);

	//обнуление исходной строки
	for(int i=0;i<strlen(str);i++)
	{
		str[i]=0;
	}

	//запись частей из независимых предложений в исходное
	strcpy(str, str1);
	if(strlen(str2) != 0)
		strcat(str, str2);
}

void findPairBrackets1(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	int i, j, k, l, BracketsCounter = 0;
	bool IsSecond = false;
	char* localBrackets[40][2];

	for(i = 0; i < strCount; i++) {
		for(j = 0; j < strlen(text[i]); j++) {
			if(text[i][j] == '(') {
				localBrackets[BracketsCounter][0] = (char*)text[i][j];
				
				for(k = i; k < strCount; k++) {
					for(l = j; l < strlen(text[k]); l++) {
						if(text[k][l] == ')' && IsSecond == false) {
							IsSecond = true;
							localBrackets[BracketsCounter][1] = (char*)&text[k][l];
							BracketsCounter++;
							j = l;
						}
						if(text[k][l] == '(' && IsSecond == false)
							localBrackets[BracketsCounter][0] = (char*)&text[k][l];
					}
				}
			}
			IsSecond = false;
		}
	}
}

void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	int i, j, k, l, BracketsCounter = 0;
	bool IsSecond = false;
	//char* localBrackets[40][2];

	for(i = lineIndex; i < strCount; i++) {
		for(j = characterIndex; j < strlen(text[i]); j++) {
			if(text[i][j] == '(' && IsSecond == false) {
				brackets[0] = i;
				brackets[1] = j;
				for(k = i; k < strCount; k++) {
					for(l = j; l < strlen(text[k]); l++) {
						if(text[k][l] == ')' && IsSecond == false) {
							IsSecond = true;
							brackets[2] = k;
							brackets[3] = l;
							//BracketsCounter++;
							j = l;
						}
						if(text[k][l] == '(' && IsSecond == false) {
							brackets[0] = k;
							brackets[1] = l;
						}
					}
				}
			}
			IsSecond = false;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	char text[20][81];
	int M;

	int brackets[4] = {0, 0, 0, 0};

	input_printf("Введите количество строк в тексте (от 1 до 20),\nзатем введите сами строки (не больше 81 символа каждая): ");
	scanf("%d\n", &M);
	if(M<1 || M>20)
	{
		error_printf("Invalid data");
		return 0;
	}

	for (int i = 0; i < M; i++)
		gets_s(text[i]);

	for (int i = 0; i < M; i++) {
		for(int j = 0; j < strlen(text[i]); j++) {
			findPairBrackets(text, M, (brackets[2] - brackets[0]), (brackets[3] - brackets[1]), brackets);

			if(brackets[0] == brackets[2]) {//пара скобок в одной строке
				if(brackets[3] != strlen(text[i]))
					brackets[3]++;
				else
					brackets[3];
				cutString(text[brackets[0]], brackets[1], brackets[3]);
			}
			else {//пара скобок проходит через несколько строк
				cutString(text[brackets[0]], brackets[1], strlen(text[i]));
				for(int k = i+1; k < brackets[3] - brackets[1]; k++) {
					cutString(text[k], 0, strlen(text[k]));
				}
				cutString(text[brackets[2]], 0, brackets[3]);
			}
		}
		for(int j = 0; j < M; j++)
			puts(text[j]);
		printf("\n");
	}

	_getch();

	return 0;
}

