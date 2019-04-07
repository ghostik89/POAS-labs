#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <conio.h>

/*
	������� ��� ��������� ������ � ������� ��� �������� ������� �� ������������
*/
void FindEqual(const int arr[], const int N, int** ptrEqualArr, int& colums, int& rows){
	//bool CorrectData = true;
	////�������� N �� �������������� ��������� ���������
	//if (N > 20 || N < 2) {
	//	CorrectData = false;
	//}
	////�������� N �� �������������� ��������� ���������
	//if (N > 20 || N < 2) {
	//	CorrectData = false;
	//}

	////���������� �������
	//for (int i = 0; i < N; i++) {
	//	//�������� �������� �� �������������� ��������� ���������
	//	if (arr[i] < -1000 || arr[i] > 1000) {
	//		CorrectData = false;
	//	}
	//}

	////���������� �������
	//for (int i = 0; i < N; i++) {
	//	//�������� �������� �� �������������� ��������� ���������
	//	if (arr[i] < -1000 || arr[i] > 1000) {
	//		CorrectData = false;
	//	}
	//}

	//bool NotEqual = true;//���������, ��� ���������� � ������� ��� ������
	//if (CorrectData) {
		bool It_Write = false; //��������������� ���������� ��� ������ � ����� ������
		bool CheckedElement = false; //���������� ��� �������� ���� ������� ����� ������������ � �����
		bool NotEqual = true;//���������, ��� ���������� � ������� ��� ������
		int maxcolums = 0;

		colums = 0;
		rows = 0;
		for (int i = 0; i < N - 1; i++) {
			//����� ������
			for (int k = i - 1; k >= 0; k--) {
				if (arr[k] == arr[i])
					CheckedElement = true;
			}
			//���� ������� ����� �� �������������
			if (!CheckedElement) {
				for (int j = i + 1; j < N; j++) {
					//���� ������� arr[i] ��� ��������� �������
					//� �� �������������� �����
					if (arr[j] == arr[i] && !It_Write) {
						//printf("%d %d ", i, j);
						ptrEqualArr[rows][colums++] = i;
						ptrEqualArr[rows][colums++] = j;
						NotEqual = false;
						It_Write = true;
					}
					//���� � �������� arr[i] ����� ���� �����
					else if (arr[j] == arr[i] && It_Write) {
						//printf("%d ", j);
						ptrEqualArr[rows][colums++] = j;
					}
				}
			}

			//���� � �������� arr[i] ���� ����� � �� �� ��� ����� ���������
			if (It_Write) {
				rows++;
				//colums = 0;
				if (maxcolums < colums) {
					maxcolums = colums;
				}
				colums = 0;
			}
			//printf("\n");
			It_Write = false;//����� ���������� ������������� ��������
			CheckedElement = false;
		}
		colums = maxcolums;
	//}
	//����� �� �������, ������� ���
	if (NotEqual)
		ptrEqualArr[0][0] = -1001;

}

void NormalizeAnswer(int** arr) {
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			arr[i][j] = 0;
		}
	}
}
void print(int **M, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d\t", M[i][j]);
		}
		printf("\n");
	}
	if (rows == 0 && columns == 0)
		printf("%d\n", M[0][0]);
}

//void CompareArrays(int** CurrentArray, int** ResultArray) {
//	
//}

void CheckArray() {
	int** EqualArr;
	int colums, rows;
	EqualArr = new int*[20];
	for (int i = 0; i < 20; i++)
		EqualArr[i] = new int[20];
	NormalizeAnswer(EqualArr);
	int check1[10] = { 89, 70, 89, 1000, 1000, 56, 78, 89, 34, 34 };
	//int check2[21] = {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23};
	int check3[5] = { 12, 1, 5, 6, 7};
	//int check4[1] = { 12 };
	//int check5[5] = { 1001, 2001, 56, 56, 45};
	int check6[6] = { 1, 1, 2, 3, 4, 4};
	int check7[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int check8[5] = { 1, 1, 1, 1, 1};

	//��������� ������
	int answer1[3][3] = {
		{0, 2, 7},
		{3, 4, 0},
		{8, 9, 0}
	};
	int InvalidAnswer = -1001;
	int answer6[2][2] = { {0, 1}, {4, 5} };
	int answer8[1][5] = { { 0, 1, 2, 3, 4} };
	
	//������� � �������

	//test1
	FindEqual(check1, 10, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	bool IncorrectID = false;
	//CompareArrays(EqualArr, answer1);
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if (answer1[i][j] != EqualArr[i][j]) {
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	if (!IncorrectID)
		printf("Succuess!\n");
	
	NormalizeAnswer(EqualArr);
	IncorrectID = false;

	printf("===========================================\n");
	//test2
	FindEqual(check3, 5, EqualArr, colums, rows);
	if (EqualArr[0][0] == InvalidAnswer)
		printf("Succuess!\n");
	else
		printf("Incorrect data. This test haven't solustion!\n");

	printf("===========================================\n");
	NormalizeAnswer(EqualArr);
	
	//test3
	FindEqual(check6, 6, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	IncorrectID = false;
	//CompareArrays(EqualArr, answer1);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (answer6[i][j] != EqualArr[i][j]) {
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	if (!IncorrectID)
		printf("Succuess!\n");
	
	printf("===========================================\n");
	NormalizeAnswer(EqualArr);
	
	//test4
	FindEqual(check7, 9, EqualArr, colums, rows);
	if (EqualArr[0][0] == InvalidAnswer)
		printf("Succuess!\n");
	else
		printf("Incorrect data. This test haven't solustion!\n");

	printf("===========================================\n");
	NormalizeAnswer(EqualArr);

	//test 5
	FindEqual(check8, 5, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	IncorrectID = false;
	//CompareArrays(EqualArr, answer1);
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 5; j++)
			if (answer8[i][j] != EqualArr[i][j]) {
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	if (!IncorrectID)
		printf("Succuess!\n");

	for (int i = 0; i < 20; i++)
		delete[] EqualArr[i];
	delete[] EqualArr;
}



int main() {
	//�������� ������ �������� �������
	int arr[20], N;
	scanf("%d", &N);



	//�������� N �� �������������� ��������� ���������
	if (N > 20 || N < 2) {
		printf("Invalid data\n");
		return 0;
	}

	//���������� �������
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		//�������� �������� �� �������������� ��������� ���������
		if (arr[i] < -1000 || arr[i] > 1000) {
			printf("Invalid data\n");
			return 0;
		}
	}
	int** EqualArr;
	int colums, rows;
	EqualArr = new int*[20];
	for (int i = 0; i < 20; i++)
		EqualArr[i] = new int[20];

	//��������� ������ ����������
	FindEqual(arr, N, EqualArr, colums, rows);
	if (EqualArr[0][0] == -1001)
		printf("no solustion!");
	else
		print(EqualArr, rows, colums);
	CheckArray();
	
	for (int i = 0; i < 20; i++)
		delete[] EqualArr[i];
	delete[] EqualArr;
	
	return 0;
}