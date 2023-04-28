#pragma once
#include <math.h>
template <class K, class V>
class HashTable
{
	private:
		const int SIZE = 21374;
		int count;
		V* table = new V[SIZE]{};
		int hash(K& value) {
			unsigned long long hash = 0;
			for (int i = 0; i < value.size(); i++) {
				hash += value[i] * pow(26, i);
			}
			hash = llabs(hash % SIZE);
			//if (table[hash])
				//hash++;
			return hash;
		}
	public:
		HashTable() {
			count = 0;
		}
		~HashTable() {
			delete[] table;
		}
		void Insert(K key, V value) {
			int index = hash(key);
			table[index] = value;
			count++;
		}
		void Remove(K key) {
			int index = hash(key);
			table[index] = V();
			count--;
		}
		V& operator[](K key) {
			int index = hash(key);
			return table[index];
		}
};