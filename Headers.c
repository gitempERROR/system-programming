#include "Header_file_task.h"

void main() {
	system("chcp 1251>nul");
	int a, b, result;
	char* string1 = malloc(100);
	char* string2 = malloc(100);
	char* string_result;
	float float_result;
	printf_s("%s\n", doubleToStr(-1514.0));
	printf_s("%lf\n", strToDouble("-12591.51515"));
	printf_s("����� �� ������������� ����� stdio.h\n");
	printf_s("������� ������������� ����� � ������� ������ �� ������������� ����� stdio.h - ");
	scanf_s("%d", &a);

	while (1) {
		printf_s("�������� ��������:\n1 - ��������\n2 - ���������\n3 - ���������\n4 - �������\n5 - ����������� �����\n");
		scanf_s("%d", &a);
		switch (a)
		{
		case(1):
			printf_s("������� �������� � � b: ");
			scanf_s("%d %d", &a, &b);
			result = sum(a, b);
			printf_s("%d\n", result);
			break;
		case(2):
			printf_s("������� �������� � � b: ");
			scanf_s("%d %d", &a, &b);
			result = dif(a, b);
			printf_s("%d\n", result);
			break;
		case(3):
			printf_s("������� �������� � � b: ");
			scanf_s("%d %d", &a, &b);
			result = mult(a, b);
			printf_s("%d\n", result);
			break;
		case(4):
			printf_s("������� �������� � � b: ");
			scanf_s("%d %d", &a, &b);
			float_result = divide(a, b);
			printf_s("%f\n", float_result);
			break;
		case(5):
			printf_s("������� ������ �:\n");
			getchar();
			gets(string1);
			printf_s("������� ������ b:\n");
			gets(string2);
			string_result = concat(string1, string2);
			printf_s("%s\n", string_result);
		default:
			break;
		}
	}

	return 1;
}
