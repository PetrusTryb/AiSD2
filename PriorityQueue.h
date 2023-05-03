#pragma once
#include "Array.h"
template <class T>
class PriorityQueue
{
private:
    Array<T> heap;
    Array<int> priorities;
    int capacity;
    int count;
    void Swap(int i, int j) {
        T temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        int temp2 = priorities[i];
        priorities[i] = priorities[j];
        priorities[j] = temp2;
    }
    void BubbleUp(int index) {
        if (index == 0)
            return;
        int parent = (index - 1) / 2;
        if (priorities[index] < priorities[parent]) {
            Swap(index, parent);
            BubbleUp(parent);
        }
    }
    void BubbleDown(int index) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        if (left >= count)
            return;
        int min = left;
        if (right < count && priorities[right] < priorities[left])
            min = right;
        if (priorities[index] > priorities[min]) {
            Swap(index, min);
            BubbleDown(min);
        }
    }
public:
    PriorityQueue() {
        count = 0;
        heap = Array<T>(1000);
        priorities = Array<T>(1000);
    }
    ~PriorityQueue() {
        
    }
    void Insert(T& data, int priority) {
        if (count == heap.Size()) {
            heap.Resize(heap.Size() * 2);
            priorities.Resize(priorities.Size() * 2);
        }
        heap[count] = data;
        priorities[count] = priority;
        BubbleUp(count);
        count++;
    }
    T Pop() {
        T temp = heap[0];
        heap[0] = heap[count - 1];
        priorities[0] = priorities[count - 1];
        count--;
        BubbleDown(0);
        return temp;
    }
    int Count() const{
        return count;
    }
};