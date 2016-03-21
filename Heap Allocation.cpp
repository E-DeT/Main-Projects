#include <iostream>
#include <string>
using namespace std;
class thing
{
	public:
		thing(thing& rthing);
		thing(int& age, string& name);
		~thing();
		thing& operator=(const thing& t);
		string& getName();
	private:
		string *mp_Name = 0;
		int *mp_Age = 0;
};
void to_copy(thing obj);
thing::thing(int& age, string& name)
{
	cout << "Object created" << endl;
	mp_Name = new string(name);
	mp_Age = new int(age);
}
thing& thing::operator=(const thing& t)
{
	cout << "Equal operator called" << endl;
	if(this != &t)
	{
		delete mp_Name;
		delete mp_Age;
		mp_Name = new string(*(t.mp_Name));
		mp_Age = new int(*(t.mp_Age));
	}
	return *this;
}
string& thing::getName()
{
	return *mp_Name;
}
thing::~thing()
{
	cout << "Object deleted" << endl;
	delete mp_Name;
	delete mp_Age;
}
thing::thing(thing& c_thing)
{
	cout << "Object copied" << endl;
	c_thing.mp_Name = new string(*(c_thing.mp_Name));
	c_thing.mp_Age = new int(*(c_thing.mp_Age));
}
void to_copy(thing obj){}
int main (int argc, char* argv[])
{
	int age = 16, x = 25;
	string name = "E" , y = "Doot";
	thing main(age, name);
	thing* t_P = new thing(x, y);
	cout << ((*t_P).getName());
	to_copy(main);
	getchar();
	return 0;
}


