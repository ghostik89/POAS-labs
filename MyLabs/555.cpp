// 555.cpp : Defines the entry point for the console application.
//
// Lab_05_tarapatina.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

/*
	Функция для выявления дублей в массиве
	const int arr[] - исходный массив, в котором происходит поиск
	int N - количество элементов в массиве
	int EqualArr[][20] - массив, в который записываются индексы дублей
	int ArrColumns[20] - количество колонок в строках EqualArr[][20]
*/
void FindDuplicate(const int arr[], int N, int EqualArr[][20], int ArrColumns[20]){
	
		bool ItWrite;//вспомогательная переменная для расположения элементов в одной строчке
		bool CheckedElement;//переменная для проверки были элемент ранее задействован в цикле
		bool NotFoundDuplicate;//считается, что изначально в массиве нет дублей
		//int MaxColumns;//необходимо для нахождения максимального значения колонок в массиве, чтобы использовать это при печати

		//Инициализация значений для работы с ними
		ItWrite = false;
		CheckedElement = false;
		NotFoundDuplicate = true;
		int colums = 0;
		int rows = 0;

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
						EqualArr[rows][colums++] = i;
						EqualArr[rows][colums++] = j;

						//обозначить, что решения есть, и индекс элемента arr[i] есть в массиве
						NotFoundDuplicate = false;
						ItWrite = true;
					}
					//если у элемента arr[i] ранее были дубли
					else if (arr[j] == arr[i] && ItWrite) {
						EqualArr[rows][colums++] = j;
					}
				}
			}
			ArrColumns[rows] = colums;
			//если у элемента arr[i] были дубли и он не был ранее в массиве
			if (ItWrite)
				rows++;
				//сбросить значение колонок
				colums = 0;
		}

			//сброс значений 
			ItWrite = false;
			CheckedElement = false;

	//дубли не найдены, решения нет
	if (NotFoundDuplicate)
		EqualArr[0][0] = -1001;

}

 /*
	функция для заполения незначащими элементами в массиве,
	т.е. избавить его от "мусорных значений"
	int arr[][20] - двумерный массив для нормализации
 */
void NormalizeAnswer(int arr[][20]) {
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			arr[i][j] = -1;
}

/*
	Функция для вывода двумерного массива
	int arr[][20] - двумерный массив, который нужно вывести
	int ArrColumns[20] - количество колонок в каждой строке массива
*/
void print(int arr[][20], int ArrColumns[20]){
	
	//основной вывод
	for (int i = 0; ArrColumns[i] != 0; i++){
		for (int j = 0; j < ArrColumns[i]; j++)
			printf("%d\t", arr[i][j]);
		printf("\n");
	}

	//вывод значения в случае, если нет решения
	if (ArrColumns[0] == 0)
		printf("%d\n", arr[0][0]);
}

/*
	Функция сравнения двух массивов
	int CurrentArray[][5] - массив, который нужно сравнить с эталонным
	int ResultArray[][20] - эталонный массив
	int ArrColumns[20] - количество колонок в каждой строке
*/
bool CompareArrays(int CurrentArray[][5], int ResultArray[][20], int ArrColumns[20]) {
	bool AllIsEqual = false;//переменная для проверки индентичности всех элементов

	for (int i = 0; ArrColumns[i] != 0 ; i++)
		for (int j = 0; j < ArrColumns[i]; j++)
			if (ResultArray[i][j] != CurrentArray[i][j]) {//если элементы не совпадают с эталонным
				printf("Incorrect data in %d %d place\n", i, j);
				AllIsEqual = true;
			}
	return !AllIsEqual;
}

/*
	функция тестирования FindDuplicate()
	int EqualArr[][20] - тестируемый массив
	int ArrColumns[20] - количество колонок в каждой его строке
*/
void UnitTests(int EqualArr[][20], int ArrColumns[20]) {
	
	const int TestCounter = 5;//количество тестов

	const int LengthOfTests[TestCounter] = {10 , 5, 6, 9, 5};//длина массивов-начальных условий

	const char TestsDiscription[TestCounter][256] = {
		{"Right mixed test\0"},
		{"No solusion test\0"},
		{"Duplicates on the left and right\0"},
		{"No solusion test\0"},
		{"All array is full of duplicates\0"}
	}; //описание каждого теста

	bool Secuess;//переменная, определяющая прохождение всх тестов

	int Tests[TestCounter][10] = {
		{89, 70, 89, 1000, 1000, 56, 78, 89, 34, 34},
		{ 12, 1, 5, 6, 7},
		{ 1, 1, 2, 3, 4, 4},
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9},
		{ 1, 1, 1, 1, 1}
	};//исходные условия тестов

	int Answers[TestCounter][3][5] = {
		{
			{0, 2, 7, -1, -1},
			{3, 4, -1, -1, -1},
			{8, 9, -1, -1, -1}
		},
		{
			{-1001, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1}
		},
		{
			{0, 1, -1, -1, -1}, 
			{4, 5, -1, -1, -1},
			{-1, -1, -1, -1, -1}
		},
		{
			{-1001, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1}
		},
		{
			{ 0, 1, 2, 3, 4},
			{-1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1}
		}
	};//ответы на тесты

	Secuess = true;//изначально считается, что тест пройден
	for(int i = 0; i < TestCounter; i++){
		NormalizeAnswer(EqualArr);
		//поиск дубликатов
		FindDuplicate(Tests[i], LengthOfTests[i], EqualArr, ArrColumns);
		if (!CompareArrays(Answers[i], EqualArr, ArrColumns)) {
			printf("Incorrect %d) %s \n", i + 1, TestsDiscription[i]);
		}

		Secuess = Secuess && (CompareArrays(Answers[i], EqualArr, ArrColumns));
	}

	if(Secuess)
		printf("Tets passed\n");
}


int main(){
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

	int EqualArr[20][20];//двумерный массив для записи индексов дубликатов
	int colums, rows;//колонки и строки для вывода
	int ArrColumns[20] = {0};

	NormalizeAnswer(EqualArr);
	//поиск дубликатов
	FindDuplicate(arr, N, EqualArr, ArrColumns);
	if (EqualArr[0][0] == -1001) //вывод в случае, если дубликатов нет
		printf("no solustion!");
	//вывести дубликаты
	else
		print(EqualArr, ArrColumns);
	printf("\n\n");

	UnitTests(EqualArr, ArrColumns);
	
	

	return 0;
}


