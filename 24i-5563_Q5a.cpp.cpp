#include <iostream>
#include <string>
using namespace std;
struct Node {
    char cdata;
    int idata;
    bool isChar;
    Node* next;

    Node(char c) {
        cdata = c;
        idata = 0;
        isChar = true;
        next = NULL;
    }

    Node(int i) {
        cdata = '\0';
        idata = i;
        isChar = false;
        next = NULL;
    }
};

class LinkedListStack {
private:
    Node* top;

public:
    LinkedListStack() {
        top = NULL;
    }

    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    void pushInt(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    char popChar() {
        if (!top || !top->isChar) return '\0';
        char val = top->cdata;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    int popInt() {
        if (!top || top->isChar) return -1;
        int val = top->idata;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return top == NULL;
    }

    ~LinkedListStack() {
        while (top != NULL) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

class ArrayStack {
private:
    int top;
    int capacity;
    char* cArr;
    int* iArr;

public:
    ArrayStack(int size = 100) {
        top = -1;
        capacity = size;
        cArr = new char[size];
        iArr = new int[size];
    }

    void push(char val) {
        if (top == capacity - 1) return;
        cArr[++top] = val;
    }

    void pushInt(int val) {
        if (top == capacity - 1) return;
        iArr[++top] = val;
    }

    char popChar() {
        if (top < 0) return '\0';
        return cArr[top--];
    }

    int popInt() {
        if (top < 0) return -1;
        return iArr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    ~ArrayStack() {
        delete[] cArr;
        delete[] iArr;
    }
};

void ChangeLocationIterative_LinkedList(char arr[], int b1, int b2) {
    LinkedListStack stack;
    for (int i = b1; i <= b2; i++)
        stack.push(arr[i]);

    for (int i = b1; i <= b2; i++)
        arr[i] = stack.popChar();
}

void ChangeLocationIterative_ArrayStack(char arr[], int b1, int b2) {
    ArrayStack stack(b2 - b1 + 1);
    for (int i = b1; i <= b2; i++)
        stack.push(arr[i]);

    for (int i = b1; i <= b2; i++)
        arr[i] = stack.popChar();
}

void PrintPattern_LinkedListStack(int n) {
    cout << "\nPattern using Linked List Stack:\n";
    int arr[100];
    int size = 1;
    arr[0] = n;

    while (true) {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;

        int i;
        for (i = size - 1; i >= 0; i--)
            if (arr[i] > 1) break;

        if (i < 0) break;

        arr[i]--;
        int total = 0;
        for (int j = 0; j <= i; j++)
            total += arr[j];

        while (total < n)
            arr[++i] = 1, total++;

        size = i + 1;
    }
}

void PrintPattern_ArrayStack(int n) {
    cout << "\nPattern using Array Stack:\n";
    int arr[100];
    int size = 1;
    arr[0] = n;

    while (true) {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;

        int i;
        for (i = size - 1; i >= 0; i--)
            if (arr[i] > 1) break;

        if (i < 0) break;

        arr[i]--;
        int total = 0;
        for (int j = 0; j <= i; j++)
            total += arr[j];

        while (total < n)
            arr[++i] = 1, total++;

        size = i + 1;
    }
}


int main() {
    char arr[8] = {'C', 'O', 'M', 'P', 'U', 'T', 'E', 'R'};
    int b1 = 3, b2 = 7;

    cout << "Original Array: ";
    for (int i = 0; i < 8; i++) cout << arr[i] << " ";
    cout << endl;

    ChangeLocationIterative_LinkedList(arr, b1, b2);
    cout << "After LinkedListStack reverse: ";
    for (int i = 0; i < 8; i++) cout << arr[i] << " ";
    cout << endl;

    ChangeLocationIterative_ArrayStack(arr, b1, b2);
    cout << "After ArrayStack reverse (restored): ";
    for (int i = 0; i < 8; i++) cout << arr[i] << " ";
    cout << endl;

    int n = 4;
    PrintPattern_LinkedListStack(n);
    PrintPattern_ArrayStack(n);

    return 0;
}

