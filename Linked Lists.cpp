//Written in C++
//The point of the program is to create a doubly linked list
//Each 'node' holds a unique integer key
//Cout is overloaded to accept node keys

#include <iostream>
#include <thread>

using namespace std;

struct List //Holds address of first and last nodes
{
	struct rof_node *first_node, *last_node, *main_list;
	void alloc_LList(int num_nodes = 5);
	~List();
};

struct rof_node //Generic node
{
	int key;
	rof_node *next_node, *prev_node;
	~rof_node();
};

rof_node::~rof_node()
{
	if(next_node)
	{
		delete next_node;
	}
	prev_node = 0, next_node = 0;
}

List::~List()
{
	delete main_list;
	first_node = 0; last_node = 0;
}

ostream& operator<<(ostream& os, List& _list) //Display list keys (going forwards)
{	
	//If _list has an initalized main_list, and main_list has more than one node
	if(_list.main_list && _list.main_list != _list.last_node)
	{
		rof_node *temp = (_list.main_list);
		while(temp != _list.last_node)
		{
			os << (*temp).key << endl;
			temp = (*temp).next_node;
		}
		os << (*temp).key << endl;
	}
	else if (_list.main_list) //Else if only one node
	{
		os << (*(_list.main_list)).key << endl;
	}
	else //Else if its not initialized 
	{
		return (os << 0);
	}
	
	return os;
}

void List::alloc_LList(int num_nodes) //Allocates nodes
{
	rof_node *this_node;
	if(num_nodes > 0) //Create first node
	{
		this_node = new rof_node;
		first_node = this_node, last_node = this_node, main_list = this_node;
		(*this_node).prev_node = 0, (*this_node).next_node = 0, (*this_node).key = 0;
		--num_nodes;
	}
	else
	{
		cout << "Invalid number of nodes called for\n\n";
		main_list = 0;
	}
	
	for(int i = 1; i <= num_nodes; i++) //If more than one node was called for
	{
		this_node = new rof_node;
		(*last_node).next_node = this_node;
		(*this_node).prev_node = last_node, (*this_node).next_node = 0, (*this_node).key = i;
		last_node = this_node;
	}
	cout << "This thread is: " <<this_thread::get_id() << endl;
}
void hal()
{
	cout << "Hallo\n";
}

int main(int argc, char* argv[])
{
	List list;
	thread t1{[&list]{list.alloc_LList(10);}}; //Experimenting with multi-threading
	t1.join(); //Wait for t1 to finish
	//list.alloc_LList(10);
	cout << list;
	//getchar();
	return 0;
}
