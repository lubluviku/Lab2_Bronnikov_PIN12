#define _CRT_SECURE_NO_WARNINGS
#define filename "data.txt"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Student {
	char* fam;
	char* name;
	char* faculty;
	int group;
	static int count;
};
int Student::count;

Student* add(Student* students) {
	Student* result = new Student[Student::count + 1];
	for (int i = 0; i < Student::count; i++) {
		result[i].fam = new char[sizeof(students[i].fam) + 1];
		strcpy(result[i].fam, students[i].fam);
		result[i].name = new char[sizeof(students[i].name) + 1];
		strcpy(result[i].name, students[i].name);
		result[i].faculty = new char[sizeof(students[i].faculty) + 1];
		strcpy(result[i].faculty, students[i].faculty);
		result[i].group = students[i].group;
	}
	delete[] students;
	char buff[50];
	printf("%s", "Фамилия: ");
	while (getc(stdin) != '\n');
	scanf("%50[^\n]%*c", buff);
	result[Student::count].fam = new char[strlen(buff) + 1];
	strcpy(result[Student::count].fam, buff);

	printf("%s", "Имя: ");
	scanf("%50[^\n]%*c", buff);
	result[Student::count].name = new char[strlen(buff) + 1];
	strcpy(result[Student::count].name, buff);

	printf("%s", "Факультет: ");
	scanf("%50[^\n]%*c", buff);
	result[Student::count].faculty = new char[strlen(buff) + 1];
	strcpy(result[Student::count].faculty, buff);

	int buffg;
	printf("%s", "Группа: ");
	scanf("%i", &buffg);
	result[Student::count].group = buffg;
	Student::count++;
	return result;
}

void table(Student* students) {
	printf("\n\n%-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Факультет", "Номер группы");
	printf("%s\n", "-------------------------------------------------------------------------------");
	for (int i = 0; i < Student::count; i++) {
		printf("%-10d %-10s %-10s %-10s %d\n", i + 1, students[i].fam, students[i].name, students[i].faculty, students[i].group);
	}
	printf("%s\n", "-------------------------------------------------------------------------------");
	printf("Количество записей в базе: %i\n\n\n", Student::count);
}

void by_fam(Student* students, char* fam) {
	for (int i = 0; i < Student::count; i++) {
		if (strcmp(students[i].fam, fam) == 0) {
			printf("%-10d %-10s %-10s %-10s %d\n", i + 1, students[i].fam, students[i].name, students[i].faculty, students[i].group);
		}
	}
}

void find_by_fam(Student* students, char* fam) {
	printf("\n\n%-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Факультет", "Номер группы");
	printf("%s\n", "-------------------------------------------------------------------------------");
	for (int i = 0; i < Student::count; i++) {
		if (strcmp(students[i].fam, fam) == 0)
			printf("%-10d %-10s %-10s %-10s %d\n", i + 1, students[i].fam, students[i].name, students[i].faculty, students[i].group);
	}
	printf("%s\n\n\n", "-------------------------------------------------------------------------------");
}

void find_by_group(Student* students, int group) {
	printf("\n\n%-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Факультет", "Номер группы");
	printf("%s\n", "-------------------------------------------------------------------------------");
	for (int i = 0; i < Student::count; i++) {
		if (students[i].group == group)
			printf("%-10d %-10s %-10s %-10s %d\n", i + 1, students[i].fam, students[i].name, students[i].faculty, students[i].group);
	}
	printf("%s\n", "-------------------------------------------------------------------------------");
}

void alph_order(Student* students) {
	printf("\n\n%-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Факультет", "Номер группы");
	printf("%s\n", "-------------------------------------------------------------------------------");
	char** fams = new char* [Student::count];
	for (int i = 0; i < Student::count; ++i) {
		fams[i] = new char[51];
	}
	for (int i = 0; i < Student::count; i++) {
		strcpy(fams[i], students[i].fam);
	}
	int size_array = Student::count;
	char* temp;
	int code;
	for (int n = 1; n < size_array; n++) {
		for (int m = 0; m < size_array - n; m++) {
			code = strcmp(fams[m + 1], fams[m]);
			if (code < 0) {
				temp = fams[m];
				fams[m] = fams[m + 1];
				fams[m + 1] = temp;
			}
		}
	}
	for (int m = 0; m < size_array; m++) { // 
		for (int i = m + 1; i < size_array; i++) {
			if (strcmp(fams[i], fams[m]) == 0) {
				for (int k = i; k < size_array - 1; k++) {
					fams[k] = fams[k + 1];
				}
				size_array--;
			}
		}
	}
	for (int i = 0; i < size_array; ++i) {
		by_fam(students, fams[i]);
		delete[] fams[i];
	}
	delete[] fams;
	/*for (int i = 0; i < Student::count; ++i) {
		delete[] fams[i];
	}*/
	printf("%s\n\n\n", "-------------------------------------------------------------------------------------------------------");
}

void save_work(Student* massive, const char* file_name)
{
	Student* tw;
	FILE* file_pointer;
	tw = massive;
	if ((file_pointer = fopen(file_name, "w")) == NULL)
	{
		perror("Ошибка открытия файла: режим save_txt");
	}
	// запись строк в текстовый файл
	fprintf(file_pointer, "%i\n", Student::count);
	for (tw = massive; tw < massive + Student::count; tw++)
	{
		fprintf(file_pointer, "%s\n", tw->name);
		fprintf(file_pointer, "%s\n", tw->fam);
		fprintf(file_pointer, "%s\n", tw->faculty);
		fprintf(file_pointer, "%i\n", tw->group);
	}
	fclose(file_pointer); // закрыть файл
};

Student* load_work(const char* file_name)
{
	Student* students = new Student[0];
	FILE* file_pointer;
	char buffs[50];
	// Проверка на прошлые записи + загрузка
	if ((file_pointer = fopen(file_name, "rb+")) == NULL) {
		printf("Файла нет!\n");
		return students;
	}
	else {
		printf("Файл найден!\n");
		if ((file_pointer = fopen(file_name, "r")) == NULL)
		{
			perror("Ошибка открытия файла");
		}
		// Перебор всего файла
		int intBuff;
		char buff[50];
		fscanf(file_pointer, "%s\n", buff);
		intBuff = 0;
		sscanf(buff, "%d", &intBuff);

		Student::count = intBuff;
		Student* result = new Student[Student::count];
		for (int i = 0; !feof(file_pointer); i++)
		{
			fscanf(file_pointer, "%s\n", buff);
			result[i].name = new char(strlen(buff) + 1);
			strcpy(result[i].name, buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].fam = new char(strlen(buff) + 1);
			strcpy(result[i].fam, buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].faculty = new char(strlen(buff) + 1);
			strcpy(result[i].faculty, buff);

			fscanf(file_pointer, "%s\n", buff);
			int intBuff = 0;
			sscanf(buff, "%d", &intBuff);
			result[i].group = intBuff;
		}
		fclose(file_pointer); // закрыть файл
		printf("Данные успешно загружены!\n");
		delete[] students;
		return result;
	}
};

int main() {
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	Student* students;
	FILE* file_pointer;
	setlocale(LC_ALL, "Rus");
	students = load_work(filename);



	// Основной цикл программы
	while (TRUE) {
		printf("1 - Добавить новый элемент\n2 - Распечатать информацию в табличном виде\n3 - Поиск по фамилии\n4 - Поиск по номеру группы\n5 - Alph order\n6 - Закрыть\n");
		int buff;
		scanf("%i", &buff);
		switch (buff) {
		case 1: {
			students = add(students);
			break;
		}
		case 2: {
			table(students);
			break;
		}
		case 3: {
			char buff[50];
			printf("Введите фамилию: ");
			while (getc(stdin) != '\n');
			scanf("%50[^\n]%*c", buff);
			char* buff2 = buff;
			find_by_fam(students, buff2);
			break;
		}
		case 4: {
			int buff;
			printf("Введите номер группы: ");
			scanf("%i", &buff);
			find_by_group(students, buff);
			break;
		}
		case 5: {
			alph_order(students);
			break;
		}
		case 6: {
			if (Student::count != 0) {
				save_work(students, filename);
			}
			delete[] students;
			return 0;
		}
		}
		buff = 0;
	}
}