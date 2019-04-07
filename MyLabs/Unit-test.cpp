// Unit-test.cpp: определяет точку входа для консольного приложения.
//
#include <stdio.h>


int test_shift_elements(); // тесты для функций
int shift_elements (int submass_offsets, int length, int mass[20]);  //тестируемая функция

int main()
{
// Тестирование
puts("Тестирование функции deleteElement ...");
if(test_shift_elements())
{
puts("\n----------------------------------------------------------------");
puts("\nfunction correct");
}
else
{
puts("\n----------------------------------------------------------------");
puts("\nfunction incorrect");
}

return 0;
}

///////////////////////////////////////
int shift_elements (int submass_offsets, int length, int mass[20])
{
	for (int i=1; i<=submass_offsets; i++)
	{
		int buffer = mass[length-1];
		for (int i=length-2; i>=0; i--)
		{
			mass[i+1]=mass[i];
		}
		mass[0]=buffer;
	}
	return 0;
}

int cmp(int a[], int b[], int length) {
	bool equal = true;
	for (int i = 0; i < length; i++)
		if (a[i] != b[i]) equal = false;
	return equal;
}

// unit-test
int test_shift_elements ()
{
	//Количество тестов
	const int test_count = 5;
    
    //Названия тестов (длиной не более 100 символов) 
    char test_name[test_count][101]=
	{
		"Смещаемая часть меньше, чем половина длины массива",
        "Смещаемая часть больше, чем половина длины массива",
        "Смещаемая часть равна половине длины массива",
        "Массив минимальной длины. Сдвигаем один элемент",
        "Массив максимальной длины. Сдвигаем все 19 элементов"
	};
	// Входные данные для тестирования
	int input_submass_offsets[test_count] = {2, 6, 3, 1, 19};
	int input_length[test_count] = {7, 7, 6, 2, 20};
    int input_arr[test_count][20] =
    {
    {1, 2, 3, 4, 5, 6, 7},
	{1, 2, 3, 4, 5, 6, 7},
	{1, 2, 3, 4, 5, 6},
	{1, 2},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
    };
   
	// Ожидаемые выходные данные
	int expect_arr[test_count][20] =
	{
		{6, 7, 1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6, 7, 1},
        {2, 1},
        {3, 4, 5, 1, 2, 3},
        {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1 }
	};
	int length_expect[test_count] = {7, 7, 6, 2, 20 };

	// Тестирование
	int is_Ok = 1;
	int diff_index [20] = {}; 

	for (int i = 0; i < test_count; i++) 
	{
		//Вызов тестируемой функции
		shift_elements (input_submass_offsets[i], input_length[i], input_arr[i]);

		// Сравниваем полученный результат с эталонным на совпадение
		bool equal = cmp(diff_index, expect_arr[i], length_expect[i]);

		//Проверка результатов
		if (equal) {
			printf("Тест %d пройден\n", i);
		}
		else
		{
			is_Ok = 0;
			printf("Тест %d не пройден\n", i+1);
			puts(test_name[i]);
			printf("Ожидалось: ");
			printf("%d ", expect_arr[i]);
			printf("\nВаш вывод: ");
			printf("%d ", diff_index);
			printf("\n");is_Ok = 0;

		}
	}
	return is_Ok;
}
 




   
