#pragma once

#ifndef QUEUE_HEADER
#define QUEUE

template <typename T>
struct Node {
	T data;
	Node<T>* previous;
	Node<T>* next;

	Node(const T& new_data): data(new_data), previous(nullptr), next(nullptr){}
};

template <typename T>
class Queue { 
	Node<T>* front;
	Node<T>* back;

public:
	Queue():front(nullptr), back(nullptr){}
	
	Queue(const Queue& other) {
		copyFrom(other);
	}
	
	Queue& operator=(const Queue& rhs) {
		if (this != &rhs) {
			clear();
			copyFrom(other);
		}
	}
	
	~Queue() {
		clear();
	}

	void copyFrom(const Queue& other) {
		
	}

	void clear() {
		while (front->next) {
			Node<T>* temp = front;
			front = front->next;
			delete temp;
		}
		front = nullptr;
		back = nullptr;
	}
};

#endif // !QUEUE_HEADER
