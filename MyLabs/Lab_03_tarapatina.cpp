// Lab_03_tarapatina.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "testing.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//�������� ������ �������� �������
	int arr[20], N;
	scanf("%d", &N);
	
	//�������� N �� �������������� ��������� ���������
	if (N > 20 || N < 2) {
		error_printf("Invalid data\n");
		return 0;
	}

	//���������� �������
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		//�������� �������� �� �������������� ��������� ���������
		if (arr[i] < -1000 || arr[i] > 1000) {
			error_printf("Invalid data\n");
			return 0;
		}
	}

	

	//����� ������ � �������
	
	bool NotEqual = true;//���������, ��� ���������� � ������� ��� ������
	bool It_Write = false; //��������������� ���������� ��� ������ � ����� ������
	bool Checked = false; //���������� ��� �������� ���� ������� ����� ������������ � �����
	for(int i = 0; i < N - 1; i++){
		//����� ������
		for(int k = i - 1; k >= 0; k--){
			if(arr[k] == arr[i])
				Checked = true;
		}
		//���� ������� ����� �� �������������
		if(!Checked){
			for (int j = i + 1; j < N; j++) {
				//���� ������� arr[i] ��� ��������� �������
				//� �� �������������� �����
				if (arr[j] == arr[i] && !It_Write) {
					printf("%d %d ", i, j);
					NotEqual = false;
					It_Write = true;
				}
				//���� � �������� arr[i] ����� ���� �����
				else if (arr[j] == arr[i] && It_Write){
					printf("%d ", j);
				}
			}
		}
		//���� � �������� arr[i] ���� ����� � �� �� ��� ����� ���������
		if(It_Write)
			printf("\n");
		It_Write = false;//����� ���������� ������������� ��������
		Checked = false;
	}
	
	//����� �� �������, ������� ���
	if (NotEqual)
		printf("no solution\n");

	//_getch();
	return 0;
}

