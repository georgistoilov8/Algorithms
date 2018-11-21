#pragma once

#ifndef QUEUE_LIST_HEADER
#define QUEUE_LIST_HEADER

template <typename T>
class Queue {
	public:
		struct Node {
			Node* ptr_next;
			Node* ptr_previous;
			T data;
			Node() : ptr_next(nullptr), ptr_previous(nullptr) {}
			Node(const T& data) : ptr_next(nullptr), ptr_previous(nullptr), data(data){}
		};
	private:
		Node* front;
		Node* back;
		size_t size;

	public:
		Queue();
		Queue(const Queue<T>& other);
		Queue& operator=(const Queue<T>& rhs);
		~Queue();

		void pop_front();
		void push_back(const T& element);
		T& get_front();

		bool empty() const;
	private:
		void clear();
		void copy(const Queue<T>& other);
};

template <typename T>
Queue<T>::Queue(): front(nullptr), back(nullptr), size(0){}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
	copy(other);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

template <typename T>
Queue<T>::~Queue() {
	clear();
}

template <typename T>
void Queue<T>::push_back(const T& element) {
	Node* new_node = new Node(element);
	if (empty()) {
		front = back = new_node;
	}
	else {
		back->ptr_next = new_node;
		back = back->ptr_next;
	}
	size++;
}

template <typename T>
T& Queue<T>::get_front() {
	return front->data;
}
template <typename T>
void Queue<T>::pop_front() {
	if (empty()) {
		return;
	}

	Node* next_node = front->ptr_next;
	delete front;
	front = next_node;
	size--;
}

template <typename T>
bool Queue<T>::empty() const {
	return size == 0;
}

template <typename T>
void Queue<T>::clear() {
	while (!empty()) {
		pop_front();
	}
	front = nullptr;
	back = nullptr;
	size = 0;
}

template <typename T>
void Queue<T>::copy(const Queue<T>& other) {
	Node* current = other.front;
	while (current) {
		push_back(current->data);
		current = current->ptr_next;
	}
}
#endif // !QUEUE_LIST_HEADER
