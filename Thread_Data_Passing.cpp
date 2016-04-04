/// The purpose of this program is to take data input by
/// the user within one thread, and to then pass that data to
/// an overhead data structure which allows a second thread
/// to display and then delete the data given

#include <iostream>
#include <thread>
#include <mutex>

struct data_node ///Holds the user input
{
    /// Since the data will pass out
    /// of scope after construction,
    /// we need to allocate the data
    /// given to ensure proper access

    char data[25];

    data_node(char c[]);

    data_node* next_node; ///Currently useless

    ~data_node();
};

data_node::~data_node()
{
    /// The below deletion causes a cascade
    /// style deletion of data_node's,
    /// ensuring that should the head_node
    /// be deleted at any point, all
    /// data_node's will be properly freed

    delete next_node;

    next_node = 0;
}

data_node::data_node(char c[]): next_node(0)
{
    for(int i = 0; c[i]; i++)
    {
        data[i] = c[i];
    }
}

///The overhead structure for data_node's

struct head_node
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

bool head_node::addData(char data[]) ///Returns a bool to check if successful
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
    char data[25];
    char choice;
    std::cout << "Thread " << std::this_thread::get_id() << " reached\n";
    while(true)
    {
        std::cout << "\nDo you wish to display your string values so far (Y/N)? ";
        std::cin >> choice;
        while(true)
        {
            if(choice == 'Y' || choice == 'y')
            {
                goto ex;
            }
            else if (choice == 'N' || choice == 'n')
            {
                break;
            }
            else
            {
                std::cout << "\nPlease input a valid choice\n";
                std::cout << "\nDo you wish to display your string values so far (Y/N)? ";
                std::cin >> choice;
            }
        }
        std::cout << "\nThen please input a character string or value: ";
        std::cin >> data;
        mx.lock();
        HN.addData(data); ///Create a data_node and attach it to HN
        mx.unlock();
    }
    ex:
        return;
}

void displayData(std::mutex& mx, head_node& HN) ///Displays user input
{
    bool exit = false;
    std::cout << "\nThread " << std::this_thread::get_id() << " reached\n\n";
    std::cout << "You typed:\n";
    while(!exit)
    {
        if(HN.first_node != 0)
        {
            /// While the below lock is unnecessary
            /// (since this code block relies on the
            /// first thread to execute properly), it
            /// is still good practice to use locks
            /// anyways.

            mx.lock();

            std::cout << (*HN.first_node).data << std::endl; ///Display data_node's data

            HN.nodeHandled(); ///Delete data_node

            mx.unlock();
        }
        else
        {
            exit = true;
        }
    }
}
void threadHandle() ///Head thread
{
    std::cout << "Thread " << std::this_thread::get_id() << " created\n\n";

    std::mutex mx; ///To prevent data racing
    head_node node; ///Overhead node

    std::thread grabData{dataInput, std::ref(mx), std::ref(node)};
    grabData.join();
    std::thread processData{displayData, std::ref(mx), std::ref(node)};
    processData.join();
}

int main()
{
    std::thread threader{threadHandle};

    threader.join();

    char c;
    std::cout << std::endl;
    std::cin >> c; ///To have the program wait

    return 0;
}
