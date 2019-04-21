#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string.h>

/*
	text � �������� �����
	strCount � ���-�� ����� ������
	lineIndex, characterIndex � ��������� ������� ������ (������ ������, ������ ������� � ������)
*/
void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]);
/*
	str � �������� ������
	beginPos, endPos � ��������� � �������� ������� ���������, ������� ���������� �������� (�������)
	�������� ������:
	str � ��������� ������
*/
void cutString(char str[81], int beginPos, int endPos);

int main() {
	char text[20][81];
	int M;
	scanf("%d", &M);

	for (int i = 0; i < M; i++)
		gets_s(text[i]);

	int brackets[4] = {-1, -1, -1, -1};
	findPairBrackets(text, M, 0, 0, brackets);

	for (int i = 0; i < 4; i++)
		printf("%d ", brackets[i]);

	return 0;
}

void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	int numL = 0, numR = 0;
	int posiL = 0, posjL = 0, posiR = 0, posjR = 0;

	for (int i = 1; i < strCount; i++) {
		for (int j = 0; text[i][j] != '\0'; j++) {
			switch (text[i][j]) {
				case ')':
						numR++;
				break;
				case '(':
					if (numL == 0) {
						posiL = i;
						posjL = j;
					}
					numL++;
				break;
			}
			if ((numL == numR) && numR > 0 && numL > 0) {
				//posiR = i;
				//posjR = j;
				brackets[0] = posiL;
				brackets[1] = posjL;
				brackets[2] = i;
				brackets[3] = j;
				break;
			}
		}
		if (brackets[0] != -1) {
			strCount -= i;
			break;
		}
	}
}

void cutString(char str[81], int beginPos, int endPos) {
	for (int i = beginPos; i < endPos || str[i] != '\0'; i++)
		str[i] = " ";
}