#pragma once

#ifndef QUEUE_ARRAY_HEADER
#define QUEUE_ARRAY_HEADER

template <typename T>
class Queue {
		size_t front;		// First element in the queue.
		size_t back;		// One element after the last one.
		size_t size;
		T* data;

	public:
		Queue();
		Queue(const Queue<T>& other);
		Queue& operator=(const Queue<T>& rhs);
		~Queue();

		bool empty() const;
		void push(const T& element);
		void pop();

		T& get_front();
	private:
		void clear();
		void copy(const Queue<T>& other);
		void resize();
};

template <typename T>
Queue<T>::Queue():front(0), back(0), size(4), data(nullptr) {
	data = new T[size];
}

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
bool Queue<T>::empty() const {
	return front == back;
}

template <typename T>
void Queue<T>::push(const T& element) {
	if ((back + 1) % size == front) {
		resize();
	}
	if (empty()) {
		data[front] = element;
	}
	else {
		data[back] = element;
	}
	back = (back + 1) % size;
}

template <typename T>
void Queue<T>::pop() {
	if (empty()) {
		std::cout << "Queue is empty.\n" << std::endl;
	}
	front = (front + 1) % size;
}

template <typename T>
T& Queue<T>::get_front() {
	return data[front];
}

template <typename T>
void Queue<T>::clear() {
	delete[] data;
	size = 4;
	front = 0;
	back = 0;
}

template <typename T>
void Queue<T>::copy(const Queue<T>& other) {
	data = new T[other.size];
	size = other.size;
	front = other.front;
	back = other.back;
	size_t count = 0;
	while (front != back) {
		data[count++] = other.data[front];
		front = (front + 1) % size;
	}

	front = 0;
	back = count;
}

template <typename T>
void Queue<T>::resize() {
	T* temp = new T[size * 2];
	size_t count = 0;
	while (front != back) {
		temp[count++] = data[front];
		front = (front + 1) % size;
	}
	delete[] data;
	data = temp;
	size *= 2;
	front = 0;
	back = count;
}

#endif // !QUEUE_ARRAY_HEADER
