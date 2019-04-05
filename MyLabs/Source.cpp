#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <conio.h>
//#include "testing.h"

int main() {

	int x1, y1, x2, y2, x3, y3, x4, y4;
	int s = 0;

	scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);

	//проверка координат прямоугольников на соответствие диапозону
	if (x1 < -1000 || x1 > 1000 || x2 < -1000 || x2 > 1000 || x3 < -1000 || x3 > 1000 || x4 < -1000 || x4 > 1000) {
		//error_printf
		printf("Invalid data\n");
		return 0;
	}
	if (y1 < -1000 || y1 > 1000 || y2 < -1000 || y2 > 1000 || y3 < -1000 || y3 > 1000 || y4 < -1000 || y4 > 1000) {
		// error_printf
		printf("Invalid data\n");
		return 0;
	}

	//проверка на наличие пересечения
	if (!(x3 >= x2 || x4 <= x1 || y3 <= y2 || y4 >= y1))
	{
		//вычесление площади при различных пересечениях
		if (x3 >= x1 && x4 <= x2 && y3 <= y1 && y4 >= y2)
		{
			s = (x4 - x3)*(y3 - y4);
		}
		else if (x3 <= x1 && x4 >= x2 && y3 >= y1 && y4 <= y2)
		{
			s = (x2 - x1)*(y1 - y2);
		}


		//если пересекается углами по x..
		if (x3 >= x1 && x4 <= x2)
		{
			if (y3 >= y1 && y4 >= y2)
			{
				s = (x4 - x3)*(y1 - y4);
			}
			else if (y3 <= y1 && y4 <= y2)
			{
				s = (x4 - x3)*(y3 - y2);
			}
		}
		//... или по y
		else if (y3 <= y1 && y4 >= y2)
		{
			if (x3 <= x1 && x4 <= x2)
			{
				s = (y3 - y4)*(x4 - x1);
			}
			else if (x3 >= x1 && x4 >= x2)
			{
				s = (y3 - y4)*(x2 - x3);
			}
		}

		//если стороны совпадают
		//sprava
		if (x3 < x1 && y3 > y1 && x4 > x1 && y4 < y1 && x4 < x2 && y4 > y2)
		{
			s = (x4 - x1)*(y1 - y4);
		}
		else if (x3 < x1 && y3 < y1 && x4 > x1 && y4 < y2 && y3 > y2 && x4 < x2)
		{
			s = (x4 - x1)*(y3 - y2);

		}

		//sleva
		else if (x3 > x1 && x3 < x2 && x4 > x2 && y3 > y1 && y4 < y1 && y4 > y2)
		{
			s = (x2 - x3)*(y1 - y4);

		}
		else if (x3 > x1 && x3 < x2 && x4 > x2 && y3 < y1 && y3 > y2 && y4 < y2)
		{
			s = (x2 - x3)*(y3 - y2);

		}
	}
	printf("%d", s);


	return 0;
}