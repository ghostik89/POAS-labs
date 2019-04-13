#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

/*
	text Ц исходный текст
	strCount Ц кол-во строк текста
	lineIndex, characterIndex Ц начальна€ позици€ поиска (индекс строки, индекс символа в строке)
*/
void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]);

/*
	str Ц исходна€ строка
	beginPos, endPos Ц начальна€ и конечна€ позиции подстроки, которую необходимо вырезать (удалить)
	¬ыходные данные:
	str Ц усеченна€ строка
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