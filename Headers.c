#include "Header_file_task.h"

void main() {
	system("chcp 1251>nul");
	int a, b, result;
	char* string1 = malloc(100);
	char* string2 = malloc(100);
	char* string_result;
	float float_result;
	char* double_input_1 = malloc(100);
	double double_input_2;
	printf_s("Метод из заголовочного файла stdio.h\n");
	printf_s("Введите целочисленное число с помощью метода из заголовочного файла stdio.h - ");
	scanf_s("%d", &a);

	while (1) {
		printf_s("Выберите действие:\n1 - сложение\n2 - вычитание\n3 - умножение\n4 - деление\n5 - объединение строк\n6 - преобразовать строку в число\n7 - преобразовать число в строку\n");
		scanf_s("%d", &a);
		switch (a)
		{
		case(1):
			printf_s("Введите значения а и b: ");
			scanf_s("%d %d", &a, &b);
			result = sum(a, b);
			printf_s("%d\n", result);
			break;
		case(2):
			printf_s("Введите значения а и b: ");
			scanf_s("%d %d", &a, &b);
			result = dif(a, b);
			printf_s("%d\n", result);
			break;
		case(3):
			printf_s("Введите значения а и b: ");
			scanf_s("%d %d", &a, &b);
			result = mult(a, b);
			printf_s("%d\n", result);
			break;
		case(4):
			printf_s("Введите значения а и b: ");
			scanf_s("%d %d", &a, &b);
			float_result = divide(a, b);
			printf_s("%f\n", float_result);
			break;
		case(5):
			printf_s("Введите строку а:\n");
			getchar();
			gets(string1);
			printf_s("Введите строку b:\n");
			gets(string2);
			string_result = concat(string1, string2);
			printf_s("%s\n", string_result);
			break;
		case(6):
			printf_s("Введите число: ");
			getchar();
			gets(double_input_1);
			printf_s("%lf\n", strToDouble(double_input_1));
			break;
		case(7):
			printf_s("Введите число: ");
			scanf_s("%lf", &double_input_2);
			printf_s("%s\n", doubleToStr(double_input_2));
			break;
		default:
			break;
		}
	}

	return 1;
}
