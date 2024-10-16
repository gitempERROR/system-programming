#include <stdio.h>
#include <stdlib.h>

typedef void (*func)();
typedef func* funcArray;

struct delegate {
	funcArray functions;
	int functions_count;
	void (*add)(struct delegate*, func);
	void (*remove)(struct delegate*, func);
	void (*launch)(struct delegate*);
	void (*remove_repeats)(struct delegate*);
};

void addFunction(struct delegate* this, func function) {
	this->functions_count++;
	this->functions = (func*)realloc(this->functions, this->functions_count * sizeof(func));
	this->functions[this->functions_count - 1] = *function;
}

void removeFunction(struct delegate* this, func function) {
	funcArray functions = malloc(0 * sizeof(func));
	int count = 0;
	for (int i = 0; i < this->functions_count; i++) {
		if (this->functions[i] != function) {
			count++;
			functions = realloc(functions, count * sizeof(func));
			functions[count - 1] = this->functions[i];
		}
	}

	free(this->functions);

	this->functions_count = count;
	this->functions = functions;
}

void launch(struct delegate* this) {
	for (int i = 0; i < this->functions_count; i++) {
		this->functions[i]();
	}
}

void removeRepeats(struct delegate* this) {
	funcArray functions = malloc(0 * sizeof(func));
	int count = 0;
	int stop = 0;
	for (int i = 0; i < this->functions_count; i++) {
		stop = 0;
		for (int j = 0; j < count; j++) {
			if (functions[j] == this->functions[i]) {
				stop = 1;
				break;
			}
		}
		if (stop) continue;
		count++;
		functions = realloc(functions, count * sizeof(func));
		functions[count - 1] = this->functions[i];
	}

	free(this->functions);

	this->functions_count = count;
	this->functions = functions;
}

struct delegate createDelegate() {
	funcArray functions = malloc(0 * sizeof(func));
	struct delegate new_delegate = { functions, 0, addFunction, removeFunction, launch, removeRepeats };
	return new_delegate;
}

void hello() {
	printf_s("hello ");
}

void world() {
	printf_s("world! ");
}

void main() {
	system("chcp 1251>nul");
	struct delegate new_delegate = createDelegate();
	int a;
	while (1) {
		printf_s("\nВыберите действие:\n1 - Добавить функцию hello в делегат\n2 - Добавить функцию world в делегат\n3 - Удалить функции hello из делегата\n4 - Удалить функции world из делегата\n5 - Запустить функции из делегата\n6 - Удалить повторения\n");
		scanf_s("%d", &a);
		switch (a)
		{
		case(1):
		{
			new_delegate.add(&new_delegate, &hello);
			break;
		}
		case(2):
		{
			new_delegate.add(&new_delegate, &world);
			break;
		}
		case(3):
		{
			new_delegate.remove(&new_delegate, hello);
			break;
		}
		case(4):
		{
			new_delegate.remove(&new_delegate, world);
			break;
		}
		case(5):
		{
			new_delegate.launch(&new_delegate);
			break;
		}
		case(6):
		{
			new_delegate.remove_repeats(&new_delegate);
			break;
		}
		default:
			break;
		}
	}
}