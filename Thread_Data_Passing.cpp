/// The purpose of this program is to take data input by
/// the user within one thread, and to then pass that data to
/// an overhead data structure which allows a second thread
/// to display and then delete the data

#include <iostream>
#include <thread>
#include <mutex> ///To ensure data isn't overridden

struct data_node ///Designed as a queue
{
    ///Since the data will pass out
    ///of scope after construction,
    ///we need to dynamically
    ///allocate the data given
    ///to ensure proper access

    char** data;

    data_node(char* c);
    data_node* next_node;

    ///The destructor is
    ///necessary due to the
    ///dynamically allocated
    ///data

    ~data_node();
};

data_node::data_node(char* c): data(new char*(c)), next_node(0){}

data_node::~data_node()
{
    delete data;
    data = 0;
    next_node = 0;
}

struct head_node ///The overhead structure
{
    head_node();
    head_node(char* data);
    ~head_node();
    bool addData(char* data);
    void nodeHandled();
    data_node* first_node;
};

head_node::head_node(): first_node(0){} ///No data passed
head_node::head_node(char* data): first_node(new data_node(data)){} ///Data passed

head_node::~head_node()
{
    delete first_node;
    first_node = 0;
}

bool head_node::addData(char* data) ///Returns a bool to check if successful
{
    data_node* temp = first_node;
    if(temp != 0) ///If first_node is assigned
    {
        while((*temp).next_node != 0) ///Purposely designed as a queue
        {
            temp = (*temp).next_node;
        }
        if(data) ///If the data is valid
        {
            (*temp).next_node = new data_node(data);
            return true;
        }
        else ///Else fail to allocate
        {
            return false;
        }
    }
    else ///Else assign first_node
    {
        if(data)
        {
            first_node = new data_node(data);
            return true;
        }
        else
        {
            return false; ///Failed to allocate data
        }
    }
}

///Delete first_node, assign first_node's next_node as first_node

void head_node::nodeHandled()
{
    data_node* temp = first_node;
    temp ? first_node = (*first_node).next_node : first_node = 0;
    temp ? delete temp : delete temp;
}

void dataInput(std::mutex& mx, head_node& HN) ///Grabs user input
{
    char* data;
    char ary[25];
    std::cout << "Please input a character string or value: ";
    std::cin >> ary;
    mx.lock();
    data = ary;
    HN.addData(data); ///Create a data_node and attach it to HN
    mx.unlock();
}

void displayData(std::mutex& mx, head_node& HN) ///Displays user input
{
    bool exit = false;
    while(!exit)
    {

        /// For some reason, the code below detects that
        /// a value is stored at head_node's first_node
        /// (leading to the reasoning that the first thread
        /// worked), but fails to properly display it.

        if(HN.first_node != 0)
        {
            mx.lock();

            std::cout << "Second thread reached\n";
            std::cout << "You typed: ";
            std::cout << *(*HN.first_node).data; ///Display data_node's data
            std::cout << "\nThe memory address of the data is: ";
            std::cout << (*HN.first_node).data;

            HN.nodeHandled(); ///Delete data_node

            mx.unlock();

            exit = true;
        }
    }
}
void threadHandle() ///Head thread
{
    using namespace std;

    mutex mx; ///To prevent data racing
    head_node node;

    thread grabData{dataInput, ref(mx), ref(node)};
    grabData.join();
    thread processData{displayData, ref(mx), ref(node)};
    processData.join();
}

int main()
{
    std::thread threader{threadHandle};

    threader.join();

    char c;
    std::cin >> c; ///To have the program wait

    return 0;
}
