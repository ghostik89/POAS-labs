#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <ctype.h>

/*
	функция для нахождения разделителя
	char ch - символ, которой проверяется
*/
bool IsSeparator(char ch) {
	char Separators[10] = "!\";:?-., ";
	if (strchr(Separators, ch) != NULL)
		return true;
	else
		return false;
}

/*
	фунция, которая преобразует буквы в порядковый номер
	в алфавите
	char ch -  буква, которая преобразуется в символ
*/
int CharToInt(char ch) {
	int number = -1;
	
	if (ch >= 'A' && ch <= 'Z')
		number = (int)(ch - 'A');
	if (ch >= 'a' && ch <= 'z')
		number = (int)(ch - 'a');

	return number;
}

/*
	функция, которая возвращает максимальный элемент в массиве
	int arr[26] - массив, в котором ищем данные
*/
int MaxInArray(int arr[26]) {
	int max = 0;

	for(int i = 0; i < 26; i++)
		if (max < arr[i]) {
			max = arr[i];
		}
	return  max != 0 ? max: -1;
}

int main() {

	int Alphabet[26] = { 0 }; //массив, который хранит количество букв в тесте
	//исходные данные
	char text[20][81];
	int M; int num; int chars = 0;
	 
	scanf("%d\n", &M);
	if (M < 1 || M > 20)//ввод текста
		return 0;

	for (int i = 0; i < M; i++) {//ввод текста
		gets_s(text[i]);
		if (strlen(text[i]) > 81) {//тест на корректные данные
			printf("Invalid data\n");
			return 0;
		}
	}

	//считаем количество букв
	for(int i = 0; i < M; i++)
		for (int j = 0; j < strlen(text[i]); j++)
			if (IsSeparator(text[i][j]) || j == 0) {
				if(j == 0)//если символ первый в строке, то его тоже считаем 
					num = CharToInt(text[i][j]);
				else
					if(j + 1 < strlen(text[i]))//если символ в строке стоит после разделителя
						num = CharToInt(text[i][j + 1]);
				if (num != -1) //если символ, который мы нашли - буква, то считаем его
					Alphabet[num]++;
			}

	int max = 0;
	max = MaxInArray(Alphabet);

	if(max == -1)
		printf("no solution\n");
	//вывод букв в порядке убывания их количества в тексте
	for (int i = 0; i < 26; i++) {
		if (Alphabet[i] == max) {
			char ch = (char)((int)'a' + i);
			printf("%c", ch);
		}
	}	
		
	return 0;
}