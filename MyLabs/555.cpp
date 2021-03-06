// 555.cpp : Defines the entry point for the console application.
//
// Lab_05_tarapatina.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

/*
	������� ��� ��������� ������ � �������
	const int arr[] - �������� ������, � ������� ���������� �����
	int N - ���������� ��������� � �������
	int EqualArr[][20] - ������, � ������� ������������ ������� ������
	int ArrColumns[20] - ���������� ������� � ������� EqualArr[][20]
*/
void FindDuplicate(const int arr[], int N, int EqualArr[][20], int ArrColumns[20]){
	
		bool ItWrite;//��������������� ���������� ��� ������������ ��������� � ����� �������
		bool CheckedElement;//���������� ��� �������� ���� ������� ����� ������������ � �����
		bool NotFoundDuplicate;//���������, ��� ���������� � ������� ��� ������

		//������������� �������� ��� ������ � ����
		ItWrite = false;//����� ����� ����������
		CheckedElement = false;
		NotFoundDuplicate = true;
		int colums = 0;
		int rows = 0;

		//����� ���������� � �������
		for (int i = 0; i < N - 1; i++) {

			//����� ������ ����������� ����������
			CheckedElement = false;
			for (int k = i - 1; k >= 0; k--) {
				if (arr[k] == arr[i])
					CheckedElement = true;
			}

			//���� ������� ����� �� �������������
			if (!CheckedElement) {//� �����
				for (int j = i + 1; j < N; j++) {
					//���� ������� ������ arr[i] ���� � �������
					//� �� �������������� �����
					if (arr[j] == arr[i] && !ItWrite) {
						//��������� ��������
						EqualArr[rows][colums++] = i;
						EqualArr[rows][colums++] = j;

						//����������, ��� ������� ����, � ������ �������� arr[i] ���� � �������
						NotFoundDuplicate = false;
						ItWrite = true;
					}
					//���� � �������� arr[i] ����� ���� �����
					else if (arr[j] == arr[i] && ItWrite) { //� ���
						EqualArr[rows][colums++] = j;
					}
				}
			}
			ArrColumns[rows] = colums;
			//�������� �������� �������
			colums = 0;
			//���� � �������� arr[i] ���� ����� � �� �� ��� ����� � �������
			if (ItWrite)
				rows++;
			ItWrite = false;
		}

	//����� �� �������, ������� ���
	if (NotFoundDuplicate)
		EqualArr[0][0] = -1001;

}

 /*
	������� ��� ��������� ����������� ���������� � �������,
	�.�. �������� ��� �� "�������� ��������"
	int arr[][20] - ��������� ������ ��� ������������
 */
void NormalizeAnswer(int arr[][20]) {
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			arr[i][j] = -1;
}

/*
	������� ��� ������ ���������� �������
	int arr[][20] - ��������� ������, ������� ����� �������
	int ArrColumns[20] - ���������� ������� � ������ ������ �������
*/
void print(int arr[][20], int ArrColumns[20]){
	
	//�������� �����
	for (int i = 0; ArrColumns[i] != 0; i++){
		for (int j = 0; j < ArrColumns[i]; j++)
			printf("%d\t", arr[i][j]);
		printf("\n");
	}

	//����� �������� � ������, ���� ��� �������
	if (ArrColumns[0] == 0)
		printf("%d\n", arr[0][0]);
}

/*
	������� ��������� ���� ��������
	int CurrentArray[][5] - ������, ������� ����� �������� � ���������
	int ResultArray[][20] - ��������� ������
	int ArrColumns[20] - ���������� ������� � ������ ������
*/
bool CompareArrays(int CurrentArray[][7], int ResultArray[][20], int ArrColumns[5]) {
	bool AllIsEqual = false;//���������� ��� �������� ������������� ���� ���������

	for (int i = 0; ArrColumns[i] != 0 ; i++)
		for (int j = 0; j < ArrColumns[i]; j++)
			if (ResultArray[i][j] != CurrentArray[i][j]) {//���� �������� �� ��������� � ���������
				AllIsEqual = true;
			}

	//� ������ ���� ������ �� ����� �������
	if (ArrColumns[0] == 0 && CurrentArray[0][0] != ResultArray[0][0])
		AllIsEqual = true;

	return !AllIsEqual;
}

/*
	������� ������������ FindDuplicate()
	int EqualArr[][20] - ����������� ������
	int ArrColumns[20] - ���������� ������� � ������ ��� ������
*/
void UnitTests() {

	int EqualArr[20][20];//��������� ������ ��� ������ �������� ����������
	int ArrColumns[20] = { 0 };//����� ������ � EqualArr 

	const int TestCounter = 6;//���������� ������

	const int LengthOfTests[TestCounter] = {4, 5, 6, 5, 7, 5};//����� ��������-��������� �������

	const char TestsDiscription[TestCounter][256] = {
		{"Array is out of range test"},
		{"Last element isn\'t duplicate"},
		{"Element have duplicate early"},
		{"Array is full of duplicate"},
		{"Mixed test"},
		{"Miss checked element"}
	}; //�������� ������� �����

	bool Secuess;//����������, ������������ ����������� ��� ������

	int Tests[TestCounter][10] = {
		{1, 2, 3, 4, 4},
		{ 1, 2, 3, 4, 5 },
		{1, 2, 1, 3, 1, 4},
		{ 1, 1, 1, 1, 1},
		{ 1, 2, 4, 6, 1, 2, 5},
		{1, 1, 2, 1, 2}
	};//�������� ������� ������

	int RightLength[TestCounter][3] = {
		{0},
		{0},
		{3, 0},
		{5, 0},
		{2, 2, 0},
		{3, 2, 0}
	}; //���������� ����� �������

	int Answers[TestCounter][2][7] = {
		{
			{-1001, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1}
		},
		{
			{-1001, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1}
		},
		{
			{0, 2, 4, -1, -1}, 
			{-1, -1, -1, -1, -1}
		},
		{
			{ 0, 1, 2, 3, 4},
			{-1, -1, -1, -1, -1}
		},
		{
			{ 0, 4, -1, -1, -1},
			{ 1, 5, -1, -1, -1}
		},
		{
			{0, 1, 3, -1, -1},
			{2, 4, -1, -1, -1}
		}
	};//������ �� �����

	Secuess = true;//���������� ���������, ��� ���� �������
	for(int i = 0; i < TestCounter; i++){
		NormalizeAnswer(EqualArr);
		//����� ����������
		FindDuplicate(Tests[i], LengthOfTests[i], EqualArr, ArrColumns);
		if (!CompareArrays(Answers[i], EqualArr, RightLength[i])) {
			printf("Incorrect %d) %s \n", i + 1, TestsDiscription[i]);
		}

		Secuess = Secuess && (CompareArrays(Answers[i], EqualArr, RightLength[i]));
	}

	if(Secuess)
		printf("Tets passed\n");
}


int main(){
	//�������� ������ �������� �������
	int arr[20], N;

	UnitTests();
	
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

	int EqualArr[20][20];//��������� ������ ��� ������ �������� ����������
	int colums, rows;//������� � ������ ��� ������
	int ArrColumns[20] = {0};

	NormalizeAnswer(EqualArr);
	//����� ����������
	FindDuplicate(arr, N, EqualArr, ArrColumns);
	if (EqualArr[0][0] == -1001) //����� � ������, ���� ���������� ���
		printf("no solustion!");
	//������� ���������
	else
		print(EqualArr, ArrColumns);
	printf("\n\n");

	return 0;
}


