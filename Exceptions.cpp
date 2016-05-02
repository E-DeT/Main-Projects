#include <iostream>
#include <new>

using namespace std;

typedef void(*rof) ();

class test
{
	public:
		static void* operator new(long long unsigned int size_t);
};

void allocError()
{
	cout << "Out of memory exception\n";
	abort();
}

void* test::operator new(long long unsigned int size_t)
{
	cout << "operator called\n";
	rof curHandler = allocError;
	rof oldHandler = set_new_handler(curHandler);
	void* alloc_Mem;
	try
	{
		alloc_Mem = ::operator new(size_t);
	}
	catch(bad_alloc&)
	{
		allocError();
	}
	set_new_handler(oldHandler);
	return alloc_Mem;
}

int main(int argc, char* argv[])
{
	for(int i = 0; i < 5; i++)
	{
		new test;
	}
	return 0;
}
