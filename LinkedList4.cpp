#include <iostream>

using namespace std;

// Define the structure of a Node
struct Node {
    int data;
    Node* link;
};

// Function prototypes
Node* createNode(int num);
int searchValue(Node* p, int target);
void insertAtEnd(Node*& p, int num);
void removeValue(Node*& p, int target, int& counter);
void reverseList(Node*& p);
void sortList(Node*& p);
void displayList(Node* p);
void displayListWithPosition(Node* p);

int main() {
    Node* p = nullptr; // Initialize p to point to the first node
    int num, counter = 0, choice;

    // Accept data from the user
    cout << "Add to linked list (enter 0 to end):" << endl;
    while (true) {
        cout << "Enter number: ";
        cin >> num;
        if (num == 0) break;
        insertAtEnd(p, num); // Use insertAtEnd
        counter++;
    }

    // Display the original linked list
    cout << "Original linked list:" << endl;
    displayListWithPosition(p);

    do {
        cout << "\nMenu:\n";
        cout << "1. Reverse linked list\n";
        cout << "2. Search for a value\n";
        cout << "3. Remove a value\n";
        cout << "4. Sort linked list\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                reverseList(p);
                cout << "Linked list reversed." << endl;
                displayList(p);
                cout << "Original linked list with positions:" << endl;
                displayListWithPosition(p);
                break;
            case 2: {
                int target;
                cout << "Enter a value to search for: ";
                cin >> target;
                int position = searchValue(p, target);
                if (position != -1) {
                    cout << "Value " << target << " found at Node: " << position << endl;
                }
				else {
                    cout << "Value " << target << " not found in the linked list." << endl;
                }
                break;
            }
            case 3: {
                int target;
                cout << "Enter a value to remove: ";
                cin >> target;
                removeValue(p, target, counter);
                cout << "Original linked list with positions:" << endl;
                displayListWithPosition(p);
                break;
            }
            case 4:
                sortList(p);
                cout << "Linked list sorted." << endl;
                cout << "Original linked list with positions:" << endl;
                displayListWithPosition(p);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } 
	while (choice != 0);

    cout << "Total number of nodes: " << counter << endl;

    return 0;
}

// Function definitions
Node* createNode(int num) {
    Node* temp = new Node();
    temp->data = num;
    temp->link = nullptr;
    return temp;
}

void insertAtEnd(Node*& p, int num) {
    Node* temp = createNode(num);
    if (p == nullptr) { // If the list is empty
        p = temp;
    } else {
        Node* current = p;
        while (current->link != nullptr) { // Traverse to the end
            current = current->link;
        }
        current->link = temp; // Link the new node at the end
    }
}


int searchValue(Node* p, int target) {
    Node* q = p;
    int position = 0;
    while (q != nullptr) {
        if (q->data == target) {
            return position; // Return the position if found
        }
        q = q->link;
        position++;
    }
    return -1; // Return -1 if not found
}

void removeValue(Node*& p, int target, int& counter) {
    Node* prev = nullptr;
    Node* current = p;

    while (current != nullptr) {
        if (current->data == target) {
            if (prev == nullptr) {
                p = current->link;
            }
			else {
                prev->link = current->link;
            }
            delete current; // Free memory
            counter--;
            return; // Value found and removed
        }
        prev = current;
        current = current->link;
    }

    cout << "Value " << target << " not found in the linked list." << endl;
}

void reverseList(Node*& p) {
    Node* prev = nullptr;
    Node* current = p;
    Node* next;

    while (current != nullptr) {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }

    p = prev; // Update the head pointer
}

void sortList(Node*& p) {
    bool swapped;
    Node* ptr1;
    Node* lptr = nullptr;

    if (p == nullptr)
        return;

    do {
        swapped = false;
        ptr1 = p;

        while (ptr1->link != lptr) {
            if (ptr1->data > ptr1->link->data) {
                swap(ptr1->data, ptr1->link->data);
                swapped = true;
            }
            ptr1 = ptr1->link;
        }
        lptr = ptr1;
    } 
	while (swapped);
}

void displayList(Node* p) {
    Node* q = p;
    while (q != nullptr) {
        cout << q->data << "->";
        q = q->link;
    }
    cout << "null" << endl;
}

void displayListWithPosition(Node* p) {
    Node* q = p;
    int position = 0;
    while (q != nullptr) {
        cout << "Node [" << position << "]: " << q->data << " ----> ";
        q = q->link;
        position++;
    }
    cout << "null" << endl;
}