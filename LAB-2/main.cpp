#include <iostream>
#include <string>
using namespace std;

struct Node{
    string songTitle;
    Node* next;
};

void addSong(Node*& head, string title){
    Node* newNode = new Node();
    newNode->songTitle = title;
    newNode->next = head;
    head = newNode;
    cout << "Node Added";
}

void searchSong(Node* head, string songName){
    if(head == nullptr){
        cout << "List is empty \n";
        return;
    }
    
    Node* current = head;
    bool found = false;
    
    while (current != nullptr){
        if(current->songTitle == songName){
            cout << "Song With The Name " << songName << " Found \n";
            found = true;
            break;
        }
        current = current->next;
    }    
    if(found == false){
        cout << "Song With The Name " << songName << " Not Found \n";
    }
    
}

void listSongs(Node* head){
    if(head == nullptr){
        cout << "List is empty \n";
        return;
    }
    Node* current = head;
    
    while(current != nullptr){
        cout << current->songTitle <<"\n";
        current = current->next;
    }
}


int main(){
    Node* head = nullptr;
    bool leave = 0;
    while(leave == 0){
        int menuOption;
        cout << "1. Add \n2. Search \n3. List \n4. Exit \n";
        cin >> menuOption;
        switch(menuOption){
            case 1: {
                cout << "Enter Song Name \n";
                string songName;
                cin >> songName;
                addSong(head, songName);
                break;
            }
            case 2: {
                cout << "Enter the Song Name You Are Searching For \n";
                string songNameForSearch;
                cin >> songNameForSearch;
                searchSong(head, songNameForSearch);
                break;
            }
            case 3: {
                cout << "Listing songs: \n";
                listSongs(head);
                break;
            }
            case 4: {
                leave = 1;
                break;
            }
        }
    }
}