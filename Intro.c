#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

static void clearBuffer() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static void readData(int** inputData, int inputCount, char* variables, int* rightInputs) {
	clearBuffer();
	int wrongs = 0;
	printf_s("Введите значения");

	for (int i = 0; i < inputCount; i++) {
		if (rightInputs[i] != 1)
			printf_s(" %c", variables[i]);
	}

	printf_s(": ");

	for (int i = 0; i < inputCount; i++) {
		if (rightInputs[i] != 1 && !scanf_s("%d", inputData[i])) {
			printf_s("Некорректный ввод переменной %c\n", variables[i]);
			wrongs++;
		}
		else { rightInputs[i] = 1; }
	}

	printf_s("\n");

	if (wrongs) {
		readData(inputData, inputCount, variables, rightInputs);
	}
}

static float* calculateSquare() {
	int a = 0;
	int b = 0;
	int c = 0;
	int** inputData = malloc(3 * sizeof(int*));
	int* rightInputs = calloc(3, sizeof(int));
	float d;
	float* output;

	char* variables = "abc";

	inputData[0] = &a;
	inputData[1] = &b;
	inputData[2] = &c;

	readData(inputData, 3, variables, rightInputs);

	d = b * b - 4 * a * c;
	if (d < 0) {
		return NULL;
	}
	else {
		if (d = 0) {
			output = calloc(2, sizeof(float));
			output[0] = -b / (2 * a);
		}
		else {
			output = calloc(2, sizeof(float));
			output[0] = (-b + sqrt(d)) / (2 * a);
			output[1] = (-b - sqrt(d)) / (2 * a);
		}
		return output;
	}
}

static float* calculateSystem() {
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int** inputData = malloc(6 * sizeof(int*));
	int* rightInputs = calloc(6, sizeof(int));
	float* output = calloc(2, sizeof(float));;

	char* variables = "abcdef";

	inputData[0] = &a;
	inputData[1] = &b;
	inputData[2] = &c;
	inputData[3] = &d;
	inputData[4] = &e;
	inputData[5] = &f;

	while (1) {
		rightInputs = calloc(6, sizeof(int));
		readData(inputData, 6, variables, rightInputs);
		if ((a != 0 || d != 0) && (b != 0 || e != 0) && (a != 0 || b != 0) && (d != 0 || b != 0) && !(a == d && b == e)) {
			break;
		}
		else {
			printf_s("Некорректный ввод!\n");
		}
	}

	output[0] = (f - c * e) / (d + (-a) * e);
	if (b != 0)
		output[1] = (c - a * output[0]) / b;
	else
		output[1] = (f - d * output[0]) / e;
	
	return output;
}

static float* calculateFactorial() {
	int a = 0;

	int** inputData = malloc(1 * sizeof(int*));
	int* rightInputs = calloc(1, sizeof(int));
	float* output = calloc(2, sizeof(float));;

	char* variables = "a";

	inputData[0] = &a;

	while (1) {
		rightInputs[0] = 0;
		readData(inputData, 1, variables, rightInputs);
		if (a > 0) {
			break;
		}
		else {
			printf_s("Факториал вычисляется только из положительных чисел!\n");
		}
	}

	output[0] = 1;
	for (int i = 1; i <= a; i++) {
		output[0] *= i;
	}

	return output;
}

static void printResult(float* funcOutput) {
	printf_s("Ответ: ");
	if (funcOutput) {
		printf_s("%f", funcOutput[0]);
		if (funcOutput[1]) {
			printf_s(" %f\n", funcOutput[1]);
		}
		else {
			printf_s("\n");
		}
	}
	else {
		printf_s("Нет корней!\n");
	}
	printf_s("\n");
}

void main() {
	setlocale(LC_ALL, "Rus");

	int choice;
	float* output;
	while (1)
	{
		printf_s("Выберите задачу:\n1 - Квадратное уравненией\n2 - Система линейных уравнений\n3 - Факториал\n0 - Выход\n");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case(1):
		{
			output = calculateSquare();
			printResult(output);
			break;
		}
		case(2): 
		{
			output = calculateSystem();
			printResult(output);
			break;
		}
		case(3):
		{
			output = calculateFactorial();
			printResult(output);
			break;
		}
		case(0):
		{
			exit(0);
		}
		default:
			break;
		}
	}
}