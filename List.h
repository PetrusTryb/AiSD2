#pragma once
#include <stdio.h>
#include "Array.h"
template <class T>
class List
{
private:
    const static int LIST_BLOCK_SIZE = 17;
    int nodes;
    int overallElements;
    struct Node
    {
        T* Value[LIST_BLOCK_SIZE] = {};
        Node* Next = nullptr;
        Node* Prev = nullptr;
        int elements = 0;
    };
    Node* head;
    Node* tail;
public:
    List() {
        nodes = 0;
        overallElements = 0;
        head = nullptr;
        tail = nullptr;
    }
    List(const List& list) {
        nodes = 0;
        overallElements = 0;
        head = nullptr;
        tail = nullptr;
        Node* n = list.head;
        while (n != nullptr) {
            for (int i = 0; i < n->elements; i++) {
                Add(*(n->Value[i]));
            }
            n = n->Next;
        }
    }
    List& operator=(const List& list) {
        if (this == &list)
            return *this;
        Clear();
        Node* n = list.head;
        while (n != nullptr) {
            for (int i = 0; i < n->elements; i++) {
                Add((n->Value[i]));
            }
            n = n->Next;
        }
        return *this;
    }
    ~List() {
        Clear();
    }
    void Add(T value) {
        if (nodes == 0) {
            Node* n = new Node;
            n->Value[0] = new T(value);
            n->elements++;
            head = n;
            tail = n;
            nodes++;
        }
        else if (tail->elements == LIST_BLOCK_SIZE) {
            Node* n = new Node;
            n->Value[0] = new T(value);
            n->elements++;
            tail->Next = n;
            n->Prev = tail;
            tail = n;
            nodes++;
        }
        else {
            tail->Value[tail->elements] = new T(value);
            tail->elements++;
        }
        overallElements++;
    }
    T* Get(String& key, bool comparator(T&, String&)) const {
        Node* n = tail;
        while (n != nullptr) {
            for (int i = n->elements - 1; i >= 0; i--) {
                if (comparator(*(n->Value[i]), key)) {
                    return n->Value[i];
                }
            }
            n = n->Prev;
        }
        return nullptr;
    }
    T* operator[](const int& index) const {
        if (index > overallElements) {
            return nullptr;
        }
        int i = 0;
        Node* n = head;
        while (n != nullptr) {
            for (int j = 0; j < n->elements; j++) {
                if (i + n->elements < index) {
                    i += n->elements;
                    break;
                }
                if (i == index) {
                    return n->Value[j];
                }
                i++;
            }
            n = n->Next;
        }
        return nullptr;
    }
    int Count() const {
        return overallElements;
    }
    int Count(String& key, bool comparator(T&, String&)) const {
        int count = 0;
        Node* n = tail;
        while (n != nullptr) {
            for (int i = 0; i < n->elements; i++) {
                if (comparator(*(n->Value[i]), key))
                    count++;
            }
            n = n->Prev;
        }
        return count;
    }
    bool HasElement(String& key, bool comparator(T&, String&)) const {
        Node* n = tail;
        while (n != nullptr) {
            for (int i = 0; i < n->elements; i++) {
                if (comparator(*(n->Value[i]), key))
                    return true;
            }
            n = n->Prev;
        }
        return false;
    }
    int Remove(const int& index) {
        if (index > overallElements) {
            return -1;
        }
        int i = 0;
        Node* n = head;
        while (n != nullptr) {
            for (int j = 0; j < n->elements; j++) {
                if (i + n->elements < index) {
                    i += n->elements;
                    break;
                }
                if (i == index) {
                    delete n->Value[j];
                    for (int k = j; k < n->elements - 1; k++) {
                        n->Value[k] = n->Value[k + 1];
                    }
                    n->elements--;
                    overallElements--;
                    if (n->elements == 0) {
                        if (n->Prev != nullptr)
                            n->Prev->Next = n->Next;
                        else
                            head = n->Next;
                        if (n->Next != nullptr)
                            n->Next->Prev = n->Prev;
                        else
                            tail = n->Prev;
                        delete n;
                        nodes--;
                    }
                    return overallElements;
                }
                i++;
            }
            n = n->Next;
        }
        return -1;
    }
    int Remove(String& key, bool comparator(T&, String&)) {
        Node* n = tail;
        while (n != nullptr) {
            for (int i = 0; i < n->elements; i++) {
                if (comparator(*(n->Value[i]), key)) {
                    delete n->Value[i];
                    for (int j = i; j < n->elements - 1; j++) {
                        n->Value[j] = n->Value[j + 1];
                    }
                    n->elements--;
                    overallElements--;
                    if (n->elements == 0) {
                        if (n->Prev != nullptr)
                            n->Prev->Next = n->Next;
                        else
                            head = n->Next;
                        if (n->Next != nullptr)
                            n->Next->Prev = n->Prev;
                        else
                            tail = n->Prev;
                        delete n;
                        nodes--;
                    }
                    return overallElements;
                }
            }
            n = n->Prev;
        }
        return -1;
    }
    void Clear() {
        Node* n = head;
        while (n != nullptr) {
            Node* temp = n;
            n = n->Next;
            for (int i = 0; i < temp->elements; i++)
                delete temp->Value[i];
            delete temp;
        }
        nodes = 0;
        overallElements = 0;
        head = nullptr;
        tail = nullptr;
    }
};