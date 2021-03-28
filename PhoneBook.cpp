#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAXPEOPLE 100 // Максимальное число контактов
#define MAXLEN   50  // Максимальная длина строки

struct СPeople {
	char name[MAXLEN];			  // Имя
	char surname[MAXLEN];		  // Фамилия
	char number[MAXLEN];		  // Номер телефона
	char dateBirth[MAXLEN];		  // Дата рождения	
	struct СPeople* next = nullptr;
};

struct SingleLinkedList {
	struct СPeople* root = nullptr;
};

int  menuSelect();
int  inputAmountOfStructs();
void inputListOfStructs();
int  menuEditing();
void deleteStruct();
bool Equals(СPeople contact, char* name, char* surname);
void editing();
int  menuFields();
void outputList();
void sorting();
void clearInputBuf();
void outputStruct(struct СPeople* StructOfData);
void freeList();
void merge_sort(int i, int j, struct СPeople* a, struct СPeople* aux, int choice);
bool lessStructures(СPeople first, СPeople second, int choice);
bool less(char* first, char* second);
bool more(char* first, char* second);
void outputInFile();
void input();
int menuInput();
void fileInput();
int menuFile();

void AddToEnd(struct СPeople* StructOfData);
void AddToBegin(struct СPeople* StructOfData);
int Count();

struct SingleLinkedList contacts;
const char* title = "№ Имя		Фамилия		 Номер телефона		  Дата рождения";

/*Написать программу, реализующую односвязный список с функциями добавления, удаления и перестановкой
Функции добавления элемента, удаления (по имени-фамилии), сортировки (по любому полю)*/


int main()
{
	SetConsoleCP(1251);			// Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);	// Установка кодовой страницы win-cp 1251 в поток вывода
	//setlocale(LC_ALL, "Russian");

	bool isMainMenuActive = true;
	while (isMainMenuActive)
	{
		int userInput = menuSelect();
		switch (userInput)
		{
		case 1: input(); break;
		case 2:
		{
			bool isMenuEditing = true;
			while (isMenuEditing)
			{
				int choice = menuEditing();
				switch (choice)
				{
				case 1: deleteStruct();				break;
				case 2: editing();					break;
				case 3: sorting();					break;
				case 4: isMenuEditing = false;		break;
				}
			}
		} break;
		case 3: outputList();				  break;
		case 4: outputInFile();				  break;
		case 5: isMainMenuActive = false;	  break;
		}
	}
}

void AddToEnd(struct СPeople* StructOfData)
{
	if (contacts.root != nullptr)
	{
		СPeople* curPointer = contacts.root;
		while (curPointer->next != nullptr)
		{
			curPointer = curPointer->next;
		}
		curPointer->next = StructOfData;
	}
	else
		contacts.root = StructOfData;
}

void AddToBegin(struct СPeople* StructOfData)
{
	СPeople* curPointer = contacts.root;
	contacts.root = StructOfData;
	contacts.root->next = curPointer;
}

int Count()
{
	СPeople* curPointer = contacts.root;
	int count = 0;
	while (curPointer != nullptr)
	{
		count++;
		curPointer = curPointer->next;
	}
	return count;
}

int menuSelect()
{
	system("cls");	// Очистка экрана 
	puts("Меню");
	puts("1 - Ввод");
	puts("2 - Редактирование");
	puts("3 - Вывод на консоль");
	puts("4 - Вывод в файл");
	puts("5 - Выход");

	unsigned int choice;
	do
	{
		printf("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 6));

	return choice;
}

int menuInput()
{
	system("cls");	// Очистка экрана 
	puts("Меню ввода");
	puts("1 - Загрузка из файла");
	puts("2 - Ввод с консоли");

	int choice;
	do
	{
		printf("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 2));

	return choice;
}

int menuFile()
{	
	puts("Меню загрузки из файла");
	puts("1 - Добавить к существующим записям");
	puts("2 - Заменить");

	int choice;
	do
	{
		printf("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 2));

	return choice;
}

void input()
{
	int choice = menuInput();
	if (choice == 1)
		fileInput();
	else
		inputListOfStructs();
}

void fileInput()
{
	if (menuFile() == 2)
		freeList();

	char nameFile[50];
	printf("Введите название файла: ");
	scanf_s("%s", nameFile, sizeof(nameFile));

	FILE* fileOnlyRead;
	errno_t err = fopen_s(&fileOnlyRead, nameFile, "rb");
	if (err == 0)
		printf("Файл %s открылся\n", nameFile);
	else
	{
		printf("Файл %s не открылся\n", nameFile);
		exit(0);
	}

	int size = 0;
	fscanf_s(fileOnlyRead, "%d", &size);

	for (int i = 0; i < size; i++)
	{
		struct СPeople* contact = (СPeople*)calloc(1, sizeof(СPeople));

		fscanf_s(fileOnlyRead, "%s", contact->name, MAXLEN);
		fscanf_s(fileOnlyRead, "%s", contact->surname, MAXLEN);
		fscanf_s(fileOnlyRead, "%s", contact->number, MAXLEN);
		fscanf_s(fileOnlyRead, "%s", contact->dateBirth, MAXLEN);

		AddToBegin(contact);
	}
	fclose(fileOnlyRead);

	outputList();
	clearInputBuf();
}

int inputAmountOfStructs()
{
	unsigned int amountPeople, mistakeProofing;
	do
	{
		printf("Введите количество контактов: ");
		mistakeProofing = scanf_s("%d", &amountPeople);
	} while (amountPeople < 1 || mistakeProofing < 1);

	return amountPeople;
}

void inputListOfStructs()
{
	int amountOfStructs = inputAmountOfStructs();

	puts(title);
	printf("Введите список из %d контактов: \n", amountOfStructs);
	clearInputBuf();

	for (int i = 0; i < amountOfStructs; i++)
	{
		struct СPeople* contact = (СPeople*)calloc(1, sizeof(СPeople));
		// Нужно выделять память динамически, чтобы значения хранились в куче (сохранялись после выхода из подпрограммы)

		printf("Введите данные %d контакта \n", i + 1);

		printf("Введите имя: ");
		gets_s(contact->name, MAXLEN);

		printf("Введите фамилию: ");
		gets_s(contact->surname, MAXLEN);

		printf("Введите номер телефона: ");
		gets_s(contact->number, MAXLEN);

		printf("Введите дату рождения в формате dd.MM.yyyy: ");
		gets_s(contact->dateBirth, MAXLEN);

		AddToBegin(contact);
	}
}

void clearInputBuf()
{
	int garbageCollector;
	while ((garbageCollector = getchar()) != '\n' && garbageCollector != EOF)
	{
	}
}

int menuEditing()
{
	system("cls");	// Очистка экрана 
	puts("Меню");
	puts("1 - Удаление отдельной строки");
	puts("2 - Редактирование определённых полей списка");
	puts("3 - Сортировка");
	puts("4 - Выход");

	int choice;
	do
	{
		printf("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 4));

	return choice;
}

void deleteStruct()
{
	СPeople* curPointer = contacts.root;

	if (curPointer == nullptr)
	{
		puts("Список пуст. ");
		getchar();
		return;
	}

	puts("Выберите контакт для удаления ");
	char name[MAXLEN], surname[MAXLEN];
	printf("Введите имя: ");
	gets_s(name, MAXLEN);
	printf("Введите фамилию: ");
	gets_s(surname, MAXLEN);

	if (Equals(*contacts.root, name, surname))
	{
		contacts.root = contacts.root->next;
		return;
	}

	while (curPointer->next != nullptr)
	{
		if (Equals(*curPointer->next, name, surname))
		{
			curPointer->next = curPointer->next->next;
			return;
		}
		curPointer = curPointer->next;
	}

	puts("Данного контакта нет.");
	getchar();
}

bool Equals(СPeople contact, char* name, char* surname)
{
	if (strcmp(contact.name, name) == 0 && strcmp(contact.surname, surname) == 0)
		return true;
	return false;
}

void editing()
{
	СPeople* curPointer = contacts.root;

	if (curPointer == nullptr)
	{
		puts("Список пуст. ");
		getchar();
		return;
	}

	puts("Выберите контакт для редактирования ");
	char name[MAXLEN], surname[MAXLEN];
	printf("Введите имя: ");
	gets_s(name, MAXLEN);
	printf("Введите фамилию: ");
	gets_s(surname, MAXLEN);

	bool isFound = false;
	if (Equals(*curPointer, name, surname))
	{
		outputStruct(curPointer);
		isFound = true;
	}

	while (curPointer->next != nullptr && !isFound)
	{
		if (Equals(*curPointer, name, surname))
		{
			outputStruct(curPointer);
			isFound = true;
		}
		curPointer = curPointer->next;
	}

	if (!isFound)
	{
		puts("Данного контакта нет.");
		getchar();
		return;
	}

	puts("Выберите поле для редактирования ");
	int choice = menuFields();

	switch (choice)
	{
	case 1:
		printf("Введите имя: ");
		gets_s(curPointer->name, MAXLEN);
		break;
	case 2:
		printf("Введите фамилию: ");
		gets_s(curPointer->surname, MAXLEN);
		break;
	case 3:
		printf("Введите номер телефона: ");
		gets_s(curPointer->number, MAXLEN);
		break;
	case 4:
		printf("Введите дату рождения в формате dd.MM.yyyy: ");
		gets_s(curPointer->dateBirth, MAXLEN);
		break;
	}

	outputStruct(curPointer);
	getchar();
}

void sorting()
{
	СPeople* curPointer = contacts.root;

	if (curPointer == nullptr)
	{
		puts("Список пуст. ");
		getchar();
		return;
	}
	outputList();

	puts("Выберите поле для сортировки ");
	int choice = menuFields();

	int amount = Count();
	struct СPeople* contactsArray = (СPeople*)calloc(amount, sizeof(СPeople));

	for (int i = 0; i < amount; i++)
	{
		contactsArray[i] = *curPointer;
		curPointer = curPointer->next;
	}
	freeList();

	struct СPeople* auxiliaryContactsArray = (СPeople*)calloc(amount, sizeof(СPeople));
	merge_sort(0, amount - 1, contactsArray, auxiliaryContactsArray, choice);
	free(auxiliaryContactsArray);

	for (int i = amount - 1; i >= 0; i--)
		AddToBegin(&contactsArray[i]);

	outputList();
}

void freeList()
{
	contacts.root->next = nullptr;
	free(contacts.root);
	contacts.root = nullptr;
}

void merge_sort(int i, int j, struct СPeople* a, struct СPeople* aux, int choice) {
	if (j <= i) {
		return;     // the subsection is empty or a single element
	}
	int mid = (i + j) / 2;

	// left sub-array is a[i .. mid]
	// right sub-array is a[mid + 1 .. j]

	merge_sort(i, mid, a, aux, choice);     // sort the left sub-array recursively
	merge_sort(mid + 1, j, a, aux, choice);     // sort the right sub-array recursively

	int pointer_left = i;       // pointer_left points to the beginning of the left sub-array
	int pointer_right = mid + 1;        // pointer_right points to the beginning of the right sub-array

	// we loop from i to j to fill each element of the final merged array
	for (int k = i; k <= j; k++) {
		if (pointer_left == mid + 1) {      // left pointer has reached the limit
			aux[k] = a[pointer_right];
			pointer_right++;
		}
		else if (pointer_right == j + 1) {        // right pointer has reached the limit
			aux[k] = a[pointer_left];
			pointer_left++;
		}
		else if (lessStructures(a[pointer_left], a[pointer_right], choice)) {        // pointer left points to smaller element
			aux[k] = a[pointer_left];
			pointer_left++;
		}
		else {        // pointer right points to smaller element
			aux[k] = a[pointer_right];
			pointer_right++;
		}
	}

	for (int k = i; k <= j; k++) {      // copy the elements from aux[] to a[]
		a[k] = aux[k];
	}
}

bool lessStructures(СPeople first, СPeople second, int choice)
{
	switch (choice)
	{
	case 1:
		return less(first.name, second.name);
		break;
	case 2:
		return less(first.surname, second.surname);
		break;
	case 3:
		return less(first.number, second.number);
		break;
	case 4:
		return less(first.dateBirth, second.dateBirth);
		break;
	}
}

bool less(char* first, char* second)
{
	if (strcmp(first, second) < 0)
		return true;
	return false;
}

bool more(char* first, char* second)
{
	if (strcmp(first, second) > 0)
		return true;
	return false;
}

int menuFields()
{
	puts("Меню");
	puts("1 - Имя");
	puts("2 - Фамилия");
	puts("3 - Номер телефона");
	puts("4 - Дата рождения");

	int choice;
	do
	{
		printf("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 4));

	return choice;
}

void outputList()
{
	if (contacts.root == nullptr)
	{
		puts("Список пуст. ");
		getchar();
		return;
	}

	puts("Список контактов");
	puts(title);

	СPeople* curPointer = contacts.root;
	int i = 0;
	do
	{
		if (i != 0)
			curPointer = curPointer->next;
		printf("%d ", i + 1);
		printf("%-010s ", curPointer->name);
		printf("%-020s ", curPointer->surname);
		printf("%-025s ", curPointer->number);
		printf("%-010s \n", curPointer->dateBirth);
		i++;
	} while (curPointer->next != nullptr);

	puts("Для продолжения нажмите любую клавишу.");
	getchar();
}

void outputStruct(struct СPeople* StructOfData)
{
	puts(title);
	printf("%-09s ", StructOfData->name);
	printf("%-010s ", StructOfData->surname);
	printf("%-011s ", StructOfData->number);
	printf("%-012s \n", StructOfData->dateBirth);
}

void outputInFile()
{
	char nameFile[50];
	printf("Введите название файла: ");
	scanf_s("%s", nameFile, sizeof(nameFile));

	FILE* fileWrite;
	errno_t err = fopen_s(&fileWrite, nameFile, "w+");
	if (err == 0)
		printf("Файл %s открылся\n", nameFile);
	else
	{
		printf("Файл %s не открылся\n", nameFile);
		clearInputBuf();
		getchar();
		return;
	}

	if (contacts.root == nullptr)
	{
		fprintf(fileWrite, "Список пуст. \n");
		getchar();
		return;
	}

	fprintf(fileWrite, "Список контактов \n");
	fprintf(fileWrite, "%s \n", title);

	СPeople* curPointer = contacts.root;
	int i = 0;
	do
	{
		if (i != 0)
			curPointer = curPointer->next;
		fprintf(fileWrite, "%d ", i + 1);
		fprintf(fileWrite, "%-010s ", curPointer->name);
		fprintf(fileWrite, "%-020s ", curPointer->surname);
		fprintf(fileWrite, "%-025s ", curPointer->number);
		fprintf(fileWrite, "%-010s \n", curPointer->dateBirth);
		i++;
	} while (curPointer->next != nullptr);

	fclose(fileWrite);
	printf("Список сохранен в файле %s \n", nameFile);
	clearInputBuf();
	getchar();
}
