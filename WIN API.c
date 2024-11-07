#include <windows.h>
#include <math.h>
#include <stdio.h>

#define ERROR_FILE_OPEN -3
#define ERROR_INVALID_DATA -4 

void read_file(HANDLE* input, char* path, double* a, double* b, double* c, char* buf);
int square_func(double a, double b, double c, double* x1, double* x2, double* d);
char* add_char_to_string(char* str, char ch);
double str_to_double(char* a);

void main() {
	HANDLE input = NULL;
	HANDLE output = NULL;
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);
	double a, b, c, x1, x2, d;
	int result;
	char* buf = calloc(1, 512);

	read_file(&input, L"input.txt", &a, &b, &c, buf);

	HANDLE outputFile = CreateFile(
		L"Output.txt",
		GENERIC_WRITE, 
		FILE_SHARE_READ, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL 
	);

	// Проверка ошибки при открытии файла
	if (outputFile == INVALID_HANDLE_VALUE) {
		WriteConsoleW(
			std,
			L"Cannot open output file",
			22,
			NULL,
			NULL
		);
		CloseHandle(std);
		exit(GetLastError());
	}

	result = square_func(a, b, c, &x1, &x2, &d);

	if (a == 0 && b == 0) {
		WriteFile(
			outputFile,
			"Не уравнение\n",
			13,
			NULL, 
			NULL
		);
	}
	else {
		char buffer[256];
		if (result != 3) sprintf_s(buffer, sizeof(buffer), "Дискриминант = %lf\n", d);

		else sprintf_s(buffer, sizeof(buffer), "Не квадратное уравнение\n");

		WriteFile(outputFile, buffer, strlen(buffer), NULL, NULL);

		if (result == 0) {
			WriteFile(outputFile, "Нет корней\n", 12, NULL, NULL);
		}
		else if (result == 1 || result == 3) {
			WriteFile(outputFile, "Число корней - 1\n", 18, NULL, NULL);
			sprintf_s(buffer, sizeof(buffer), "x1 = %lf", x1);
			WriteFile(outputFile, buffer, strlen(buffer), NULL, NULL);
		}
		else {
			WriteFile(outputFile, "Число корней - 2\n", 18, NULL, NULL);
			sprintf_s(buffer, sizeof(buffer), "x1 = %lf, x2 = %lf", x1, x2);
			WriteFile(outputFile, buffer, strlen(buffer), NULL, NULL);
		}
	}

	CloseHandle(outputFile);
	CloseHandle(std);
	_getch();
}

void read_file(HANDLE* input, char* path, double* a, double* b, double* c, char* buf) {
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);

	*input = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (input == INVALID_HANDLE_VALUE) {
		WriteConsoleW(
			std,
			L"Cannot open input file",
			22,
			NULL,
			NULL
			);
		CloseHandle(std);
		exit(GetLastError());
	}

	DWORD bytesRead = 0;
	char* number_buf = malloc(1);
	number_buf[0] = '\0';
	char digit;
	unsigned int stage = 0;

	while (TRUE) {
		ReadFile(
			*input,
			buf,
			1,
			&bytesRead,
			NULL
		);

		if ((bytesRead != 1 && stage != 2) || ((buf[0] < 48 || buf[0] > 57) && (buf[0] != ' ' && buf[0] != '.' && buf[0] != '\n' && buf[0] != '\r' && buf[0] != '-'))) {
			WriteConsoleW(
				std,
				L"Cannot read data",
				16,
				NULL,
				NULL
			);
			CloseHandle(std);
			CloseHandle(*input);
			exit(ERROR_INVALID_DATA);
		}
		if (buf[0] == '\r') continue;
		if (buf[0] == ' ' || buf[0] == '\n' || (bytesRead != 1 && stage == 2)) {
			switch (stage)
			{
			case(0):
				*a = str_to_double(number_buf);
				stage++;
				break;
			case(1):
				*b = str_to_double(number_buf);
				stage++;
				break;
			case(2):
				*c = str_to_double(number_buf);
				free(number_buf);
				CloseHandle(std);
				CloseHandle(*input);
				return;
			default:
				exit(ERROR_INVALID_DATA);
				break;
			}
			number_buf = malloc(1);
			number_buf[0] = '\0';
			continue;
		};
		digit = buf[0];
		number_buf = add_char_to_string(number_buf, digit);
	}
}

char* add_char_to_string(char* str, char ch) {
	size_t len = 0;
	while (str[len] != '\0') {
		len++;
	}

	char* new_str = (char*)calloc(len + 2, sizeof(char));

	for (size_t i = 0; i < len; i++) {
		new_str[i] = str[i];
	}

	new_str[len] = ch;
	new_str[len + 1] = '\0';
	return new_str;
}

double str_to_double(char* a) {
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