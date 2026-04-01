#include <iostream>
#include <string>
using namespace std;


struct MoneyBundle
{
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer
{
    string customerName;
    string transactionType;
};


class MoneyStack
{
private:
    MoneyBundle* top;
public:
    MoneyStack() {
        top = nullptr;
    }

    void push(string serial, string currency, int b100, int b50, int b20) {
        MoneyBundle* newBundle = new MoneyBundle();
        newBundle->serialNumber = serial;
        newBundle->currencyType = currency;
        newBundle->billCounts[0] = b100;
        newBundle->billCounts[1] = b50;
        newBundle->billCounts[2] = b20;
        
        newBundle->next = top;
        top = newBundle;
        cout << "-> Money bundle [" << serial << "] added to the safe." << endl;
    }

    bool isEmpty(){
        return top == nullptr;
    }

    MoneyBundle* pop(){
        if(isEmpty()){
            return nullptr;
        }
        MoneyBundle* temp = top;
        top = top->next;
        return temp;
    }

    void display(){
        cout << "Money Bundles in the Safe (Stack)" << endl;
        if(isEmpty()){
            cout << "The safe is empty" << endl;
            return;
        }
        MoneyBundle* current = top;
        while (current != nullptr)
        {
            cout << "Serial = " << current->serialNumber << "\n Currency = " <<
            current->currencyType << "\n Bills = " << current->billCounts[0] << "/" 
            << current->billCounts[1] << "/" << current->billCounts[2] << endl;
        }
    }
};

const int MAX_SIZE = 5;

class CustomerQueue{
private:
    Customer queue[MAX_SIZE];
    int front;
    int rear;
    int count;
public:
    CustomerQueue(){
        front = -1;
        rear = -1;
        count = 0;
    }

    bool isFull(){
        return count == MAX_SIZE;
    }
    
    bool isEmpty(){
        return count == 0;
    }

    void enqueue(string name, string type){
        if(isFull()){
            cout << "Queue is full. Customer " << name << " can not join the line." << endl;
            return;
        }

        if (isEmpty()){
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX_SIZE;
        }

        queue[rear].customerName = name;
        queue[rear].transactionType = type;
        count++;
        cout << "Customer " << name << " joined the line for a " << type << "." << endl;
    }

    Customer dequeue(){
        Customer emptyCustomer = {"", ""};
        if(isEmpty()){
            return emptyCustomer;
        }

        Customer servedCustomer = queue[front];

        if(front == rear){
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }

        count--;
        return servedCustomer;
    }

    void display(){
        cout << "Customers waiting in the line (Queue)" << endl; 
        if (isEmpty()){
            cout << "No customers waiting." << endl;
            return;
        } 

        int i = front;
        for (int c = 0; c < count; c++){
            cout << c + 1 << ".Name: " << queue[i].customerName
            << " / Transaction: " << queue[i].transactionType << endl;
            i = (i+1) % MAX_SIZE;
        }
    }
};


int main(){
    MoneyStack safe;
    CustomerQueue line;
    int choice;
    bool exit = false;
    while(!exit){
        cout << "Bank Management System \n 1. Receive Money \n 2. New Customer \n 3. Process Transaction \n 4. Display Status \n 5. Exit \n Enter your choice:" << endl;
        cin >> choice;

        switch(choice){
            case 1: {
                string serial, currency;
                int b100, b50, b20;
                cout << "Enter serial number: " << endl;
                cin >> serial;
                cout << "Enter currency number: " << endl;
                cin >> currency;
                cout << "Enter quantity of 100s, 50s and 20s" << endl;
                cin >> b100 >> b50 >> b20;
                safe.push(serial, currency, b100, b50, b20);
                break; }
            case 2: {
                string name, type;
                cout << "Enter customer name: " << endl;
                cin >> name;
                cout << "Enter transaction type: " << endl;
                cin >> type;
                line.enqueue(name, type);
                break; }
            case 3: {
            if (line.isEmpty()) {
                cout << "-> No customers to serve in the queue." << endl;
            } else if (safe.isEmpty()) {
                cout << "-> Cannot process! The safe is empty. Please receive money first." << endl;
            } else {
                Customer served = line.dequeue();
                MoneyBundle* usedMoney = safe.pop();

                cout << "\n-> PROCESSING TRANSACTION..." << endl;
                cout << "Serving Customer: " << served.customerName << " (" << served.transactionType << ")" << endl;
                cout << "Using Money Bundle: " << usedMoney->serialNumber << " (" << usedMoney->currencyType << ")" << endl;
                cout << "-> Transaction Complete!" << endl;
                delete usedMoney; 
            }
            break;
            }
            case 4:
                safe.display();
                line.display();
                break;
            case 5:
                cout << "Exiting." << endl;
                exit = 1;
                break;
            default:
                cout << "Invalid choice. " << endl;
        }
    }
}