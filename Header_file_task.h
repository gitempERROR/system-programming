#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b);
int dif(int a, int b);
int mult(int a, int b);
float divide(int a, int b);
char* concat(char* a, char* b);
double strToDouble(char* a);

int sum(int a, int b) {
	return a + b;
}

int dif(int a, int b) {
	return a - b;
}

int mult(int a, int b) {
	return a * b;
}

float divide(int a, int b) {
	return a / b;
}

char* concat(char* a, char* b) {
	int size_a = 1, size_b = 1;
	char* c;
	while (a[size_a - 1] != '\0') size_a++;
	while (b[size_b - 1] != '\0') size_b++;

	c = (char*)malloc(size_a + size_b - 1);

	for (int i = 0; i < (size_a - 1); i++) {
		c[i] = a[i];
	}

	for (int i = 0; i < (size_b - 1); i++) {
		c[size_a - 1 + i] = b[i];
	}

	c[size_a + size_b - 2] = '\0';

	return c;
}

double strToDouble(char* a) {
	double result = 0;
	int decimal_pos = 0;
	int is_negative = 0;

	if (a[0] == '-') is_negative = 1;
	while (a[decimal_pos] != '.' && a[decimal_pos] != '\0') {
		decimal_pos++;
	}

	for (int i = is_negative; i < decimal_pos; i++) {
		result = result * 10 + (a[i] - '0');
	}

	if (a[decimal_pos] == '.') {
		int j = 1;
		for (int i = decimal_pos + 1; a[i] != '\0'; i++) {
			result += (a[i] - '0') * (double)1 / (double)(10 * j);
			j *= 10;
		}
	}

	return result * (-1 + 2 * (1 - is_negative));
}

char* doubleToStr(double a) {
	char* result = (char*)calloc(100, 1);
	int len = 1, comma_placed = 0, negative = 0;

	if (a < 0) {
		a *= -1;
		negative = 1;
		result[0] = '-';
	}

	for(double b = a; b >= 10; b /= 10) {
		len *= 10;
	}

	double b = a;
	for (int i = 0; 1; i++) {
		result[i + comma_placed + negative] = (char)((int)(b / (double)len) + '0');

		if (b - (int)b == 0 && (int)b == 0) break;
		b -= (int)(b / (double)len) * len;

		if (len > 1) len /= 10;

		if ((int)b == 0) {
			b *= 10;
			if (!comma_placed) {
				comma_placed = 1;
				result[i + 1 + negative] = '.';
			}
		}
	}

	return result;
}
