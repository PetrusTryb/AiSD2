#pragma once
template <class T>
class PriorityQueue
{
private:
	T* heap;
	int* priorities;
	int capacity;
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
	int count;
	PriorityQueue() {
		count = 0;
		capacity = 1000;
		heap = new T[capacity]{};
		priorities = new int[capacity] {};
	}
	~PriorityQueue() {
		delete[] heap;
		delete[] priorities;
	}
	void Insert(T& data, int priority) {
		if (count == capacity) {
			T* temp = new T[capacity * 2]{};
			int* temp2 = new int[capacity * 2] {};
			for (int i = 0; i < capacity; i++) {
				temp[i] = heap[i];
				temp2[i] = priorities[i];
			}
			delete[] heap;
			delete[] priorities;
			heap = temp;
			priorities = temp2;
			capacity *= 2;
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
};

