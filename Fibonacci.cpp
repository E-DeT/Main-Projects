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
	int* p_One = new int(0);
	int* p_Two = new int(1);
	bool isOne = true;
	cout << *p_One << ", " << *p_Two << ", ";
	for(int i = 0; i < 25; i++)
	{
		if(isOne)
		{
			*p_One = (*p_One + *p_Two);
			isOne = false;
			cout << *p_One << ", ";
		}
		else if(!isOne)
		{
			*p_Two = (*p_One + *p_Two);
			isOne = true;
			cout << *p_Two << ", ";
		}
		
	}
}
