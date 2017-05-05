#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include "header.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	char *MEMORY_POINTER;
	cout << "Лабораторная работа №6" << endl;
	cout << "Реализация собственного аллокатора" << endl;
	cout << "Есть функции выделения памяти, перевыделения и очистки" << endl << endl;

	MEMORY_POINTER = (char *)Allocator::malloc(30);

	cout << "Адрес выделенной памяти под указатель: " << int(MEMORY_POINTER) << endl << endl;

	cout << "Помещаем значение по указателю" << endl;

	strcpy(MEMORY_POINTER, "Dratuti, I am Zhenya");

	cout << "Информация о значении указателя и его адресе: "<< endl;
	cout << MEMORY_POINTER << endl;
	cout << int(MEMORY_POINTER) << endl << endl;

	MEMORY_POINTER = (char *)Allocator::realloc(MEMORY_POINTER, 50);

	cout << "Информация о значении указателя и его адресе: " << endl;
	cout << MEMORY_POINTER << endl;
	cout << int(MEMORY_POINTER) << endl << endl;

	Allocator::free(MEMORY_POINTER);

	return 0;
}