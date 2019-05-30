// Lab_Tarapatina.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//#include "str_unit.h"
//#include "testing.h"
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <ctype.h>


/*
	str � �������� ������
	beginPos, endPos � ��������� � �������� ������� ���������, ������� ���������� ��������
*/ 
void cutString(char str[81], int beginPos, int endPos) {
	int StokLen = strlen(str);// ����� ������
	
	int DeleteLen = endPos - beginPos + 1;//���������� ��������, ������� ���� �������

	if (endPos < beginPos)//���� ������� ����������
		DeleteLen = beginPos - endPos + 1;

	if (beginPos + DeleteLen > StokLen) //���� ��������� ����� �������� �������� �� ����� ������
		DeleteLen = StokLen - beginPos + 1;

	if (endPos < beginPos) //�������� ��� ������������ �������� ������ � �����
		memmove(str + endPos, str + endPos + DeleteLen, StokLen - DeleteLen + 1);
	else
		memmove(str + beginPos, str + beginPos + DeleteLen, StokLen - DeleteLen + 1);//������� ��������
}
/*
	text � �������� �����
	strCount � ���-�� ����� ������
	lineIndex, characterIndex � ��������� ������� ������ (������ ������, ������ ������� � ������)
	
	bra�kets � ������� ���� ������;���� ���� ������ �� ����������, �� ��� ������� ����� -1
*/
void findPairBrackets (const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	
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

	for (int i = 0; i < 4; i++)
		brackets[i] = -1;


	for (int i = lineIndex; i < strCount && !(EndCount); i++) {
		char tempstring[81];//��������� ������ ��� ������ ��������
		strcpy(tempstring, text[i]);

		//������������� �������
		TotalPosition = 0; TempIndexOfBrackets = 0;
		if (characterIndex != 0 && i == lineIndex) {//���� ��������� ������� ������
			TotalPosition = characterIndex;
			cutString(tempstring, 0, TotalPosition - 1);//������ �������� ������
		}

		//���� ����, ��� ������
		while (strcspn(tempstring, "()") != strlen(tempstring)) {
			
			TotalPosition += TempIndexOfBrackets;//��������� �������� �� ������
			TempIndexOfBrackets = strcspn(tempstring, "()");//���� ��������� ������
			char NowBracket;//������� ������
			NowBracket = tempstring[TempIndexOfBrackets];

			cutString(tempstring, 0, TempIndexOfBrackets);//������ �������� ������
			
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
	if ((EndCount || CountBrackets >= 0)  && (LastRightBracketLine != -1 && LastRightBracketChar != -1)) {
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
	const int TestsCounterForFind = 3;
	
	//������������ ������ ������
	int brackets[4];//������ ��� ������ ������
	//const char tests[TestsCounterForFind][256] = {
	//	"Not correct start position (lineIndex or charIndex)",
	//	"Not correct srtCount",
	//	"Haven\'t pos",
	//	"Don\'t stop count",
	//	"Forget initialize index",
	//	"Forget add indexes to array"
	//};//������ �������� ��� ������Z
	const int strCounts[TestsCounterForFind] = { 0, 2, 3};//���������� ����� � ������
	const char texts[TestsCounterForFind][3][81] = {
		{
			""
		}, 
		{
			"menya eto vse",
			"ochen( silno) ogorchaet"
		}, 
		{
			"",
			"menya eto (vse",
			"ochen silno) ogorchaet"
		}, 
	};//�����
	const int StartIndexes[TestsCounterForFind][2] = {
		{0, 0},
		{0, 0},
		{1, 5},
	};//������� ��� ������ ������
	const int RightBrackets[TestsCounterForFind][4] = {
		{-1, -1, -1, -1}, 
		{1, 5, 1, 12}, 
		{1, 10, 2, 11}, 
	};//��������� ������

	bool Success;//��������� ���������� �����

	Success = true;//���������� �������, ��� ���� �������
	for (int i = 0; i < TestsCounterForFind; i++) {
		findPairBrackets(texts[i], strCounts[i], StartIndexes[i][0], StartIndexes[i][1], brackets);
		if (!CompareBrackets(brackets, RightBrackets[i]))
			printf("Incorrect test %d)\n", i+1);
		Success = Success && CompareBrackets(brackets, RightBrackets[i]);
	}
	if (Success)
		printf("Tests passed for func findPairBrackets!\n");

	//������������ ��������� �����

	const int TestForString = 6;//���������� ������
	//const char Description[TestForString][256] = {
	//	"",
	//	"kaznit nelza pomilovat",
	//	"Bad memmove"
	//};//�������� � �����
	char strings[TestForString][81] = {
		"",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat"
	};//�������� ������
	const int Indexes[TestForString][2] = {
		{0, 0}, 
		{3, 3}, 
		{0, 21},
		{7, 12},
		{0, 6},
		{13, 21}
	};//������� ��� ��������� �����
	const char Answers[TestForString][81] = {
		"",
		"kazit nelza pomilovat", 
		"",
		"kaznit pomilovat",
		"nelza pomilovat",
		"kaznit nelza "
	};//��������� ������

	printf("\n");

	Success = true;//���������� �������, ��� ���� �������
	for (int i = 0; i < TestForString; i++) {
		cutString(strings[i], Indexes[i][0], Indexes[i][1]);
		if (strcmp(strings[i], Answers[i]))
			printf("Incorrect test %d)\n", i+1);
		Success = Success && !strcmp(strings[i], Answers[i]);
	}
	if (Success)
		printf("Tests passed for func cutString!\n");
}

int main(){
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
	int brackets[4];
	int StopLine, StopChar; //�����, � �������� �������� ����� ��������
	
	//�������������
	StopLine = 0; StopChar = 0;
	//�� ����, ��� ���� ������ ���������� ��������
	while (StopChar != -1) {

		//������������� ������� ��������
		//for (int i = 0; i < 4; i++)
		//			brackets[i] = -1;
		findPairBrackets(text, M, StopLine, StopChar, brackets);

		if (brackets[2] != -1) {//���� �������� �������
			int StartLineForCut;//����� ��� ��������� ������

			StartLineForCut = brackets[0];
			if (StartLineForCut != brackets[2]) {//� ������ �������������� ���������
				//�������� ������ ������
				cutString(text[StartLineForCut], brackets[1], strlen(text[StartLineForCut]) - 1);
				++StartLineForCut;
				
				//�������� ������������ ����� �������� �� ���������
				while (StartLineForCut != brackets[2]) {
					cutString(text[StartLineForCut], 0, strlen(text[StartLineForCut]) - 1);
					StartLineForCut++;
				}

				//�������� ��������� ������
				StartLineForCut = brackets[2];
				cutString(text[StartLineForCut], 0, brackets[3]);

				//���� ��������� ������ ������ - ������������� ��
				if (isspace(text[StartLineForCut][0])) { 
					strcpy(text[StartLineForCut], text[StartLineForCut + 1]);
					StartLineForCut++; M--; 
				}
			}
			else {
				//������������ ���������
				cutString(text[StartLineForCut], brackets[1], brackets[3]);
			}
		}
		//�������� �������� �������
		StopLine = brackets[0]; StopChar = brackets[1];
	}
	//������ ������
	print(text, M);
	
	return 0;
}

