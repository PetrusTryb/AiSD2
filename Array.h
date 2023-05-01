#pragma once
#include <cstdio>
template <class V>
class Array {
private:
    int ARRAY_BLOCK_SIZE = 10;
    V* data = nullptr;
    int currentLenght;
    int maxLenght;
public:
    Array() {
        data = new V[ARRAY_BLOCK_SIZE]{};
        maxLenght = ARRAY_BLOCK_SIZE;
        currentLenght = 0;
    }
    Array(int size) {
        data = new V[size]{};
        maxLenght = size;
        currentLenght = size;
    }
    Array(const Array& arr) {
        data = new V[arr.maxLenght]{};
        maxLenght = arr.maxLenght;
        currentLenght = arr.currentLenght;
        for (int i = 0; i < currentLenght; i++) {
            data[i] = arr.data[i];
        }
    }
    Array(const char* arr) {
        int size = 0;
        while (arr[size] != '\0')
            size++;
        data = new V[size]{};
        maxLenght = size;
        currentLenght = size;
        for (int i = 0; i < currentLenght; i++) {
            data[i] = arr[i];
        }
    }
    Array& operator=(const Array& arr) {
        if (this == &arr)
            return *this;
        delete[] data;
        data = new V[arr.maxLenght]{};
        maxLenght = arr.maxLenght;
        currentLenght = arr.currentLenght;
        for (int i = 0; i < currentLenght; i++) {
            data[i] = arr.data[i];
        }
        return *this;
    }

    void operator+=(int i) {
        if (i == 0) {
            Add('0');
            return;
        }
        Array temp;
        while (i > 0) {
            temp.Add((i % 10) + '0');
            i /= 10;
        }
        for (int i = temp.Size() - 1; i >= 0; i--) {
            Add(temp[i]);
        }
    }

    void operator+=(char& c) {
        Add(c);
    }

    void operator+=(const Array& arr) {
        for (int i = 0; i < arr.Size(); i++) {
            Add(arr[i]);
        }
    }

    ~Array() {
        delete[] data;
    }

    void Add(const V& c) {
        if (currentLenght == maxLenght) {
            V* temp = new V[maxLenght + ARRAY_BLOCK_SIZE]{};
            for (int i = 0; i < currentLenght; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            maxLenght += ARRAY_BLOCK_SIZE;
        }
        data[currentLenght] = c;
        currentLenght++;
    }

    V& operator[](const int index) const {
        if (index < 0 || index >= currentLenght)
            throw - 1;
        return data[index];
    }

    void Change(const int index, const V& c) {
        data[index] = c;
    }

    bool operator==(Array& str) const {
        if (currentLenght != str.Size())
            return false;
        for (int i = 0; i < currentLenght; i++)
            if (str[i] != data[i]) {
                return false;
            }
        return true;
    }

    int ToInt() const {
        int x = 0;
        for (int i = 0; i < currentLenght; i++) {
            int temp = data[i] - '0';
            if ((temp < 0 || temp>9))
                throw - 2;
            x *= 10;
            x += temp;
        }
        return x;
    }

    char* ToValidString() {
        return (char*)data;
    }

    int Size() const {
        return currentLenght;
    }

    void Resize(int size) {
		if (size < 0)
			throw - 3;
        V* temp = new V[size]{};
        for (int i = 0; i < currentLenght && i < size; i++) {
			temp[i] = data[i];
		}
        delete[] data;
		data = temp;
		maxLenght = size;
		currentLenght = size;
	}

    void Clear() {
        delete[] data;
        data = new V[ARRAY_BLOCK_SIZE]{};
        maxLenght = ARRAY_BLOCK_SIZE;
        currentLenght = 0;
    }

};

typedef Array<char> String;