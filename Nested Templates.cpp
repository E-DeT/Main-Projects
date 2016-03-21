#include <iostream> 

template <typename t>
class mainclass; 

template <typename t>
class nestedclass 
{
	public:
		nestedclass(); 
		t* t_P; 
		void assignP(mainclass<t>& m); 
};

template <typename t> 
nestedclass<t>::nestedclass() {} 

template <typename t>
class mainclass
{
	public:
		mainclass(t value); 
		nestedclass<t>* nP; 
	private:
		friend class nestedclass<t>; 
		t* main_P;
};

template <typename t>
mainclass<t>::mainclass(t value): 
	main_P(new t(value)), 
	nP(new nestedclass<t>()) {} 
	
template <typename t> 
void nestedclass<t>::assignP(mainclass<t>& m) 
{
	(*this).t_P = m.main_P;
}
int main(int argc, char* argv[])
{
	
	mainclass<char*> mc("Hallo");
	
	(*(mc.nP)).assignP(mc); n

	std::cout << (*(*(mc.nP)).t_P); 
	return 0;
}
