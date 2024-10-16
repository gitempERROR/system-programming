#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
	node* next_node;
	int data;
};

void print(node* head) 
{
	node* last_element = head;
	while (last_element != NULL) {
		printf_s("%d ", last_element->data);
		last_element = last_element->next_node;
	}
	printf_s("\n");
}

node* create(int data) 
{
	node* head = calloc(1, sizeof(node));
	head->next_node = NULL;
	head->data = data;
}


node* get_node_by_id(node* head, int index, int* start_index) {
	node* last_element = head;
	while (last_element->next_node->next_node != NULL && *start_index != index) {
		last_element = last_element->next_node;
		*start_index = *start_index + 1;
	}
	return last_element;
}

node* add_in_index(node* head, int data, int index)
{
	node* last_element = head;
	node* new_element;
	int i = 1;

	if (index == 0) {
		new_element = calloc(1, sizeof(node));
		new_element->data = data;
		new_element->next_node = head;
		head = new_element;
		return head;
	}

	last_element = get_node_by_id(head, index, &i);

	if (i != index) {
		if (i = index - 1) {
			new_element = calloc(1, sizeof(node));
			new_element->data = data;
			new_element->next_node = last_element->next_node->next_node;
			last_element->next_node->next_node = new_element;
		}
		else {
			printf_s("\nНекорректная индексация!\n");
		}
		return head;
	};

	new_element = calloc(1, sizeof(node));
	new_element->data = data;
	new_element->next_node = last_element->next_node;
	last_element->next_node = new_element;

	return head;
}

void clear(node* head) {
	node* last_element = head;
	while (last_element != NULL) {
		head = last_element;
		last_element = last_element->next_node;
		free(head);
	}
}

node* remove_by_index(node* head, int index) 
{
	node* last_element = head;
	node* removed_element;
	int i = 1;

	if (index == 0) {
		head = last_element->next_node;
		free(last_element);
		return head;
	}

	last_element = get_node_by_id(head, index, &i);

	if (i != index) {
		printf_s("\nНекорректная индексация!\n");
		return head;
	};

	removed_element = last_element->next_node;
	last_element->next_node = last_element->next_node->next_node;
	free(removed_element);

	return head;
}

node* swap_by_indexes(node* head, int index1, int index2)
{
	node* last_element1 = head;
	node* last_element2 = head;
	node* buffer;
	int i = 1;
	int id1 = index1;
	index1 = min(index1, index2);
	index2 = max(id1, index2);

	last_element2 = get_node_by_id(head, index2, &i);

	if (i != index2) return head;

	if (index1 == 0) {
		buffer = head;
		head = last_element2->next_node;
		last_element2->next_node = buffer;
		buffer = head->next_node;
		head->next_node = last_element2->next_node->next_node;
		last_element2->next_node->next_node = buffer;
		return head;
	}

	i = 1;

	last_element1 = get_node_by_id(head, index1, &i);

	if (i != index1) return head;

	buffer = last_element1->next_node;
	last_element1->next_node = last_element2->next_node;
	last_element2->next_node = buffer;
	buffer = last_element1->next_node->next_node;
	last_element1->next_node->next_node = last_element2->next_node->next_node;
	last_element2->next_node->next_node = buffer;

	return head;
}

void main() 
{
	system("chcp 1251>nul");
	int a;
	node* head = calloc(1, sizeof(node));
	while (1) {
		printf_s("1 - Создать новый список\n2 - добавить в текущий список по индексу\n3 - напечатать текущий список\n4 - удалить по индексу\n5 - поменять местами по индексам\n");
		scanf_s("%d", &a);
		switch (a)
		{
		case(1):
		{
			int b;
			printf_s("Введите значение первого элемента - ");
			scanf_s("%d", &b);
			head = create(b); // Создание списка
			break;
		}
		case(2):
		{
			int b;
			printf_s("Введите значение элемента - ");
			scanf_s("%d", &b);
			int c;
			printf_s("Введите индекс элемента для вставки - ");
			scanf_s("%d", &c);
			head = add_in_index(head, b, c);
			break;
		}
		case(3):
		{
			print(head);
			break;
		}
		case(4):
		{
			int c;
			printf_s("Введите индекс элемента для удаления - ");
			scanf_s("%d", &c);
			head = remove_by_index(head, c); // Удаление начального элемента
			break;
		}
		case(5):
		{
			int b;
			printf_s("Введите индекс элемента 1 - ");
			scanf_s("%d", &b);
			int c;
			printf_s("Введите индекс элемента 2 - ");
			scanf_s("%d", &c);
			head = swap_by_indexes(head, b, c);
			break;
		}
		default:
			break;
		}
	}
}
