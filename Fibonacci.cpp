#include <iostream>
void Fibonacci();
using namespace std;
int main(int argc, char* argv[])
{
	Fibonacci();
	return 0;
}
void Fibonacci()
{
	int first = 0, second = 1, n = 0;
	std::cout << first << " ";
	for(int i = 0; i < 25; i++)
	{
		std::cout << n << " ";
		n = first + second;
		first = second;
		second = n;
	}
}
