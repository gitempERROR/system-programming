#include <stdlib.h>;
#include <stdio.h>;
#include <locale.h>;

void intPointer() {
	int* choice = malloc(4);
	int* a = malloc(4);
	while (1) {
		printf_s("Выберите действие:\n1 - ввести значение переменной;\n2 - вывести значение переменной;\nостальное - выход.\n");
		scanf_s("%d", choice);
		switch (*choice)
		{
		case(1):
		{
			printf_s("Введите новое значение переменной - ");
			scanf_s("%d", a);
			break;
		}
		case(2):
		{
			printf_s("Текущее значение переменной - %d\n", *a);
			break;
		}
		default:
			return;
			break;
		}
		printf_s("\n");
	}
}

void millionArray() {
	int* array = malloc(1000000 * sizeof(int));
	int* i = malloc(4);
	for (*i = 0; *i < 1000000; (*i)++)
		array[*i] = *i;
	printf_s("Массив создан\n");

	free(array);

	printf_s("Массив удален\n");
}

void variableArrayPrint(int* array, int* lenght) {
	int* i = malloc(4);
	for (*i = 0; *i < *lenght; (*i)++) {
		printf_s("%d ", array[*i]);
	}
	printf_s("\n\n");
}

int** triangle() {
	int* size = malloc(sizeof(int));
	int* i = malloc(sizeof(int));
	int* j = malloc(sizeof(int));
	int* counter = malloc(sizeof(int));
	int** matrix;
	int* matrixRow;
	printf_s("Введите размер треугольника - ");
	scanf_s("%d", size);
	matrix = malloc(*size * sizeof(int*));
	*counter = 0;
	for (*i = 0; *i < *size; (*i)++) {
		matrixRow = malloc((*i + 1) * sizeof(int));
		for (*j = 0; *j <= *i; (*j)++) {
			matrixRow[*j] = *counter;
			printf_s("%d ", matrixRow[*j]);
			(*counter)++;
		}
		matrix[*i] = matrixRow;
		printf_s("\n");
	}
	return matrix;
}

void voidFunctionCaller(void (*functionPointer)()) {
	(*functionPointer)();
}

void main() {
	setlocale(LC_ALL, "Rus");

	int* i = malloc(sizeof(int));
	int** (*trianglePointer)();

	voidFunctionCaller(&intPointer);
	voidFunctionCaller(&millionArray);

	int* array = malloc(5 * sizeof(int));
	for (*i = 0; *i < 5; (*i)++) {
		array[*i] = *i;
	}
	variableArrayPrint(array, i);

	trianglePointer = &triangle;
	int** matrix = (*trianglePointer)();

	printf_s("\n%d\n\n", matrix[1][1]); // Для проверки что матрица содержит значения и к ней можно обратиться
}