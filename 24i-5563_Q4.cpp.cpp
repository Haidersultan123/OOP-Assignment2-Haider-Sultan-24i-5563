#include <iostream>
#include <string>
using namespace std;

struct Customer {
    int customerID;
    string name;
    int tickets;
    Customer* next;

    Customer(int id, string n, int t) {
        customerID = id;
        name = n;
        tickets = t;
        next = NULL;
    }
};

class TicketQueue {
private:
    Customer* front;
    Customer* rear;

public:
    TicketQueue() {
        front = NULL;
        rear = NULL;
    }

    void enqueue(int id, string name, int tickets) {
        Customer* newCustomer = new Customer(id, name, tickets);

        if (rear == NULL) {
            front = rear = newCustomer;
        } else {
            rear->next = newCustomer;
            rear = newCustomer;
        }

        cout << "Customer " << name << " (ID: " << id << ") added to the queue.\n";
    }

    void dequeue() {
        if (front == NULL) {
            cout << "Queue is empty. No customer to serve.\n";
            return;
        }

        Customer* temp = front;
        cout << "Serving Customer: " << temp->name 
             << " (ID: " << temp->customerID << "), Tickets: " << temp->tickets << endl;

        front = front->next;
        if (front == NULL)
            rear = NULL;

        delete temp;
    }

    void display() {
        if (front == NULL) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "\nCurrent Queue:\n";
        Customer* temp = front;
        while (temp != NULL) {
            cout << "ID: " << temp->customerID 
                 << ", Name: " << temp->name 
                 << ", Tickets: " << temp->tickets << endl;
            temp = temp->next;
        }
    }

    ~TicketQueue() {
        Customer* temp = front;
        while (temp != NULL) {
            Customer* next = temp->next;
            delete temp;
            temp = next;
        }
        front = rear = NULL;
    }
};

class PriorityTicketQueue {
private:
    Customer* front;

public:
    PriorityTicketQueue() {
        front = NULL;
    }

    void enqueue(int id, string name, int tickets) {
        Customer* newCustomer = new Customer(id, name, tickets);

        if (front == NULL || tickets > front->tickets) {
            newCustomer->next = front;
            front = newCustomer;
        } else {
            Customer* temp = front;
            while (temp->next != NULL && temp->next->tickets >= tickets) {
                temp = temp->next;
            }
            newCustomer->next = temp->next;
            temp->next = newCustomer;
        }

        cout << "Customer " << name << " (ID: " << id 
             << ", Tickets: " << tickets << ") added with priority.\n";
    }

    void dequeue() {
        if (front == NULL) {
            cout << "Priority queue is empty.\n";
            return;
        }

        Customer* temp = front;
        cout << "Serving (Priority) Customer: " << temp->name 
             << " (ID: " << temp->customerID 
             << "), Tickets: " << temp->tickets << endl;

        front = front->next;
        delete temp;
    }

    void display() {
        if (front == NULL) {
            cout << "Priority queue is empty.\n";
            return;
        }

        cout << "\nPriority Queue:\n";
        Customer* temp = front;
        while (temp != NULL) {
            cout << "ID: " << temp->customerID 
                 << ", Name: " << temp->name 
                 << ", Tickets: " << temp->tickets << endl;
            temp = temp->next;
        }
    }

    ~PriorityTicketQueue() {
        Customer* temp = front;
        while (temp != NULL) {
            Customer* next = temp->next;
            delete temp;
            temp = next;
        }
        front = NULL;
    }
};

int main() {
    cout << "===== Movie Ticket Booking Queue =====\n";
    TicketQueue q;

    q.enqueue(101, "Alice", 2);
    q.enqueue(102, "Bob", 4);
    q.enqueue(103, "Charlie", 1);

    q.display();

    cout << endl;
    q.dequeue();

    q.display();
    
    cout << "\n===== Priority Ticket Booking Queue =====\n";
    PriorityTicketQueue pq;
    pq.enqueue(201, "Zara", 5);
    pq.enqueue(202, "Mike", 2);
    pq.enqueue(203, "John", 8);

    pq.display();
    cout << endl;
    pq.dequeue();
    pq.display();

    return 0;
}

