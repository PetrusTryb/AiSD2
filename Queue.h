#pragma once
template <class T>
class Queue
{
private:
	struct Node
	{
		T data;
		Node* next;
	};
	Node* head;
	int count;
public:
	Queue() {
		head = nullptr;
		count = 0;
	}
	~Queue() {
		Clear();
	}
	void Enqueue(const T& data) {
		Node* temp = new Node;
		temp->data = data;
		temp->next = nullptr;
		if (head == nullptr) {
			head = temp;
		}
		else {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = temp;
		}
		count++;
	}
	T Dequeue() {
		count--;
		Node* temp = head;
		head = head->next;
		T data = temp->data;
		delete temp;
		return data;
	}
	int Count() {
		return count;
	}
	void Clear() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		count = 0;
		head = nullptr;
	}
};