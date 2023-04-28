#pragma once
#include <stdio.h>
template <class T>
class PriorityQueue
{
	private:
		struct Node
		{
		int priority;
		T data;
		Node* next;
	};
	Node* head;
	int count;
public:
	PriorityQueue() {
		head = nullptr;
		count = 0;
	}
	~PriorityQueue() {
		Clear();
	}
	void Enqueue(T data, int priority) {
		Node* temp = new Node;
		temp->data = data;
		temp->priority = priority;
		temp->next = nullptr;
		if (head == nullptr) {
			head = temp;
		}
		else {
			Node* current = head;
			while (current->next != nullptr && current->next->priority < priority) {
				current = current->next;
			}
			temp->next = current->next;
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

