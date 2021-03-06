#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <ctype.h>

/*
	str � �������� ������
	beginPos, endPos � ��������� � �������� ������� ���������, ������� ���������� ��������
*/
void cutString(char str[81], const int beginpos, const int endpos) {
	int StokLen = strlen(str);// ����� ������
	
	int DeleteLen = endpos - beginpos;//���������� ��������, ������� ���� �������

	if (endpos < beginpos)//���� ������� ����������
		DeleteLen = beginpos - endpos;

	if (beginpos + DeleteLen > StokLen) //���� ��������� ����� �������� �������� �� ����� ������
		DeleteLen = StokLen - beginpos;

	if (endpos < beginpos) //�������� ��� ������������ �������� ������ � �����
		memmove(str + endpos, str + endpos + DeleteLen, StokLen - DeleteLen + 1);
	else
		memmove(str + beginpos, str + beginpos + DeleteLen, StokLen - DeleteLen + 1);//������� ��������
}
/*
	text � �������� �����
	strCount � ���-�� ����� ������
	lineIndex, characterIndex � ��������� ������� ������ (������ ������, ������ ������� � ������)
	
	bra�kets � ������� ���� ������;���� ���� ������ �� ����������, �� ��� ������� ����� -1
*/
void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	
	bool IsFirstLeftBracket;//��������� ������ ����� ������
	int FirstLeftBracketLine, FirstLeftBracketChar, LastRightBracketLine, LastRightBracketChar;//���������� ������� ������
	int TempIndexOfBrackets;//��������� ������ ���������� ������
	int CountBrackets; //��� �������� �� ������ ��������� ������������������
	bool EndCount;//����� �������� ��������
	int TotalPosition;//�������� �������

	//������������� ����������
	CountBrackets = 0;
	EndCount = false;
	IsFirstLeftBracket = false;
	FirstLeftBracketLine = -1; FirstLeftBracketChar = -1;
	LastRightBracketLine = -1;LastRightBracketChar = -1;


	for (int i = lineIndex; i < strCount && !(EndCount); i++) {
		char tempstring[81];//��������� ������ ��� ������ ��������
		strcpy(tempstring, text[i]);

		//������������� �������
		TotalPosition = 0; TempIndexOfBrackets = 0;
		if (characterIndex != 0 && i == lineIndex) {//���� ��������� ������� ������
			TotalPosition = characterIndex;
			cutString(tempstring, 0, TotalPosition);//������ �������� ������
		}

		//���� ����, ��� ������
		while (strcspn(tempstring, "()") != strlen(tempstring)) {
			
			TotalPosition += TempIndexOfBrackets;//��������� �������� �� ������
			TempIndexOfBrackets = strcspn(tempstring, "()");//���� ��������� ������
			char NowBracket;//������� ������
			NowBracket = tempstring[TempIndexOfBrackets];

			cutString(tempstring, 0, TempIndexOfBrackets + 1);//������ �������� ������
			
			//�������� ��� ��������� ������
			switch (NowBracket) {
			case '(':

				CountBrackets++;//�������� ������� ���������� ��������� ������������������

				if (!IsFirstLeftBracket) {//���� �� ��������� ����� ������
					FirstLeftBracketLine = i;
					FirstLeftBracketChar = TempIndexOfBrackets + TotalPosition;
					IsFirstLeftBracket = true;
				}

				//���� ��� ���������� ���������� ��������� ������������������
				//������ � ������� ��������
				if (!EndCount && LastRightBracketLine != -1 && CountBrackets > 0)
					EndCount = true;
				
				break;
			case ')':

				CountBrackets--;
				
				//���� �� ��������� ������ ������
				if (CountBrackets >= 0 && !EndCount) {
					LastRightBracketLine = i;
					LastRightBracketChar = TotalPosition + TempIndexOfBrackets;
					//������, ����� ������ ����� ������� ���� � �����
					if ((LastRightBracketChar == FirstLeftBracketChar || TotalPosition == 0) && (FirstLeftBracketLine == LastRightBracketLine)) 
						LastRightBracketChar++;
					//���������� ��������� ������������������ �������
					if(CountBrackets == 0)
						EndCount = true;
				}
				//���� ��������� ������������������ ���������� ������������
				if (CountBrackets < 0 && !EndCount) {
					FirstLeftBracketLine = -1;
					FirstLeftBracketChar = -1;
					IsFirstLeftBracket = false;
					CountBrackets = 0;
				}
				break;
			}
			TempIndexOfBrackets++;//�������� ��������� ������
		}
	}

	//���� ������ ��������� ������������� ������ �������
	if (EndCount || CountBrackets >= 0) {
		brackets[0] = FirstLeftBracketLine;
		brackets[1] = FirstLeftBracketChar;
		brackets[2] = LastRightBracketLine;
		brackets[3] = LastRightBracketChar;
	}
}

/*
	������� ������ ������
	const char text[20][81] - ����� ��� ������
	M - ���-�� ����
*/
void print(const char text[20][81], int M) {
	for (int i = 0; i < M; i++) {
		//���������� ������ ������
		if (strlen(text[i]) == 0)
			continue;
		puts(text[i]); printf("\n");
	}
}

/*
	������� ��������� ������� ������
*/
bool CompareBrackets(const int Current[4], const int Result[4]) {
	for (int i = 0; i < 4; i++)
		if (Current[i] != Result[i])
			return false;
	return true;
}

//���� �����
void UnitTests() {
	const int TestsCounterForFind = 6;
	
	//������������ ������ ������
	int brackets[4] = { -1, -1, -1, -1 };//������ ��� ������ ������
	const char tests[TestsCounterForFind][256] = {
		"Not correct start position (lineIndex or charIndex)",
		"Not correct srtCount",
		"Haven\'t pos",
		"Don\'t stop count",
		"Forget initialize index",
		"Forget add indexes to array"
	};//������ �������� ��� ������
	const int strCounts[TestsCounterForFind] = { 1, 1, 2, 2, 1, 2};//���������� ����� � ������
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
	};//�����
	const int StartIndexes[TestsCounterForFind][2] = {
		{0, 1},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	};//������� ��� ������ ������
	const int RightBrackets[TestsCounterForFind][4] = {
		{0, 12, 0, 17}, 
		{0, 1, 0, 5}, 
		{0, 8, 1, 8}, 
		{0, 3, 0, 4},
		{0, 3, 0, 10},
		{0, 0, 1, 0}
	};//��������� ������

	bool Success;//��������� ���������� �����

	Success = true;//���������� �������, ��� ���� �������
	for (int i = 0; i < TestsCounterForFind; i++) {
		findPairBrackets(texts[i], strCounts[i], StartIndexes[i][0], StartIndexes[i][1], brackets);
		if (!CompareBrackets(brackets, RightBrackets[i]))
			printf("Incorrect test %d) in %s\n", i+1, tests[i]);
		Success = Success && CompareBrackets(brackets, RightBrackets[i]);
	}
	if (Success)
		printf("Tests passed for func findPairBrackets!\n");

	//������������ ��������� �����

	const int TestForString = 3;//���������� ������
	const char Description[TestForString][256] = {
		"Swap begin and end (haven\'t if-condition)",
		"More, than lehgt of string",
		"Bad memmove"
	};//�������� � �����
	char strings[TestForString][81] = {
		"rat rat rat",
		"fat fat fat fat",
		"move move"
	};//�������� ������
	const int Indexes[TestForString][2] = {
		{3, 0}, {0, 17}, {0, 5}
	};//������� ��� ��������� �����
	const char Answers[TestForString][81] = {
		" rat rat",
		"", 
		"move"
	};//��������� ������

	printf("\n");

	Success = true;//���������� �������, ��� ���� �������
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
	UnitTests();

	//�������� ������
	char text[20][81];
	int M;
	
	scanf("%d\n", &M);//��������� ������
	if (M < 1 || M > 20) {//���� �� ���������� ������
		printf("Invalid data\n");
		return 0;
	}

	for (int i = 0; i < M; i++) {//���� ������
		gets_s(text[i]);
		if (strlen(text[i]) > 81) {//���� �� ���������� ������
			printf("Invalid data\n");
			return 0;
		}
	}

	//������ �������� ��������
	int brackets[4] = {-1, -1, -1, -1};
	int StopLine, StopChar; //�����, � �������� �������� ����� ��������
	
	//�������������
	StopLine = 0; StopChar = 0;
	//�� ����, ��� ���� ������ ���������� ��������
	while (StopChar != -1) {

		//������������� ������� ��������
		for (int i = 0; i < 4; i++)
					brackets[i] = -1;
		findPairBrackets(text, M, StopLine, StopChar, brackets);

		if (brackets[2] != -1) {//���� �������� �������
			int StartLineForCut;//����� ��� ��������� ������

			StartLineForCut = brackets[0];
			if (StartLineForCut != brackets[2]) {//� ������ �������������� ���������
				//�������� ������ ������
				cutString(text[StartLineForCut], brackets[1], strlen(text[StartLineForCut]));
				++StartLineForCut;
				
				//�������� ������������ ����� �������� �� ���������
				while (StartLineForCut != brackets[2]) {
					cutString(text[StartLineForCut], 0, strlen(text[StartLineForCut]));
					strcpy(text[StartLineForCut], text[StartLineForCut + 1]);
					StartLineForCut++; M--;
				}

				//�������� ��������� ������
				StartLineForCut = brackets[0] + 1;
				cutString(text[StartLineForCut], 0, brackets[3] + 1);

				//���� ��������� ������ ������ - ������������� ��
				if (isspace(text[StartLineForCut][0])) { 
					strcpy(text[StartLineForCut], text[StartLineForCut + 1]);
					StartLineForCut++; M--; 
				}
			}
			else {
				//������������ ���������
				cutString(text[StartLineForCut], brackets[1], brackets[3] + 1);

				//���� ��������� ������ ������ - ������������� ��
				if (isspace(text[StartLineForCut][0])) {
					strcpy(text[StartLineForCut], text[StartLineForCut + 1]);
					StartLineForCut++; M--;
				}
			}
		}
		//�������� �������� �������
		StopLine = brackets[0]; StopChar = brackets[1];
	}
	//������ ������
	print(text, M);

	return 0;
}
