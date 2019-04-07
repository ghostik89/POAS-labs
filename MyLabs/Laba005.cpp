#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <conio.h>

/*
	Функция для выявления дублей в массиве без проверки массива на корректность
*/
void FindDuplicate(const int arr[], const int N, int** ptrEqualArr, int& colums, int& rows){
	
		bool ItWrite;//вспомогательная переменная для расположения элементов в одной строчке
		bool CheckedElement;//переменная для проверки были элемент ранее задействован в цикле
		bool NotFoundDuplicate;//считается, что изначально в массиве нет дублей
		int MaxColumns;//необходимо для нахождения максимального значения колонок в массиве, чтобы использовать это при печати

		//Инициализация значений для работы с ними
		ItWrite = false;
		CheckedElement = false;
		NotFoundDuplicate = true;
		MaxColumns = 0;
		colums = 0;
		rows = 0;

		//поиск дубликатов в массиве
		for (int i = 0; i < N - 1; i++) {

			//поиск раннее проверенной переменной
			for (int k = i - 1; k >= 0; k--) {
				if (arr[k] == arr[i])
					CheckedElement = true;
			}

			//если элемент ранее не использовался
			if (!CheckedElement) {
				for (int j = i + 1; j < N; j++) {
					//если элемент индекс arr[i] нету в массиве
					//и не рассматривался ранее
					if (arr[j] == arr[i] && !ItWrite) {
						//printf("%d %d ", i, j);
						//присовить значения
						ptrEqualArr[rows][colums++] = i;
						ptrEqualArr[rows][colums++] = j;

						//обозначить, что решения есть, и индекс элемента arr[i] есть в массиве
						NotFoundDuplicate = false;
						ItWrite = true;
					}
					//если у элемента arr[i] ранее были дубли
					else if (arr[j] == arr[i] && ItWrite) {
						ptrEqualArr[rows][colums++] = j;
					}
				}
			}

			//если у элемента arr[i] были дубли и он не был ранее в массиве
			if (ItWrite) {
				rows++;
				//сохранить количество колонок для последующей печати
				if (MaxColumns < colums) {
					MaxColumns = colums;
				}
				//сбросить значение колонок
				colums = 0;
			}

			//сброс значений 
			ItWrite = false;
			CheckedElement = false;
		}
		colums = MaxColumns;

	//дубли не найдены, решения нет
	if (NotFoundDuplicate)
		ptrEqualArr[0][0] = -1001;

}

 /*
	функция для нормализации значений в массиве,
	т.е. избавить его от "мусорных значений"
	int** arr - двумерный массив для нормализации
 */
void NormalizeAnswer(int** arr) {
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			arr[i][j] = 0;
		}
	}
}

/*
	Функция для вывода двумерного массива
	int **arr - двумерный массив, который нужно вывести
	int rows - количество строчек массива
	int columns - количество колонок в массиве
*/
void print(int **arr, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}

	//вывод значения в случае, если нет решения
	if (rows == 0 && columns == 0)
		printf("%d\n", arr[0][0]);
}

//void CompareArrays(int** CurrentArray, int** ResultArray) {
//	
//}

/*
	функция тестирования FindDuplicate()
*/
void UnitTests() {

	int** EqualArr;//двумерный массив для хранения дубликатов
	int colums, rows;//количество колонок и строчек массива

	//инициализация и нормализация массива
	EqualArr = new int*[20];
	for (int i = 0; i < 20; i++)
		EqualArr[i] = new int[20];
	NormalizeAnswer(EqualArr);

	//исходные данные тестов
	int check1[10] = { 89, 70, 89, 1000, 1000, 56, 78, 89, 34, 34 };
	int check2[5] = { 12, 1, 5, 6, 7};
	int check3[6] = { 1, 1, 2, 3, 4, 4};
	int check4[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int check5[5] = { 1, 1, 1, 1, 1};

	//правильные ответы на тесты
	int answer1[3][3] = {
		{0, 2, 7},
		{3, 4, 0},
		{8, 9, 0}
	};
	int NoSolusionAnswer = -1001;
	int answer2[2][2] = { {0, 1}, {4, 5} };
	int answer3[1][5] = { { 0, 1, 2, 3, 4} };
	
	//тестирование

	//тест первый
	FindDuplicate(check1, 10, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	bool IncorrectID = false;//переменная для проверки на прохождение теста
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if (answer1[i][j] != EqualArr[i][j]) {//если элементы не совпадают с эталонным
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	//при прохождении теста вывести сообщение
	if (!IncorrectID)
		printf("Succuess!\n");
	
	//сброс данных для дальнейшего тестирования
	NormalizeAnswer(EqualArr);
	printf("\n===========================================\n");
	
	//тест второй
	FindDuplicate(check2, 5, EqualArr, colums, rows);
	if (EqualArr[0][0] == NoSolusionAnswer)//если элементы не совпадают с эталонным
		printf("Succuess! This test haven't solusion\n");
	//при прохождении теста вывести сообщение
	else
		printf("Incorrect data. This test haven't solusion!\n");

	//сброс значений
	printf("\n===========================================\n");
	NormalizeAnswer(EqualArr);
	
	//тест третий
	FindDuplicate(check3, 6, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	IncorrectID = false;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (answer2[i][j] != EqualArr[i][j]) {//если элементы не совпадают с эталонным
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	//при прохождении теста вывести сообщение
	if (!IncorrectID)
		printf("Succuess!\n");
	
	//сброс значений
	printf("\n===========================================\n");
	NormalizeAnswer(EqualArr);
	
	//тест четвертый
	FindDuplicate(check4, 9, EqualArr, colums, rows);
	if (EqualArr[0][0] == NoSolusionAnswer)//если элементы не совпадают с эталонным
		printf("Succuess! This test haven't solusion\n");
	//при прохождении теста вывести сообщение
	else
		printf("Incorrect data. This test haven't solustion!\n");

	printf("\n===========================================\n");
	NormalizeAnswer(EqualArr);

	//тест пятый
	FindDuplicate(check5, 5, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	IncorrectID = false;
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 5; j++)
			if (answer3[i][j] != EqualArr[i][j]) {//если элементы не совпадают с эталонным
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	//при прохождении теста вывести сообщение
	if (!IncorrectID)
		printf("Succuess!\n");

	//удалить массив
	for (int i = 0; i < 20; i++)
		delete[] EqualArr[i];
	delete[] EqualArr;
}



int main() {
	//исходные данные согласно условию
	int arr[20], N;
	scanf("%d", &N);



	//проверка N на принадлежность заданному диапозону
	if (N > 20 || N < 2) {
		printf("Invalid data\n");
		return 0;
	}

	//считывание массива
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		//проверка элемента на принадлежность заданному диапозону
		if (arr[i] < -1000 || arr[i] > 1000) {
			printf("Invalid data\n");
			return 0;
		}
	}

	int** EqualArr;//двумерный массив для записи индексов дубликатов
	int colums, rows;//колонки и строки для вывода

	//инициализация массива
	EqualArr = new int*[20];
	for (int i = 0; i < 20; i++)
		EqualArr[i] = new int[20];
	
	//поиск дубликатов
	FindDuplicate(arr, N, EqualArr, colums, rows);
	if (EqualArr[0][0] == -1001) //вывод в случае, если дубликатов нет
		printf("no solustion!");
	//вывести дубликаты
	else
		print(EqualArr, rows, colums);
	printf("\n\n");

	//удалить массив
	for (int i = 0; i < 20; i++)
		delete[] EqualArr[i];
	delete[] EqualArr;

	UnitTests();
	
	return 0;
}