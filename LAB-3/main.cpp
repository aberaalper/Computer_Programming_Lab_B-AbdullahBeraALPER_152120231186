
#include <iostream>
#include <string>
using namespace std;

struct Page{
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;
    
    Page(string u, string t, int h, int m, int s) {
        url = u;
        title = t;
        accessTime[0] = h;
        accessTime[1] = m;
        accessTime[2] = s;
        next = nullptr;
        prev = nullptr;
    }
};

class BrowserHistory {
    Page* head = nullptr;
    Page* tail = nullptr;
    Page* current = nullptr;
public:
    void visit(string url, string title, int h, int m, int s){
        Page* newPage = new Page(url, title, h, m, s);
        if(!head){
            head = tail = current = newPage;
        } else {
            if(current != tail){
                Page* temp = current->next;
                while(temp){
                    Page* toDelete = temp;
                    temp = temp->next;
                    delete toDelete;
                }
            }
            current->next = newPage;
            newPage->prev = current;
            tail = newPage;
            current = newPage;
        }
        cout << "Visited " << title << "\n";
    }
    
    void back(){
        if(current && current->prev){
            current = current->prev;
            cout << "Going back to " << current->title << "\n";
        } else {
            cout << "Can not go back \n";
        }
    }
    
    void forward(){
        if(current && current->next){
            current = current->next;
            cout << "Going forward to " << current->title << "\n";
        } else {
            cout << "Can not go forward \n";
        }
    }
    
    void deleteEntry(){
        if(!current){
            cout << "History is empty \n";
            return;
        }
        
        Page* toDelete = current;
        cout << "Deleting the page " << toDelete->title << "\n";
        
        if (toDelete->prev) {
            toDelete->prev->next = toDelete->next;
        } else {
            head = toDelete->next;
        }

        if (toDelete->next) {
            toDelete->next->prev = toDelete->prev;
        } else {
            tail = toDelete->prev;
        }
        
        if (toDelete->prev) {
            current = toDelete->prev;
        } else {
            current = toDelete->next;
        }

        delete toDelete;
    }
    
    void displayHistory(){
        if(!head){
            cout << "History is empty \n";
            return;
        }

        cout << "Browser History \n";
        Page* temp = head;
        while(temp){
            if(temp == current){
                cout << "-> ";
            } else {
                cout << "   ";
            }

            cout << "[" << temp->title << "] (" << temp->url << ") - Time: ";
            
            for(int i = 0; i < 3; i++){
                if (temp->accessTime[i] < 10) cout << "0"; 
                cout << temp->accessTime[i];
                if(i < 2) cout << ":"; 
            }
            cout << "\n";
            
            temp = temp->next;
        }
        cout << "\n";
    }
    
    void clearAll(){
        Page* temp = head;
        while(temp){
            Page* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = current = nullptr;
        cout << "Memory cleared \n";
    }
};

int main()
{
    BrowserHistory browser;
    string command;

    cout << "Welcome to Browser History \n";

    while (true) {
        cout << "\nEnter command: \n 1. Visit\n 2. Back \n 3. Forward \n 4. Delete \n 5. Display \n 6. Exit \n ";
        cin >> command;
    for (int i = 0; i < command.length(); i++) {
        command[i] = (command[i]);
    }

        if (command == "1") {
            string url, title;
            int h, m, s;
            cout << "Enter URL: "; cin >> url;
            cout << "Enter Title: "; 
            cin >> ws; 
            getline(cin, title); 
            cout << "Enter Time (HH MM SS): "; cin >> h >> m >> s;
            
            browser.visit(url, title, h, m, s);
        } 
        else if (command == "2") {
            browser.back();
        } 
        else if (command == "3") {
            browser.forward();
        } 
        else if (command == "4") {
            browser.deleteEntry();
        } 
        else if (command == "5") {
            browser.displayHistory();
        } 
        else if (command == "6") {
            browser.clearAll(); 
            break; 
        } 
        else {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}