#pragma once
#include "Array.h"
template <class K, class V>
class HashTable
{
private:
    const unsigned int SIZE = 1749900;
    int count;
    V* table = new V[SIZE]{};
    int maxIndex = 0;
    unsigned int hash(K& input) {
        unsigned int h = 0;
        for (int i = 0; i < (int)input.Size(); i++) {
            h += input[i];
            h *= 0x5bd1e995;
            h ^= input[i] >> 15;
        }
        if (h % SIZE > maxIndex)
            maxIndex = h % SIZE;
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
        //if(used[index])
        //        printf("Collision detected!\n");
        table[index] = value;
        //used[index] = true;
        count++;
    }
    V& operator[](K& key) {
        int index = hash(key);
        return table[index];
    }
    void Shrink() {
        V* temp = new V[maxIndex + 1]{};
        for (int i = 0; i < maxIndex + 1; i++) {
            temp[i] = table[i];
        }
        delete[] table;
        table = temp;
    }
    int Count() {
		return count;
	}
};