#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <ctype.h>

void cutString(char str[81], int beginPos, int endPos) {
	int StokLen = strlen(str);// длина строки

	int DeleteLen = endPos - beginPos + 1;//количество символов, которое надо удалить

	if (endPos < beginPos)//если символы перепутаны
		DeleteLen = beginPos - endPos + 1;

	if (beginPos + DeleteLen > StokLen) //если удаляемая часть вылезает вылезает за длину строки
		DeleteLen = StokLen - beginPos + 1;

	if (endPos < beginPos) //удаление при перепутанных позициях начала и конца
		memmove(str + endPos, str + endPos + DeleteLen, StokLen - DeleteLen + 1);
	else
		memmove(str + beginPos, str + beginPos + DeleteLen, StokLen - DeleteLen + 1);//простое удаление
}

void print(const char text[20][81], int M) {
	for (int i = 0; i < M; i++) {
		if (strlen(text[i]) == 0)
			continue;
		puts(text[i]); printf("\n");
	}
}

int main() {
	char text[20][81];
	char symbols[255];
	int N, M;
	
	scanf("%d", &N);
	if (N < 1 || N > 255)
		return 0;
	
	scanf("%s\n", &symbols);
	if (strlen(symbols) > N + 1)
		return 0;

	scanf("%d\n", &M);
	if (M < 1 || M > 255)
		return 0;

	
	for (int i = 0; i < M; i++) {//ввод текста
		gets_s(text[i]);
		if (strlen(text[i]) > 81) {//тест на корректные данные
			printf("Invalid data\n");
			return 0;
		}
	}
	print(text, M);
	
	int index;
	for (int i = 0; i < M; i++)
		while (strcspn(text[i], symbols) != strlen(text[i]) ) {
			index = strcspn(text[i], symbols);
			cutString(text[i], index, index);
		}
	print(text, M);

	return 0;
}