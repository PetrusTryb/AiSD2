#pragma once
template <class V>
class Array {
private:
    int ARRAY_BLOCK_SIZE = 10;
    V* data = nullptr;
    int maxLength;
    int currentLength;
public:
    Array() {
        data = new V[ARRAY_BLOCK_SIZE]{};
        maxLength = ARRAY_BLOCK_SIZE;
        currentLength = 0;
    }
    Array(int size) {
        data = new V[size]{};
        maxLength = size;
        currentLength = size;
    }
    Array(const Array& arr) {
        data = new V[arr.maxLength]{};
        maxLength = arr.maxLength;
        currentLength = arr.currentLength;
        for (int i = 0; i < currentLength; i++) {
            data[i] = arr.data[i];
        }
    }
    Array& operator=(const Array& arr) {
        if (this == &arr)
            return *this;
        delete[] data;
        data = new V[arr.maxLength]{};
        maxLength = arr.maxLength;
        currentLength = arr.currentLength;
        for (int i = 0; i < currentLength; i++) {
            data[i] = arr.data[i];
        }
        return *this;
    }

    ~Array() {
        delete[] data;
    }

    void Add(const V& c) {
        if (currentLength == maxLength) {
            V* temp = new V[maxLength + ARRAY_BLOCK_SIZE]{};
            for (int i = 0; i < currentLength; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            maxLength += ARRAY_BLOCK_SIZE;
        }
        data[currentLength] = c;
        currentLength++;
    }

    V& operator[](const int index) const {
        return data[index];
    }

    bool operator==(Array& str) const {
        if (currentLength != str.Size())
            return false;
        for (int i = 0; i < currentLength; i++)
            if (str[i] != data[i]) {
                return false;
            }
        return true;
    }

    int ToInt() const {
        int x = 0;
        for (int i = 0; i < currentLength; i++) {
            int temp = data[i] - '0';
            x *= 10;
            x += temp;
        }
        return x;
    }

    char* ToValidString() {
        return (char*)data;
    }

    int Size() const {
        return currentLength;
    }

    void Resize(int size) {
        V* temp = new V[size]{};
        for (int i = 0; i < currentLength && i < size; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        maxLength = size;
        currentLength = size;
    }

    void Clear() {
        delete[] data;
        data = new V[ARRAY_BLOCK_SIZE]{};
        maxLength = ARRAY_BLOCK_SIZE;
        currentLength = 0;
    }

};

typedef Array<char> String;