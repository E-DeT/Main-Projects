#include <iostream>
using namespace std;
class rof 
{
	public:
		friend void doot();
		static int s_Count;
		rof(char* cStr);
	private:
		int data;
		void strLength(char* str);
};

int rof::s_Count = 0;

rof::rof(char* cStr)
{
	if(cStr)
	{
		strLength(cStr);
		cout << data << endl;
		cout << cStr << endl;;
	}
	s_Count++;
}
void rof::strLength(char* str)
{
	int count = 0;
	while (*(str) != '\0')
	{
		if(*(str) == ' ')
		{
			count--;
		}
		str++;
		count++;
	}
	data = count;
}
void pTo();
void pTo()
{
	int x,y;
	int *c,*d; 
	x = y = 5;
	c = &x;
	d = &y;
	int** f, **g; 
	f = &c; 
	g = &d;
	int** pArray[2]; 
	pArray[0] = f; 
	pArray[1] = g;
	cout << *(*(pArray[0])); 
}
int main (int argc, char* argv[])
{
	rof mai("Hello World"), dai("Five"), lai("Fifteen");
	int x = 5;
	
	cout << mai.s_Count << endl << endl;
	pTo();
}
