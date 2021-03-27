#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#define MAXPEOPLE 100 // Максимальное число контактов
#define MAXLEN   50  // Максимальная длина строки

void initializationList(struct СPeople* StructOfData);
int  menuSelect();
void inputArrayOfStructs(struct СPeople* StructOfData, const char* title);
int  inputAmountOfStructs();
int  findFreeStruct(struct СPeople* StructOfData);
int  menuEditing();
int  inputItemNumber(struct СPeople* StructOfData, const char* title);
int	 isEmptyList(struct СPeople* StructOfData);
void deleteStruct(struct СPeople* StructOfData, const char* title);
void editing(struct СPeople* StructOfData, const char* title);
int  menuFields();
void outputList(struct СPeople* StructOfData, const char* title);
void sorting(struct СPeople* StructOfData);

struct СPeople {
	char name[MAXLEN];			  // Имя
	char surname[MAXLEN];		  // Фамилия
	char number[MAXLEN];		  // Номер телефона
	char dateBirth[MAXLEN];		  // Дата рождения	
	bool isDeleted;
	struct СPeople* next;
};

struct SingleLinkedList {
	struct СPeople* root;
};

struct SingleLinkedList contacts;

/*Написать программу, реализующую односвязный список с функциями добавления, удаления и перестановкой
Функции добавления элемента, удаления (по имени-фамилии), сортировки (по любому полю)*/


int main()
{
	SetConsoleCP(1251);			// Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);	// Установка кодовой страницы win-cp 1251 в поток вывода

	const char* title = "№ Имя   Фамилия   Номер телефона   Дата рождения";
	struct СPeople people[MAXPEOPLE];
	initializationList(people);  //Инициализация списка (массива структур)

	int isMainMenuActive = 1;
	while (isMainMenuActive)
	{
		int userInput = menuSelect();
		switch (userInput)
		{
		case 1: inputArrayOfStructs(people, title); break;
		case 2:
		{
			int isMenuEditing = 1;
			while (isMenuEditing)
			{
				int choice = menuEditing();
				switch (choice)
				{
				case 1: deleteStruct(people, title); break;
				case 2: editing(people, title);		break;
				case 3: sorting(people);			break;
				case 4: isMenuEditing = 0;			break;
				}
			}
		} break;
		case 3: outputList(people, title); break;
		case 4: isMainMenuActive = 0;	  break;
		}
	}
}

void initializationList(struct СPeople* StructOfData)
{
	for (register int i = 0; i < MAXPEOPLE; i++)
		StructOfData[i].isDeleted = true;
}

void addToBegin(struct СPeople* StructOfData)
{
	if (root != null)
	{
		var curPointer = root;
		while (curPointer.next != null)
		{
			curPointer = curPointer.next;
		}
		curPointer.next = node;
	}
	else
		root = node;
}

int menuSelect()
{
	int choice;
	system("cls");	// Очистка экрана 
	puts("Меню");
	puts("1 - Ввод");
	puts("2 - Изменение");
	puts("3 - Вывод");
	puts("4 - Выход");
	do
	{
		puts("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 5));
	return choice;
}

int inputAmountOfStructs()
{
	int amountPeople, mistakeProofing;
	do
	{
		puts("Введите количество контактов: ");
		mistakeProofing = scanf_s("%d", &amountPeople);
	} while (amountPeople < 1 || mistakeProofing < 1);

	return amountPeople;
}

void inputArrayOfStructs(struct СPeople* StructOfData, const char* title)
{
	int amountOfStructs = inputAmountOfStructs();

	puts(title);
	printf("Введите список из %d контактов: \n", amountOfStructs);

	for (int i = 0; i < amountOfStructs; i++)
	{
		int slot;
		slot = findFreeStruct(StructOfData);
		if (slot == -1) {
			puts("Список заполнен.");
			return;
		}

		printf("Введите данные %d контакта \n", i + 1); 

		printf("Введите имя: ");
		while (getchar() != '\n');
		gets_s(StructOfData[slot].name, MAXLEN);

		printf("Введите фамилию: ");
		gets_s(StructOfData[slot].surname, MAXLEN);

		printf("Введите номер телефона: ");
		gets_s(StructOfData[slot].number, MAXLEN);

		printf("Введите дату рождения в формате dd.MM.yyyy: ");
		gets_s(StructOfData[slot].dateBirth, MAXLEN);

		StructOfData[slot].isDeleted = false;
	}
}

int findFreeStruct(struct СPeople* StructOfData)
{
	// Поиск свободной структуры
	register int i;
	for (i = 0; !StructOfData[i].isDeleted && i < MAXPEOPLE; i++);
	if (i == MAXPEOPLE)
		return -1; // Свободных структур нет
	return i;
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
		puts("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 4));

	return choice;
}

int inputItemNumber(struct СPeople* StructOfData, const char* title)
{
	if (isEmptyList(StructOfData))
	{
		puts("Список пуст. ");
		getchar();
		return -1;
	}

	outputList(StructOfData, title);

	int number;
	do
	{
		int mistakeProofing;
		puts("Введите номер записи контакта: ");
		do
		{
			mistakeProofing = scanf_s("%i", &number);
		} while (number < 0 || mistakeProofing < 1);

		if (StructOfData[number - 1].isDeleted)
			printf("Товар с номером %i не существует \n", number);

	} while (number - 1 < 0 || number - 1 >= MAXPEOPLE || StructOfData[number - 1].isDeleted);

	return number - 1;
}

int isEmptyList(struct СPeople* StructOfData)
{
	for (int i = 0; i < MAXPEOPLE; i++)
		if (StructOfData[i].isDeleted == 0)
			return 0;
	return 1;
}

void deleteStruct(struct СPeople* StructOfData, const char* title)
{
	int number = inputItemNumber(StructOfData, title);
	if (number == -1)
		return;
	StructOfData[number].isDeleted = 1;
}

void editing(struct СPeople* StructOfData, const char* title)
{
	if (isEmptyList(StructOfData))
	{
		puts("Список пуст. ");
		getchar();
		return;
	}

	int number = inputItemNumber(StructOfData, title);
	if (number == -1)
		return;
	
	puts("Выберите поле для редактирования ");
	int choice = menuFields();

	switch (choice)
	{
	case 1:
		puts("Введите имя: ");
		gets_s(StructOfData[number].name, MAXLEN);
		break;
	case 2:
		puts("Введите фамилию: ");
		gets_s(StructOfData[number].surname, MAXLEN);
		break;
	case 3:
		puts("Введите номер телефона: ");
		gets_s(StructOfData[number].number, MAXLEN);
		break;
	case 4:
		puts("Введите дату рождения в формате dd.MM.yyyy: ");
		gets_s(StructOfData[number].dateBirth, MAXLEN);
		break;
	}
}

void sorting(struct СPeople* StructOfData)
{
	;
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
		puts("Введите номер нужного пункта: ");
		scanf_s("%i", &choice);
		while (getchar() != '\n');
	} while ((choice < 1) || (choice > 4));

	return choice;
} 

void outputList(struct СPeople* StructOfData, const char* title)
{
	if (isEmptyList(StructOfData))
	{
		puts("Список пуст. ");
		getchar();
		return;
	}

	puts("Список контактов");
	puts(title);
	for (int i = 0; i < MAXPEOPLE; i++)
		if (!StructOfData[i].isDeleted)
		{
			printf("%d ", i + 1);
			printf("%-09s ", StructOfData[i].name);
			printf("%-010s ", StructOfData[i].surname);
			printf("%-011s ", StructOfData[i].number);
			printf("%-012s \n", StructOfData[i].dateBirth);
		}
	puts("Для продолжения нажмите любую клавишу.");
	getchar();
}


