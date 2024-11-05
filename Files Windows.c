#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ERROR_FILE_OPEN -3
#define ERROR_INVALID_DATA -4 

int read_data(FILE* input, char* path, double* a, double* b, double* c, char* any);
int square_func(double a, double b, double c, double* x1, double* x2, double* d);

void main() {
	FILE* input = NULL;
	FILE* output = NULL;
	char any;
	double a, b, c, x1, x2, d;
	int result;

	read_data(input, "Input.txt", &a, &b, &c, &any);

	output = fopen("Output.txt", "wt");
	if (output == NULL) {
		fprintf_s(stdout, "error creating output file");
		if (input != NULL) {
			fclose(input);
		}
		exit(ERROR_FILE_OPEN);
	}

	if (a == 0 && b == 0) {
		fputs("Не уравнение", output);
		_getch();
		return;
	}

	result = square_func(a, b, c, &x1, &x2, &d);
	if (result != 3)
		fprintf_s(output, "Дискриминант = %lf\n", d);
	else
		fprintf_s(output, "Не квадратное уравнение\n");

	if (result == 0) {
		fputs("Нет корней", output);
	}
	else if (result == 1 || result == 3) {
		fputs("Число корней - 1\n", output);
		fprintf_s(output, "x1 = %lf", x1);
	}
	else {
		fputs("Число корней - 2\n", output);
		fprintf_s(output, "x1 = %lf, x2 = %lf", x1, x2);
	}
	fclose(output);
	_getch();
}

int square_func(double a, double b, double c, double* x1, double* x2, double* d) {
	if (a == 0) {
		*x1 = c / b;
		return 3;
	}

	*d = b * b - 4 * a * c;

	if (*d < 0) {
		return 0;
	}
	else if (*d == 0) {
		*x1 = -b / (2 * a);
		return 1;
	}
	else {
		*x1 = (-b - sqrt(*d)) / (2 * a);
		*x2 = (-b + sqrt(*d)) / (2 * a);
		return 2;
	}
}

int read_data(FILE* input, char* path, double* a, double* b, double* c, char* any) {
	input = fopen(path, "rt");
	if (input == NULL) {
		fprintf_s(stdout, "error opening input file");
		exit(ERROR_FILE_OPEN);
	}

	if (!fscanf_s(input, "%lf", a) != 1) {
		fprintf(stdout, "error reading data");
		fclose(input);
		exit(ERROR_INVALID_DATA);
	}

	fscanf_s(input, "%c", any);

	if (!fscanf_s(input, "%lf", b) != 1) {
		fprintf(stdout, "error reading data");
		fclose(input);
		exit(ERROR_INVALID_DATA);
	}

	fscanf_s(input, "%c", any);

	if (!fscanf_s(input, "%lf", c) != 1) {
		fprintf(stdout, "error reading data");
		fclose(input);
		exit(ERROR_INVALID_DATA);
	}
	fclose(input);
}