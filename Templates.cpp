#include <iostream>
using namespace std;
template<class t>
class List
{
	public:
		List(int array_size = 10);
		~List();
		t* search(t& search_key);
		bool push(t& obj);
		t* pop(t& obj);
	private:
		t* t_P;
		int array_pos, size;
};
template <class t> List<t>::List(int array_size):
	t_P(new t[array_size]), array_pos(0),
	size(array_size) {}
template <class t> List<t>::~List()
{
	delete [] t_P;
	t_P = 0;
}
template<class t> t* List<t>::search(t& search_key)
{
	t* temp = t_P;
	while((*temp) != 0)
	{
		if((*temp) == search_key)
		{
			return temp;
		}
		temp += 1;
	}
	return 0;
}
template <class t> t* List<t>::pop(t& obj)
{
	t* temp = t_P;
	if(array_pos <= 0)
	{
		return (*(temp += array_pos));
		array_pos--;
	}
	else
	{
		return 0;
	}
}
template <class t> bool List<t>::push(t& obj)
{
	t* temp = t_P;
	if(array_pos < size)
	{
		(*(temp += array_pos)) = obj;
		array_pos++;
		return true;
	}
	else
	{
		return false;
	}
}
int main(int argc, char* argv[])
{
	List<int> listints(5);
	int a = 6, b = 7;
	char* c = "Hallo";
	List<char*> listchar;
	listchar.push(c);
	cout << *(listchar.search(c)) << endl;
	listints.push(a);
	if(listints.search(a))
	{
		cout << *(listints.search(a));
	}
	else
	{
		cout << "Failure";
	}
}
