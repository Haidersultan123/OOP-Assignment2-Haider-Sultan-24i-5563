#include <iostream>
#include <string>
using namespace std;

class Feature {
protected:
    string Name;
public:
    Feature(const string &name) : Name(name) {}
    virtual void analyze() = 0;          
    virtual Feature* clone() const = 0;  
    virtual ~Feature() {}
};


class LandFeature : public Feature {
public:
    LandFeature(const string &name) : Feature(name) {}
    void analyze() override {
        cout << "Land Feature Detected: " << Name << " (e.g., forest, desert, mountain)" << endl;
    }
    Feature* clone() const override {
        return new LandFeature(*this);
    }
};

class WaterFeature : public Feature {
public:
    WaterFeature(const string &name) : Feature(name) {}
    void analyze() override {
        cout << "Water Feature Detected: " << Name << " (e.g., river, ocean, lake)" << endl;
    }
    Feature* clone() const override {
        return new WaterFeature(*this);
    }
};

struct Node {
    int FeatureID;
    Feature* feature;
    Node* next;
    Node(int id, Feature* f) : FeatureID(id), feature(f), next(NULL) {}
};

class SinglyLinkedList {
private:
    Node* head;

    void clear() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp->feature;
            delete temp;
        }
    }

public:
    SinglyLinkedList() : head(NULL) {}

    SinglyLinkedList(const SinglyLinkedList& other) : head(NULL) {
        Node* cur = other.head;
        while (cur) {
            insertAtEnd(cur->FeatureID, cur->feature->clone());
            cur = cur->next;
        }
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* cur = other.head;
            while (cur) {
                insertAtEnd(cur->FeatureID, cur->feature->clone());
                cur = cur->next;
            }
        }
        return *this;
    }

    SinglyLinkedList operator+(const SinglyLinkedList& other) const {
        SinglyLinkedList newList(*this); 
        Node* cur = other.head;
        while (cur) {
            newList.insertAtEnd(cur->FeatureID, cur->feature->clone());
            cur = cur->next;
        }
        return newList;
    }

    void insertAtEnd(int featureID, Feature* f) {
        Node* newNode = new Node(featureID, f);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    void deleteByID(int featureID) {
        if (!head) return;
        if (head->FeatureID == featureID) {
            Node* t = head;
            head = head->next;
            delete t->feature;
            delete t;
            cout << "Feature with ID " << featureID << " deleted.\n";
            return;
        }
        Node* cur = head;
        while (cur->next && cur->next->FeatureID != featureID) cur = cur->next;
        if (cur->next) {
            Node* t = cur->next;
            cur->next = t->next;
            delete t->feature;
            delete t;
            cout << "Feature with ID " << featureID << " deleted.\n";
        } else {
            cout << "Feature with ID " << featureID << " not found.\n";
        }
    }

    void displayAll() const {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        cout << "\n--- Feature List ---\n";
        Node* t = head;
        while (t) {
            cout << "Feature ID: " << t->FeatureID << " -> ";
            t->feature->analyze();
            t = t->next;
        }
        cout << "--------------------\n";
    }

    void reverseList() {
        Node *prev = NULL, *curr = head, *next = NULL;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    ~SinglyLinkedList() {
        clear();
    }
};

int main() {
    SinglyLinkedList list;
    list.insertAtEnd(1, new LandFeature("Forest"));
    list.insertAtEnd(2, new WaterFeature("River"));
    list.insertAtEnd(3, new LandFeature("Mountain"));
    list.insertAtEnd(4, new WaterFeature("Lake"));

    cout << "Initial Feature List:\n";
    list.displayAll();

    list.deleteByID(2);
    cout << "After deletion:\n";
    list.displayAll();

    list.reverseList();
    cout << "After reversing:\n";
    list.displayAll();

   
    SinglyLinkedList list2;
    list2.insertAtEnd(5, new WaterFeature("Ocean"));
    list2.insertAtEnd(6, new LandFeature("Desert"));

    SinglyLinkedList merged = list + list2;
    cout << "Merged list:\n";
    merged.displayAll();

    SinglyLinkedList copied;
    copied = merged;
    cout << "Copied list:\n";
    copied.displayAll();

    return 0;
}

