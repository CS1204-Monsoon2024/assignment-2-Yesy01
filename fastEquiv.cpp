#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;   // Pointer to the head of the linked list
    int size;     // Current size of the linked list
    long long listHash; // Hash value representing the entire list
    
    // A simple hash function for combining hash values (can be improved)
    long long computeHash(int value) {
        return value * 31; // A simple hash combining function (use primes)
    }

public:
    LinkedList() {
        head = nullptr;
        size = 0;
        listHash = 0; // Initialize hash to zero
    }

    ~LinkedList() {
        // Destructor to free memory
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new element at the front of the list
    void insertFront(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
        // Update the hash value for the entire list
        listHash += computeHash(value); // Add the hash of the new element
    }

    // Delete the element from the front of the list
    void deleteFront() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        // Update the hash by removing the contribution of the current head
        listHash -= computeHash(head->data); // Subtract the hash of the current head
        // Delete the node
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    // Search for an element in the list
    bool search(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Check if two linked lists are equivalent in O(1) time
    bool isEquivalent(LinkedList& other) {
        // Compare both the size and the listHash
        return this->size == other.size && this->listHash == other.listHash;
    }

    // Display the list elements
    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

// Main function to test the LinkedList implementation
int main() {
    LinkedList list1, list2;
    int choice, value;

    // Menu for List 1
    cout << "Choose operations for List 1:" << endl;
    do {
        cout << "1. Insert Front\n2. Delete Front\n3. Search\n4. Display\n5. Exit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            list1.insertFront(value);
            break;
        case 2:
            list1.deleteFront();
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            if (list1.search(value)) {
                cout << "Value found!" << endl;
            } else {
                cout << "Value not found!" << endl;
            }
            break;
        case 4:
            list1.display();
            break;
        case 5:
            cout << "Exiting List 1 operations." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    // Menu for List 2
    cout << "Choose operations for List 2:" << endl;
    do {
        cout << "1. Insert Front\n2. Delete Front\n3. Search\n4. Display\n5. Exit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            list2.insertFront(value);
            break;
        case 2:
            list2.deleteFront();
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            if (list2.search(value)) {
                cout << "Value found!" << endl;
            } else {
                cout << "Value not found!" << endl;
            }
            break;
        case 4:
            list2.display();
            break;
        case 5:
            cout << "Exiting List 2 operations." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    // Check if the two lists are equivalent
    if (list1.isEquivalent(list2)) {
        cout << "Both lists are equivalent!" << endl;
    } else {
        cout << "Lists are not equivalent." << endl;
    }

    return 0;
}
