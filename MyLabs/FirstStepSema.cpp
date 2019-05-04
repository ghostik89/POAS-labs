#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

void cutstring(char str[81], int beginpos, int endpos) {
	int l = strlen(str);// длина строки

	int len = endpos - beginpos;//количество символов, чтобы удалить

	if (len < 0) len = l - beginpos;//если количество меньше нуля
	if (beginpos + len > l) len = l - beginpos;//если вылезает за длину строки

	memmove(str + beginpos, str + beginpos + len, l - len + 1);//удаление
}

void cutString(char str[81], int beginPos, int endPos)
{
	char str1[81];
	char str2[81];

	for (int i = 0; i < strlen(str); i++)
	{
		str1[i] = 0;
	}

	strncpy(str1, str, beginPos);
	strcpy(str2, str + endPos);

	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = 0;
	}

	strcpy(str, str1);
	strcat(str, str2);
}

void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	int numL = 0, numR = 0;
	int numLi = 0, numLj = 0, numRi = 0, numRj = 0;
	int index, counter = 0;
	bool EndCount = false;
	bool NotCorrectBrackets = false;
	char tempstring[81];
	int pos = 0;
	index = characterIndex; char bracket;


	for (int i = lineIndex; i < strCount; i++) {
		strcpy(tempstring, text[i]);
		pos = 0;
		while (strcspn(tempstring, "()") != strlen(tempstring)) {
			pos += index;
			index = strcspn(tempstring, "()");
			bracket = tempstring[index];
			cutstring(tempstring, 0, index + 1);
			switch (bracket) {
			case '(':
				counter++;
				if (numL == 0 && !NotCorrectBrackets) {
					numLi = i;
					numLj = index + pos;
				}
				numL++;
				break;
			case ')':
				counter--;
				if (counter < 0) {
					NotCorrectBrackets = true;
				}
				if (counter == 0 && !EndCount && !NotCorrectBrackets) {
					numRi = i;
					numRj = pos + index;
					if (numRj == numLj || pos == 0) numRj++;
					EndCount = true;
				}
				break;
			}
			index++;
		}
		index = 0;
	}
	if (counter == 0 && !NotCorrectBrackets) {
		brackets[0] = numLi;
		brackets[1] = numLj;
		brackets[2] = numRi;
		brackets[3] = numRj;
	}
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
	int M;
	scanf("%d\n", &M);

	for (int i = 0; i < M; i++)
		gets_s(text[i]);

	int brackets[4] = {-1, -1, -1, -1};
	findPairBrackets(text, M, 0, 0, brackets);

	for (int i = 0; i < 4; i++)
		printf("%d ", brackets[i]);
	printf("\n");
	/*for (int i = 0; i < M; i++) {
		cutstring(text[i], brackets[1], brackets[3] + 1);
	}
	print(text, M);*/

	return 0;
}
