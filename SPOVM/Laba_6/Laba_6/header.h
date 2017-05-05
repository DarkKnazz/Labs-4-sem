#include <iostream>
#include <Windows.h>
using namespace std;

class Allocator
{
	Allocator(){}

public:
	static void* malloc(size_t size);
	static void* realloc(void* ptr, size_t newSize);
	static void free(void *ptr);
};