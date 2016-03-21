#include <iostream>
#include <string>

using namespace std;

class rof
{
	public:
		rof(string& n);
		~rof();
		void virtual greet(string* n);
		string* name;
	private:
		string* per_Name = new string("rof"); //rof Name
};
rof::rof(string& n)
{
	name = new string(n);
}
void rof::greet(string* n)
{
	cout << "Hi " << *name << "! It's me, " << *per_Name << "!\n";
}
rof::~rof()
{
	delete per_Name;
	delete name;
}
class foo : public rof
{
	public:
		foo(string& n);
		~foo();
		void greet(string* n);
	private:
		string* per_Name = new string("foo"); //foo Name
};
foo::foo(string& n):
	rof(n) {}
foo::~foo()
{
	delete per_Name;
}
void foo::greet(string* n)
{
	cout << "Hi " << *name << "! It's me, " << *per_Name << "!\n";
}
int main(int argc, char* argv[])
{
	string name = "Ed";
	rof* d_P = new rof(name);
	(*d_P).greet((*d_P).name);
	foo* l_P = new foo(name);
	(*l_P).greet((*l_P).name);
}

