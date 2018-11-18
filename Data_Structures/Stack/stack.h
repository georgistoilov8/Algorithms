/*
Author: Georgi Stoilov
*/

#ifndef STACK_INCLUDED
#define STACK

template <typename T>
class Stack {
	int size;
	int capacity;
	T* data;
	T* top_;
public:
	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& rhs);
	~Stack();

	// Member functions:
	bool empty() const;
	int get_size() const;
	T& top() const;
	void push(const T& element);
	void pop();

	// Help functions:
	void copy(const Stack& other);
	void clear();
	void resize();
};

template <typename T>
Stack<T>::Stack()
	:size(0), capacity(4),
	data(nullptr), top_(nullptr) {
	data = new T[capacity];
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
	copy(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

template <typename T>
Stack<T>::~Stack() {
	clear();
}

// Help functions:
template <typename T>
void Stack<T>::clear() {
	delete[] data;
	top_ = nullptr;
	size = 0;
	capacity = 4;
}

template <typename T>
void Stack<T>::copy(const Stack<T>& other) {
	data = new T[other.capacity];
	capacity = other.capacity;
	size = other.size;
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
	top_ = &data[size - 1];
}

template <typename T>
void Stack<T>::resize() {
	T* temp = new T[capacity * 2];
	capacity *= 2;
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}
	top_ = &temp[size - 1];
	delete[] data;
	data = temp;
}

// Member functions:
template <typename T>
bool Stack<T>::empty() const {
	return size == 0;
}

template <typename T>
int Stack<T>::get_size() const {
	return size;
}

template <typename T>
T& Stack<T>::top() const {
	return *top_;
}

template <typename T>
void Stack<T>::push(const T& element) {
	if (size >= capacity) {
		resize();
	}
	data[size] = element;
	top_ = &data[size];
	size++;
}

template <typename T>
void Stack<T>::pop() {
	if (!empty()) {
		size--;
		top_ = &data[size - 1];
	}
}
#endif // !STACK_INCLUDED

