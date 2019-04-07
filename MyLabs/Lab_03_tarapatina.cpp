// Lab_03_tarapatina.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "testing.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//исходные данные согласно условию
	int arr[20], N;
	scanf("%d", &N);
	
	//проверка N на принадлежность заданному диапозону
	if (N > 20 || N < 2) {
		error_printf("Invalid data\n");
		return 0;
	}

	//считывание массива
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		//проверка элемента на принадлежность заданному диапозону
		if (arr[i] < -1000 || arr[i] > 1000) {
			error_printf("Invalid data\n");
			return 0;
		}
	}

	

	//поиск дублей в массиве
	
	bool NotEqual = true;//считается, что изначально в массиве нет дублей
	bool It_Write = false; //вспомогательная переменная для печати в одной строке
	bool Checked = false; //переменная для проверки были элемент ранее задействован в цикле
	for(int i = 0; i < N - 1; i++){
		//поиск дублей
		for(int k = i - 1; k >= 0; k--){
			if(arr[k] == arr[i])
				Checked = true;
		}
		//если элемент ранее не использовался
		if(!Checked){
			for (int j = i + 1; j < N; j++) {
				//если элемент arr[i] был напечатан впервые
				//и не рассматривался ранее
				if (arr[j] == arr[i] && !It_Write) {
					printf("%d %d ", i, j);
					NotEqual = false;
					It_Write = true;
				}
				//если у элемента arr[i] ранее были дубли
				else if (arr[j] == arr[i] && It_Write){
					printf("%d ", j);
				}
			}
		}
		//если у элемента arr[i] были дубли и он не был ранее напечатан
		if(It_Write)
			printf("\n");
		It_Write = false;//сброс индикатора напечатанного элемента
		Checked = false;
	}
	
	//дубли не найдены, решения нет
	if (NotEqual)
		printf("no solution\n");

	//_getch();
	return 0;
}

