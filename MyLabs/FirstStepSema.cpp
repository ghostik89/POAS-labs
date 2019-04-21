#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string.h>

/*
	text – исходный текст
	strCount – кол-во строк текста
	lineIndex, characterIndex – начальная позиция поиска (индекс строки, индекс символа в строке)
*/
void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]);
//функция для извлечения подстроки, заключенной
//в скобки
//char* extract(char* str, int& index)
//{
//	char buffer[MAX];   //временное пространство для подстроки
//	char* pstr(nullptr);//указатель на новую строку для возраста
//	int numL(0);        //счетчик найденных левых скобок
//	int bufindex(index);//сохранить начальное значение index
//
//	do
//	{
//		buffer[index - bufindex] = *(str + index);
//		switch (buffer[index - bufindex])
//		{
//		case ')':
//			if (0 == numL)
//			{
//				buffer[index - bufindex] = '\0'; //заменить ')'
//				++index;                         //на '\0'
//				pstr = new char[index - bufindex];
//				if (!pstr)
//				{
//					cout << "Program broken :'(\n";
//					exit(1);
//				}
//				strcpy_s(pstr, index - bufindex, buffer);//копировать подстроку в новую память
//
//				return pstr;
//			}
//			else numL--;
//			break;
//
//		case '(': numL++;
//			break;
//		}
//
//	} while (*(str + index++) != '\0');
//
//	error(0);
//	cout << "Program broken :'(\n";
//	exit(1);
//}
/*
	str – исходная строка
	beginPos, endPos – начальная и конечная позиции подстроки, которую необходимо вырезать (удалить)
	Выходные данные:
	str – усеченная строка
*/
void cutString(char str[81], int beginPos, int endPos);

int main() {
	char text[20][81];
	int M;
	scanf("%d", &M);

	for (int i = 0; i < M; i++)
		gets_s(text[i]);

	int brackets[4] = {-1};
	findPairBrackets(text, M, 0, 0, brackets);

	for (int i = 0; i < 4; i++)
		printf("%d ", brackets[i]);

	return 0;
}

void findPairBrackets(const char text[20][81], int strCount, int lineIndex, int characterIndex, int brackets[4]) {
	int numL = 0, numR = 0;
	int posiL = 0, posjL = 0, posiR = 0, posjR = 0;

	for (int i = 1; i < strCount; i++) {
		for (int j = 0; text[i][j] != '\0'; j++) {
			switch (text[i][j]) {
				case ')':
						numR++;
				break;
				case '(':
					if (numL == 0) {
						posiL = i;
						posjL = j;
					}
					numL++;
				break;
			}
			if ((numL == numR) && numR > 0 && numL > 0) {
				posiR = i;
				posjR = j;
				brackets[0] = posiL;
				brackets[1] = posjL;
				brackets[2] = posiR;
				brackets[3] = posjR;
				break;
			}
		}
		if (brackets[0] != -1) {
			strCount -= i;
			break;
		}
	}

}