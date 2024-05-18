#include <iostream>
using namespace std;

template<class T>
class LinkedList {
public:
    class Node {
    public:
        Node() : next(nullptr), data(0) {}
        Node(T d) : next(nullptr), data(d) {}
        Node(Node *n) : next(n), data(0) {}
        Node(Node *n, T d) : next(n), data(d) {}
        T data;
        Node *next;
    };

    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool addFromHead(T d) {
        if (!head) {
            head = new Node(d);
        } else {
            head = new Node(head, d);
        }
        return true;
    }

    bool addFromTail(T d) {
        if (!head) {
            head = new Node(d);
        } else {
            Node *current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new Node(d);
        }
        return true;
    }

    bool removeFromHead() {
        if (!head) return false;
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    bool removeFromTail() {
        if (!head) return false;
        if (!head->next) {
            delete head;
            head = nullptr;
            return true;
        }
        Node *current = head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        return true;
    }

    size_t getSize() const {
        size_t size = 0;
        Node *current = head;
        while (current) {
            size++;
            current = current->next;
        }
        return size;
    }

    bool searchData(T d) const {
        Node *current = head;
        while (current) {
            if (current->data == d) return true;
            current = current->next;
        }
        return false;
    }

    T operator[](int i) const {
        Node *current = head;
        int count = 0;
        while (current) {
            if (count == i) return current->data;
            count++;
            current = current->next;
        }
        throw out_of_range("Index out of range");
    }

    friend ostream &operator<<(ostream &o, LinkedList *l) {
        Node *current = l->head;
        o << "{";
        while (current) {
            o << current->data;
            if (current->next) o << ", ";
            current = current->next;
        }
        o << "}";
        return o;
    }

protected:
    Node *head;
};

template<class T>
class Set : private LinkedList<T> {
public:
    Set() : LinkedList<T>() {}

    bool addElement(T d) {
        if (this->searchData(d)) return false;
        this->addFromTail(d);
        return true;
    }

    friend ostream &operator<<(ostream &o, Set<T> *s) {
        typename LinkedList<T>::Node *current = s->head;
        o << "{";
        bool first = true;
        while (current) {
            if (!first) o << ", ";
            o << current->data;
            first = false;
            current = current->next;
        }
        o << "}\n";
        return o;
    }

    Set<T>* operator+(Set<T> *s) {
        Set<T> *result = new Set<T>();
        typename LinkedList<T>::Node *current = this->head;
        while (current) {
            result->addElement(current->data);
            current = current->next;
        }
        current = s->head;
        while (current) {
            result->addElement(current->data);
            current = current->next;
        }
        return result;
    }

    Set<T>* operator-(Set<T> *s) {
        Set<T> *result = new Set<T>();
        typename LinkedList<T>::Node *current = this->head;
        while (current) {
            if (!s->searchData(current->data)) {
                result->addElement(current->data);
            }
            current = current->next;
        }
        return result;
    }

    Set<T>* operator*(Set<T> *s) {
        Set<T> *result = new Set<T>();
        typename LinkedList<T>::Node *current = this->head;
        while (current) {
            if (s->searchData(current->data)) {
                result->addElement(current->data);
            }
            current = current->next;
        }
        return result;
    }
};

int main() {
    Set<int> s1;
    s1.addElement(4);
    s1.addElement(5);
    cout << &s1;

    Set<int> s2;
    s2.addElement(5);
    s2.addElement(6);

    Set<int>* s3 = s1 + &s2;
    cout << s3;

    Set<int>* s4 = s1 - &s2;
    cout << s4;

    Set<int>* s5 = s1 * &s2;
    cout << s5;

    delete s3;
    delete s4;
    delete s5;

    return 0;
}
