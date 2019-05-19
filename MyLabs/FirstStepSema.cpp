#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <ctype.h>

void cutString(char str[81], const int beginpos, const int endpos) {
	int l = strlen(str);// длина строки
	
	int len = endpos - beginpos;//количество символов, чтобы удалить
	if (endpos < beginpos)
		len = beginpos - endpos;

	//if (len < 0) len = l - beginpos;//если количество меньше нуля
	if (beginpos + len > l) len = l - beginpos;//если вылезает за длину строки
	if (endpos < beginpos)
		memmove(str + endpos, str + endpos + len, l - len + 1);
	else
		memmove(str + beginpos, str + beginpos + len, l - len + 1);//удаление
}

void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	int numL = 0;
	int numLi = -1, numLj = -1, numRi = -1, numRj = -1;
	int index, counter = 0;
	bool EndCount = false;
	char tempstring[81];
	int pos = 0;
	index = characterIndex; 
	char bracket;


	for (int i = lineIndex; i < strCount && !(EndCount); i++) {
		strcpy(tempstring, text[i]);
		pos = 0; index = 0;
		if (characterIndex != 0 && i == lineIndex) {
			pos = characterIndex;
			cutString(tempstring, 0, pos);
		}
		while (strcspn(tempstring, "()") != strlen(tempstring)) {
			pos += index;
			index = strcspn(tempstring, "()");
			bracket = tempstring[index];
			cutString(tempstring, 0, index + 1);
			switch (bracket) {
			case '(':
				counter++;
				if (numL == 0) {
					numLi = i;
					numLj = index + pos;
				}
				if (!EndCount && numRi != -1 && counter > 0)
					EndCount = true;
				numL++;
				break;
			case ')':
				counter--;
				//баг с парными скобками
				if (counter >= 0 && !EndCount) {
					numRi = i;
					numRj = pos + index;
					if ((numRj == numLj || pos == 0) && (numLi == numRi)) numRj++;
					if(counter == 0)
						EndCount = true;
				}
				if (counter < 0 && !EndCount) {
					numLi = -1;
					numLj = -1;
					numL = 0;
					counter = 0;
				}
				break;
			}
			index++;
		}
	}

	if (EndCount || counter >= 0) {
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

bool CompareBrackets(const int Current[4], const int Result[4]) {
	for (int i = 0; i < 4; i++)
		if (Current[i] != Result[i])
			return false;
	return true;
}

void UnitTests() {
	const int TestsCounterForFind = 6;
	
	//тестирование поиска скобок
	int brackets[4] = { -1, -1, -1, -1 };
	const char tests[TestsCounterForFind][256] = {
		"Not correct start position (lineIndex or charIndex)",
		"Not correct srtCount",
		"Haven\'t pos",
		"Don\'t stop count",
		"Forget initialize index",
		"Forget add indexes to array"
	};
	const int strCounts[TestsCounterForFind] = { 1, 1, 2, 2, 1, 2};
	const char texts[TestsCounterForFind][2][81] = {
		{
			"(start here (main)"
		}, 
		{
			"W((W))",
			"I )want it"
		}, 
		{
			"Hey man ( today ()",
			"We start) what\'s up?"
		}, 
		{
			"Wow()",
			"Time to stop(!)"
		}, 
		{
			"hmm((dude))..."
		},
		{
			"((",
			")"
		}
	};
	const int StartIndexes[TestsCounterForFind][2] = {
		{0, 1},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	};
	const int RightBrackets[TestsCounterForFind][4] = {
		{0, 12, 0, 17}, 
		{0, 1, 0, 5}, 
		{0, 8, 1, 8}, 
		{0, 3, 0, 4},
		{0, 3, 0, 10},
		{0, 0, 1, 0}
	};
	bool Success;

	Success = true;
	for (int i = 0; i < TestsCounterForFind; i++) {
		findPairBrackets(texts[i], strCounts[i], StartIndexes[i][0], StartIndexes[i][1], brackets);
		if (!CompareBrackets(brackets, RightBrackets[i]))
			printf("Incorrect test %d) in %s\n", i+1, tests[i]);
		Success = Success && CompareBrackets(brackets, RightBrackets[i]);
	}
	if (Success)
		printf("Tests passed for func findPairBrackets!\n");

	//тестирование обрезание строк

	const int TestForString = 3;
	const char Description[TestForString][256] = {
		"Swap begin and end (haven\'t if-condition)",
		"More, than lehgt of string",
		"Bad memmove"
	};
	char strings[TestForString][81] = {
		"rat rat rat",
		"fat fat fat fat",
		"move move"
	};
	const int Indexes[TestForString][2] = {
		{3, 0}, {0, 17}, {0, 5}
	};
	const char Answers[TestForString][81] = {
		" rat rat",
		"", 
		"move"
	};

	printf("\n");

	Success = true;
	for (int i = 0; i < TestForString; i++) {
		cutString(strings[i], Indexes[i][0], Indexes[i][1]);
		if (strcmp(strings[i], Answers[i]))
			printf("Incorrect test %d) in %s\n", i+1, tests[i]);
		Success = Success && !strcmp(strings[i], Answers[i]);
	}
	if (Success)
		printf("Tests passed for func cutString!\n");
}

int main() {
	//UnitTests();

	char text[20][81];
	int M;
	scanf("%d\n", &M);
	
	if (M < 1 || M > 20) {
		printf("Invalid data\n");
		return 0;
	}

	for (int i = 0; i < M; i++) {
		gets_s(text[i]);
		if (strlen(text[i]) > 81) {
			printf("Invalid data\n");
			return 0;
		}
	}

	int brackets[4] = {-1, -1, -1, -1};

	//findPairBrackets(text, M, 0, 0, brackets);

	//for (int i = 0; i < 4; i++)
	//	printf("%d ", brackets[i]);
	//printf("\n");
	//for (int i = 0; i < M; i++) {
	//	cutString(text[i], brackets[1], brackets[3] + 1);
	//}
	//print(text, M);
	
	int StopLine = 0, StopChar = 0;
	while (StopChar != -1) {
		findPairBrackets(text, M, StopLine, StopChar, brackets);
		if (brackets[2] != -1) {
			int m = brackets[0];
			if (m != brackets[2]) {
				cutString(text[m], brackets[1], strlen(text[m]));
				++m;
				//баги здесь - строки за массивом
				while (m != brackets[2]) {
					cutString(text[m], 0, strlen(text[m]));
					strcpy(text[m], text[m + 1]);
					m++; M--;
				}
				m = brackets[0] + 1;
				cutString(text[m], 0, brackets[3] + 1);
				if (isspace(text[m][0])) { 
					strcpy(text[m], text[m + 1]);
					m++; M--; 
				}
			}
			else
				cutString(text[m], brackets[1], brackets[3] + 1);
		}
		StopLine = brackets[0]; StopChar = brackets[1];
		for (int i = 0; i < 4; i++)
			brackets[i] = -1;
	}
	print(text, M);

	return 0;
}
