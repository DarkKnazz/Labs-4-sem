#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include "header.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	char *MEMORY_POINTER;
	cout << "������������ ������ �6" << endl;
	cout << "���������� ������������ ����������" << endl;
	cout << "���� ������� ��������� ������, ������������� � �������" << endl << endl;

	MEMORY_POINTER = (char *)Allocator::malloc(30);

	cout << "����� ���������� ������ ��� ���������: " << int(MEMORY_POINTER) << endl << endl;

	cout << "�������� �������� �� ���������" << endl;

	strcpy(MEMORY_POINTER, "Dratuti, I am Zhenya");

	cout << "���������� � �������� ��������� � ��� ������: "<< endl;
	cout << MEMORY_POINTER << endl;
	cout << int(MEMORY_POINTER) << endl << endl;

	MEMORY_POINTER = (char *)Allocator::realloc(MEMORY_POINTER, 50);

	cout << "���������� � �������� ��������� � ��� ������: " << endl;
	cout << MEMORY_POINTER << endl;
	cout << int(MEMORY_POINTER) << endl << endl;

	Allocator::free(MEMORY_POINTER);

	return 0;
}