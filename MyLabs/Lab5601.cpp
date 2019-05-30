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
	str – исходная строка
	beginPos, endPos – начальная и конечная позиции подстроки, которую необходимо вырезать
*/ 
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
/*
	text – исходный текст
	strCount – кол-во строк текста
	lineIndex, characterIndex – начальная позиция поиска (индекс строки, индекс символа в строке)
	
	braсkets – индексы пары скобок;если пара скобок не обнаружена, то все индексы равны -1
*/
void findPairBrackets (const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	
	bool IsFirstLeftBracket;//индикатор первой левой скобки
	int FirstLeftBracketLine, FirstLeftBracketChar, LastRightBracketLine, LastRightBracketChar;//координаты крайних скобок
	int TempIndexOfBrackets;//временный индекс нахождения скобки
	int CountBrackets; //для проверки на верную скобчатую последовательность
	bool EndCount;//конец подсчета скобочек
	int TotalPosition;//поправка позиции

	//инициализация переменных
	CountBrackets = 0;
	EndCount = false;
	IsFirstLeftBracket = false;
	FirstLeftBracketLine = -1; FirstLeftBracketChar = -1;
	LastRightBracketLine = -1;LastRightBracketChar = -1;

	for (int i = 0; i < 4; i++)
		brackets[i] = -1;


	for (int i = lineIndex; i < strCount && !(EndCount); i++) {
		char tempstring[81];//временная строка для поиска скобочек
		strcpy(tempstring, text[i]);

		//инициализация позиций
		TotalPosition = 0; TempIndexOfBrackets = 0;
		if (characterIndex != 0 && i == lineIndex) {//если отправная позиция задана
			TotalPosition = characterIndex;
			cutString(tempstring, 0, TotalPosition - 1);//сужаем диапозон поиска
		}

		//пока есть, где искать
		while (strcspn(tempstring, "()") != strlen(tempstring)) {
			
			TotalPosition += TempIndexOfBrackets;//обновляем поправку на позцию
			TempIndexOfBrackets = strcspn(tempstring, "()");//ищем очередную скобку
			char NowBracket;//текущая скобка
			NowBracket = tempstring[TempIndexOfBrackets];

			cutString(tempstring, 0, TempIndexOfBrackets);//сужаем диапозон поиска
			
			//сценарий для различных скобок
			switch (NowBracket) {
			case '(':

				CountBrackets++;//обновить счетчик правильной скобчатой последовательности

				if (!IsFirstLeftBracket) {//если мы встречаем левую скобку
					FirstLeftBracketLine = i;
					FirstLeftBracketChar = TempIndexOfBrackets + TotalPosition;
					IsFirstLeftBracket = true;
				}

				//если уже обнаружена правильная скобчатая последовательность
				//вместе с лишними скобками
				if (!EndCount && LastRightBracketLine != -1 && CountBrackets > 0)
					EndCount = true;
				
				break;
			case ')':

				CountBrackets--;
				
				//если мы встречаем правую скобку
				if (CountBrackets >= 0 && !EndCount) {
					LastRightBracketLine = i;
					LastRightBracketChar = TotalPosition + TempIndexOfBrackets;
					//случай, когда скобки стоят впритык друг к другу
					if ((LastRightBracketChar == FirstLeftBracketChar || TotalPosition == 0) && (FirstLeftBracketLine == LastRightBracketLine)) 
						LastRightBracketChar++;
					//правильная скобчатая последовательность найдена
					if(CountBrackets == 0)
						EndCount = true;
				}
				//если скобчатая последовательность изначально неправильная
				if (CountBrackets < 0 && !EndCount) {
					FirstLeftBracketLine = -1;
					FirstLeftBracketChar = -1;
					IsFirstLeftBracket = false;
					CountBrackets = 0;
				}
				break;
			}
			TempIndexOfBrackets++;//обновить временный индекс
		}
	}

	//если парные правильно расставленные скобки найдены
	if ((EndCount || CountBrackets >= 0)  && (LastRightBracketLine != -1 && LastRightBracketChar != -1)) {
		brackets[0] = FirstLeftBracketLine;
		brackets[1] = FirstLeftBracketChar;
		brackets[2] = LastRightBracketLine;
		brackets[3] = LastRightBracketChar;
	}
}

/*
	функция печати текста
	const char text[20][81] - текст для печати
	M - кол-во сток
*/
void print(const char text[20][81], int M) {
	for (int i = 0; i < M; i++) {
		//пропустить пустую строку
		if (strlen(text[i]) == 0)
			continue;
		puts(text[i]); printf("\n");
	}
}

/*
	функция сравнения массива скобок
*/
bool CompareBrackets(const int Current[4], const int Result[4]) {
	for (int i = 0; i < 4; i++)
		if (Current[i] != Result[i])
			return false;
	return true;
}

//юнит тесты
void UnitTests() {
	const int TestsCounterForFind = 3;
	
	//тестирование поиска скобок
	int brackets[4];//массив для записи скобок
	//const char tests[TestsCounterForFind][256] = {
	//	"Not correct start position (lineIndex or charIndex)",
	//	"Not correct srtCount",
	//	"Haven\'t pos",
	//	"Don\'t stop count",
	//	"Forget initialize index",
	//	"Forget add indexes to array"
	//};//массив описаний для тестовZ
	const int strCounts[TestsCounterForFind] = { 0, 2, 3};//количество строк в тексте
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
	};//тесты
	const int StartIndexes[TestsCounterForFind][2] = {
		{0, 0},
		{0, 0},
		{1, 5},
	};//индексы для начала обхода
	const int RightBrackets[TestsCounterForFind][4] = {
		{-1, -1, -1, -1}, 
		{1, 5, 1, 12}, 
		{1, 10, 2, 11}, 
	};//эталонные ответы

	bool Success;//индикатор успешности теста

	Success = true;//изначально считаем, что тест пройден
	for (int i = 0; i < TestsCounterForFind; i++) {
		findPairBrackets(texts[i], strCounts[i], StartIndexes[i][0], StartIndexes[i][1], brackets);
		if (!CompareBrackets(brackets, RightBrackets[i]))
			printf("Incorrect test %d)\n", i+1);
		Success = Success && CompareBrackets(brackets, RightBrackets[i]);
	}
	if (Success)
		printf("Tests passed for func findPairBrackets!\n");

	//тестирование обрезание строк

	const int TestForString = 6;//количество тестов
	//const char Description[TestForString][256] = {
	//	"",
	//	"kaznit nelza pomilovat",
	//	"Bad memmove"
	//};//описания к тесту
	char strings[TestForString][81] = {
		"",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat",
		"kaznit nelza pomilovat"
	};//тестовые строки
	const int Indexes[TestForString][2] = {
		{0, 0}, 
		{3, 3}, 
		{0, 21},
		{7, 12},
		{0, 6},
		{13, 21}
	};//индексы для обрезания строк
	const char Answers[TestForString][81] = {
		"",
		"kazit nelza pomilovat", 
		"",
		"kaznit pomilovat",
		"nelza pomilovat",
		"kaznit nelza "
	};//эталонные ответы

	printf("\n");

	Success = true;//изначально считаем, что тест пройден
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

	//исходные данные
	char text[20][81];
	int M;
	
	scanf("%d\n", &M);//считываем данные
	if (M < 1 || M > 20) {//тест на корректные данные
		printf("Invalid data\n");
		return 0;
	}

	for (int i = 0; i < M; i++) {//ввод текста
		gets_s(text[i]);
		if (strlen(text[i]) > 81) {//тест на корректные данные
			printf("Invalid data\n");
			return 0;
		}
	}

	//массив индексов скобочек
	int brackets[4];
	int StopLine, StopChar; //место, с которого начнется поиск скобочек
	
	//инициализация
	StopLine = 0; StopChar = 0;
	//до того, как есть парные правильные скобочки
	while (StopChar != -1) {

		//инициализация массива скобочек
		//for (int i = 0; i < 4; i++)
		//			brackets[i] = -1;
		findPairBrackets(text, M, StopLine, StopChar, brackets);

		if (brackets[2] != -1) {//если скобочки найдены
			int StartLineForCut;//старт для обрезания строки

			StartLineForCut = brackets[0];
			if (StartLineForCut != brackets[2]) {//в случае многострочного обрезания
				//обрезаем первую строку
				cutString(text[StartLineForCut], brackets[1], strlen(text[StartLineForCut]) - 1);
				++StartLineForCut;
				
				//обрезаем пространство между строками по вертикали
				while (StartLineForCut != brackets[2]) {
					cutString(text[StartLineForCut], 0, strlen(text[StartLineForCut]) - 1);
					StartLineForCut++;
				}

				//обрезаем последнюю строку
				StartLineForCut = brackets[2];
				cutString(text[StartLineForCut], 0, brackets[3]);

				//если последняя строка пустая - утрамбовываем ее
				if (isspace(text[StartLineForCut][0])) { 
					strcpy(text[StartLineForCut], text[StartLineForCut + 1]);
					StartLineForCut++; M--; 
				}
			}
			else {
				//однострочное обрезание
				cutString(text[StartLineForCut], brackets[1], brackets[3]);
			}
		}
		//обновить конечные позиции
		StopLine = brackets[0]; StopChar = brackets[1];
	}
	//печать текста
	print(text, M);
	
	return 0;
}

