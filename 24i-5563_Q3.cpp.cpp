#include <iostream>
#include <string>
using namespace std;

struct Node {
    int BookID;
    string Title;
    string Author;
    Node* prev;
    Node* next;

    Node(int id, string title, string author) {
        BookID = id;
        Title = title;
        Author = author;
        prev = NULL;
        next = NULL;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = NULL;
        tail = NULL;
    }

    void addAtBeginning(int id, string title, string author) {
        Node* newNode = new Node(id, title, author);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void addAtEnd(int id, string title, string author) {
        Node* newNode = new Node(id, title, author);
        if (tail == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void addAtPosition(int position, int id, string title, string author) {
        if (position <= 1) {
            addAtBeginning(id, title, author);
            return;
        }

        Node* temp = head;
        int count = 1;

        while (temp != NULL && count < position - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL || temp->next == NULL) {
            addAtEnd(id, title, author);
            return;
        }

        Node* newNode = new Node(id, title, author);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }

    void deleteByID(int id) {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;

        while (temp != NULL && temp->BookID != id) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Book with ID " << id << " not found.\n";
            return;
        }

        if (temp == head && temp == tail) {
            head = tail = NULL;
        } else if (temp == head) {
            head = head->next;
            head->prev = NULL;
        } else if (temp == tail) {
            tail = tail->prev;
            tail->next = NULL;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Book with ID " << id << " deleted.\n";
    }

    void displayForward() {
        Node* temp = head;
        if (temp == NULL) {
            cout << "List is empty.\n";
            return;
        }

        cout << "\nBooks (Forward Order):\n";
        while (temp != NULL) {
            cout << "ID: " << temp->BookID 
                 << ", Title: " << temp->Title 
                 << ", Author: " << temp->Author << endl;
            temp = temp->next;
        }
    }

    void displayBackward() {
        Node* temp = tail;
        if (temp == NULL) {
            cout << "List is empty.\n";
            return;
        }

        cout << "\nBooks (Reverse Order):\n";
        while (temp != NULL) {
            cout << "ID: " << temp->BookID 
                 << ", Title: " << temp->Title 
                 << ", Author: " << temp->Author << endl;
            temp = temp->prev;
        }
    }

    ~DoublyLinkedList() {
        Node* temp = head;
        while (temp != NULL) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = NULL;
    }
};

int main() {
    DoublyLinkedList library;

    library.addAtEnd(101, "The Martian", "Andy Weir");
    library.addAtEnd(102, "Dune", "Frank Herbert");
    library.addAtBeginning(100, "1984", "George Orwell");
    library.addAtPosition(2, 150, "Foundation", "Isaac Asimov");

    library.displayForward();
    library.displayBackward();

    library.deleteByID(102);
    library.displayForward();

    return 0;
}

