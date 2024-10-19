#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Node {
public:
    int value;
    unsigned long long hash; // Hash of the suffix starting from this node
    Node* next;

    Node(int value): value(value), hash(0), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    Node* tail;

    static const int m = 1000003;      // Range for h(x)
    static const int p = 31;           // Prime number for polynomial hashing
    static const unsigned long long M = 1000000007;   // Modulus to prevent overflow

    LinkedList(): head(nullptr), tail(nullptr) {}

    void insert(int value);

    Node* search(int key);

    void deleteNode(int key);

    bool equivalence(LinkedList& other);

    void updateHashes();

    unsigned long long getHash() {
        return head ? head->hash : 0;
    }

private:
    static unsigned int h(int x, int m) {
        return (x % m) + 1;
    }
};

void LinkedList::insert(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    // Update hashes
    updateHashes();
}

Node* LinkedList::search(int value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value)
            return current;
        current = current->next;
    }
    return nullptr;
}

void LinkedList::deleteNode(int value) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->value == value) {
            if (prev == nullptr) {
                // Deleting head
                head = current->next;
                if (head == nullptr) tail = nullptr;
            } else {
                prev->next = current->next;
                if (current->next == nullptr) tail = prev;
            }
            delete current;
            // Update hashes
            updateHashes();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void LinkedList::updateHashes() {
    std::vector<Node*> nodes;
    Node* current = head;
    while (current != nullptr) {
        nodes.push_back(current);
        current = current->next;
    }

    unsigned long long hashNext = 0;

    for (int i = nodes.size() - 1; i >= 0; --i) {
        current = nodes[i];
        unsigned int h_i = h(current->value, m);
        current->hash = (h_i + (p * hashNext) % M) % M;
        hashNext = current->hash;
    }
}

bool LinkedList::equivalence(LinkedList& other) {
    if (this->getHash() != other.getHash())
        return false; // Lists are not equivalent

    cout << "Hashes are equal, comparing node by node" << endl;
    // Hashes are equal, compare node by node
    Node* curr1 = this->head;
    Node* curr2 = other.head;

    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->value != curr2->value)
            return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return (curr1 == nullptr && curr2 == nullptr);
}

int main() {
    LinkedList L1;
    LinkedList L2;

    int n1;
    cin >> n1;
    for (int i = 0; i < n1; ++i) {
        int value;
        cin >> value;
        L1.insert(value);
    }

    int n2;
    cin >> n2;
    for (int i = 0; i < n2; ++i) {
        int value;
        cin >> value;
        L2.insert(value);
    }

    if (L1.equivalence(L2)) {
        cout << "Lists are equivalent" << endl;
    } else {
        cout << "Lists are not equivalent" << endl;
    }

    return 0;
}