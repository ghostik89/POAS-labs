#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

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

	return 0;
}