#include "header.h"

void *Allocator::malloc(size_t size)
{
	HLOCAL MEMORY_BLOCK;
	void*  new_ptr;

	cout << "��������� ������: " << endl;

	MEMORY_BLOCK = LocalAlloc(LHND, size);						//�������� ���� ������ � ��������� ��� ������

	if (MEMORY_BLOCK == NULL)
	{
		cout << "������ � ��������� ������." << endl;
		new_ptr = nullptr;
	}
	else
	{
		new_ptr = LocalLock(MEMORY_BLOCK);						//��������� ���� ������ ���� �������� ������ �� main
	}

	return new_ptr;
}

void *Allocator::realloc(void *ptr, size_t newSize)
{
	HLOCAL MEMORY_BLOCK = LocalHandle(ptr);							//���������� ������������� ���������� ����� ������

	cout << "������������� ������" << endl;

	LocalUnlock(MEMORY_BLOCK);										//������������ ��� ���� ������ ��� ������������� ������

	MEMORY_BLOCK = LocalReAlloc(MEMORY_BLOCK, newSize, LMEM_ZEROINIT);	//������������ ������ ��� ��� ����, ������� ��������� ������

	if (MEMORY_BLOCK == NULL)
	{
		cout << "������������� �� �������" << endl;
		ptr = nullptr;
	}
	else
	{
		ptr = LocalLock(MEMORY_BLOCK);								//��������� ���� ����� �������� ������ � ���������� � ���� ������
	}

	return ptr;
}

void Allocator::free(void *ptr)
{
	cout << "������� ������." << endl;
	HLOCAL MEMORY_BLOCK = LocalHandle(ptr);

	LocalUnlock(MEMORY_BLOCK);

	if (LocalFree(MEMORY_BLOCK) == NULL)
		cout << "������ ������� �������." << endl;
	else
		cout << "���...." << endl;
}
