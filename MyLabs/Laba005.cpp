#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <conio.h>

/*
	������� ��� ��������� ������ � ������� ��� �������� ������� �� ������������
*/
void FindDuplicate(const int arr[], const int N, int** ptrEqualArr, int& colums, int& rows){
	
		bool ItWrite;//��������������� ���������� ��� ������������ ��������� � ����� �������
		bool CheckedElement;//���������� ��� �������� ���� ������� ����� ������������ � �����
		bool NotFoundDuplicate;//���������, ��� ���������� � ������� ��� ������
		int MaxColumns;//���������� ��� ���������� ������������� �������� ������� � �������, ����� ������������ ��� ��� ������

		//������������� �������� ��� ������ � ����
		ItWrite = false;
		CheckedElement = false;
		NotFoundDuplicate = true;
		MaxColumns = 0;
		colums = 0;
		rows = 0;

		//����� ���������� � �������
		for (int i = 0; i < N - 1; i++) {

			//����� ������ ����������� ����������
			for (int k = i - 1; k >= 0; k--) {
				if (arr[k] == arr[i])
					CheckedElement = true;
			}

			//���� ������� ����� �� �������������
			if (!CheckedElement) {
				for (int j = i + 1; j < N; j++) {
					//���� ������� ������ arr[i] ���� � �������
					//� �� �������������� �����
					if (arr[j] == arr[i] && !ItWrite) {
						//printf("%d %d ", i, j);
						//��������� ��������
						ptrEqualArr[rows][colums++] = i;
						ptrEqualArr[rows][colums++] = j;

						//����������, ��� ������� ����, � ������ �������� arr[i] ���� � �������
						NotFoundDuplicate = false;
						ItWrite = true;
					}
					//���� � �������� arr[i] ����� ���� �����
					else if (arr[j] == arr[i] && ItWrite) {
						ptrEqualArr[rows][colums++] = j;
					}
				}
			}

			//���� � �������� arr[i] ���� ����� � �� �� ��� ����� � �������
			if (ItWrite) {
				rows++;
				//��������� ���������� ������� ��� ����������� ������
				if (MaxColumns < colums) {
					MaxColumns = colums;
				}
				//�������� �������� �������
				colums = 0;
			}

			//����� �������� 
			ItWrite = false;
			CheckedElement = false;
		}
		colums = MaxColumns;

	//����� �� �������, ������� ���
	if (NotFoundDuplicate)
		ptrEqualArr[0][0] = -1001;

}

 /*
	������� ��� ������������ �������� � �������,
	�.�. �������� ��� �� "�������� ��������"
	int** arr - ��������� ������ ��� ������������
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
	������� ��� ������ ���������� �������
	int **arr - ��������� ������, ������� ����� �������
	int rows - ���������� ������� �������
	int columns - ���������� ������� � �������
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

	//����� �������� � ������, ���� ��� �������
	if (rows == 0 && columns == 0)
		printf("%d\n", arr[0][0]);
}

//void CompareArrays(int** CurrentArray, int** ResultArray) {
//	
//}

/*
	������� ������������ FindDuplicate()
*/
void UnitTests() {

	int** EqualArr;//��������� ������ ��� �������� ����������
	int colums, rows;//���������� ������� � ������� �������

	//������������� � ������������ �������
	EqualArr = new int*[20];
	for (int i = 0; i < 20; i++)
		EqualArr[i] = new int[20];
	NormalizeAnswer(EqualArr);

	//�������� ������ ������
	int check1[10] = { 89, 70, 89, 1000, 1000, 56, 78, 89, 34, 34 };
	int check2[5] = { 12, 1, 5, 6, 7};
	int check3[6] = { 1, 1, 2, 3, 4, 4};
	int check4[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int check5[5] = { 1, 1, 1, 1, 1};

	//���������� ������ �� �����
	int answer1[3][3] = {
		{0, 2, 7},
		{3, 4, 0},
		{8, 9, 0}
	};
	int NoSolusionAnswer = -1001;
	int answer2[2][2] = { {0, 1}, {4, 5} };
	int answer3[1][5] = { { 0, 1, 2, 3, 4} };
	
	//������������

	//���� ������
	FindDuplicate(check1, 10, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	bool IncorrectID = false;//���������� ��� �������� �� ����������� �����
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if (answer1[i][j] != EqualArr[i][j]) {//���� �������� �� ��������� � ���������
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	//��� ����������� ����� ������� ���������
	if (!IncorrectID)
		printf("Succuess!\n");
	
	//����� ������ ��� ����������� ������������
	NormalizeAnswer(EqualArr);
	printf("\n===========================================\n");
	
	//���� ������
	FindDuplicate(check2, 5, EqualArr, colums, rows);
	if (EqualArr[0][0] == NoSolusionAnswer)//���� �������� �� ��������� � ���������
		printf("Succuess! This test haven't solusion\n");
	//��� ����������� ����� ������� ���������
	else
		printf("Incorrect data. This test haven't solusion!\n");

	//����� ��������
	printf("\n===========================================\n");
	NormalizeAnswer(EqualArr);
	
	//���� ������
	FindDuplicate(check3, 6, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	IncorrectID = false;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (answer2[i][j] != EqualArr[i][j]) {//���� �������� �� ��������� � ���������
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	//��� ����������� ����� ������� ���������
	if (!IncorrectID)
		printf("Succuess!\n");
	
	//����� ��������
	printf("\n===========================================\n");
	NormalizeAnswer(EqualArr);
	
	//���� ���������
	FindDuplicate(check4, 9, EqualArr, colums, rows);
	if (EqualArr[0][0] == NoSolusionAnswer)//���� �������� �� ��������� � ���������
		printf("Succuess! This test haven't solusion\n");
	//��� ����������� ����� ������� ���������
	else
		printf("Incorrect data. This test haven't solustion!\n");

	printf("\n===========================================\n");
	NormalizeAnswer(EqualArr);

	//���� �����
	FindDuplicate(check5, 5, EqualArr, colums, rows);
	print(EqualArr, rows, colums);
	IncorrectID = false;
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 5; j++)
			if (answer3[i][j] != EqualArr[i][j]) {//���� �������� �� ��������� � ���������
				printf("Incorrect data in %d %d place\n", i, j);
				IncorrectID = true;
			}
	//��� ����������� ����� ������� ���������
	if (!IncorrectID)
		printf("Succuess!\n");

	//������� ������
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

	int** EqualArr;//��������� ������ ��� ������ �������� ����������
	int colums, rows;//������� � ������ ��� ������

	//������������� �������
	EqualArr = new int*[20];
	for (int i = 0; i < 20; i++)
		EqualArr[i] = new int[20];
	
	//����� ����������
	FindDuplicate(arr, N, EqualArr, colums, rows);
	if (EqualArr[0][0] == -1001) //����� � ������, ���� ���������� ���
		printf("no solustion!");
	//������� ���������
	else
		print(EqualArr, rows, colums);
	printf("\n\n");

	//������� ������
	for (int i = 0; i < 20; i++)
		delete[] EqualArr[i];
	delete[] EqualArr;

	UnitTests();
	
	return 0;
}