#pragma once
#include "Array.h"
template <class K, class V>
class HashTable
{
private:
    const unsigned int SIZE = 1749900;
    int count;
    V* table = new V[SIZE]{};
    unsigned int hash(K& input) {
        unsigned int h = 0;
        for (int i = 0; i < (int)input.Size(); i++) {
            h += input[i];
            h *= 0x5bd1e995;
            h ^= input[i] >> 15;
        }
        return (h) % SIZE;
    }
public:
    HashTable() {
        count = 0;
    }
    ~HashTable() {
        delete[] table;
    }
    void Insert(K& key, V& value) {
        int index = hash(key);
        table[index] = value;
        count++;
    }
    V& operator[](K& key) {
        int index = hash(key);
        return table[index];
    }
    int Count() {
        return count;
    }
};