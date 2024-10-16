#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define sqr(a) a * a
#define hp(p) p/2
#define area(p, a, b, c) sqrt((hp(p)) * (hp(p) - a) * (hp(p) - b) * (hp(p) - c))
#define x1_pre 1
#define x2_pre 3
#define x3_pre 7
#define y1_pre 2
#define y2_pre 4
#define y3_pre 6

double lenght(double x1, double x2, double y1, double y2);
int triangle_prep(double* P, double* S);
int triangle(double x1, double x2, double x3, double y1, double y2, double y3, double* P, double* S);

double lenght(double x1, double x2, double y1, double y2) {
	return sqrt(sqr((x2 - x1)) + sqr((y2 - y1)));
}

int triangle_prep(double* P, double* S) {
	double len1, len2, len3;

#if x1_pre == x2_pre == x3_pre || y1_pre == y2_pre == y3_pre 
	return 1;
#elif x1_pre == x2_pre && y1_pre == y2_pre || x1_pre == x3_pre && y1_pre == y3_pre || x2_pre == x3_pre && y2_pre == y3_pre 
	return 1;
#else
	len1 = lenght(x1_pre, x2_pre, y1_pre, y2_pre);
	len2 = lenght(x1_pre, x3_pre, y1_pre, y3_pre);
	len3 = lenght(x2_pre, x3_pre, y2_pre, y3_pre);

	if (len1 >= len2 + len3 || len2 >= len1 + len3 || len3 >= len1 + len2)
	return 1;

	* P = len1 + len2 + len3;
	*S = area(*P, len1, len2, len3);
#endif
}

int triangle(double x1, double x2, double x3, double y1, double y2, double y3, double* P, double* S) {
	double len1, len2, len3;

	if (x1 == x2 == x3 || y1 == y2 == y3) return 1;
	if (x1 == x2 && y1 == y2 || x1 == x3 && y1 == y3 || x2 == x3 && y2 == y3) return 1;

	len1 = lenght(x1, x2, y1, y2);
	len2 = lenght(x1, x3, y1, y3);
	len3 = lenght(x2, x3, y2, y3);

	if (len1 >= len2 + len3 || len2 >= len1 + len3 || len3 >= len1 + len2) return 1;

	*P = len1 + len2 + len3;
	*S = area(*P, len1, len2, len3);
}

void main() {
	while (1) {
		system("chcp 1251>nul");
		printf_s("Выберите действие:\n1 - Посчитать длину отрезка\n2 - Найти площадь и периметр треугольника\n3 - Найти площадь и периметр треугольника функцией препроцессора\n");
		int a;
		double x1, y1, x2, y2, x3, y3, lenght_result, S, P;
		scanf_s("%d", &a);
		switch (a)
		{
		case(1):
			printf_s("Введите через пробел x1 y1 x2 y2:\n");
			scanf_s("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			lenght_result = lenght(x1, x2, y1, y2);
			printf_s("Длина отрезка - %lf\n", lenght_result);
			break;
		case(2):
			printf_s("Введите через пробел x1 y1 x2 y2 x3 y3:\n");
			scanf_s("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
			if (triangle(x1, x2, x3, y1, y2, y3, &P, &S) == 1) {
				printf_s("Не треугольник!\n");
			}
			else {
				printf_s("Площадь треугольника - %lf, периметр треугольника - %lf\n", S, P);
			}
			break;
		case(3):
			if (triangle_prep(&P, &S) == 1) {
				printf_s("Не треугольник!\n");
			}
			else {
				printf_s("Площадь треугольника - %lf, периметр треугольника - %lf\n", S, P);
			}
		default:
			break;
		}
	}
}
