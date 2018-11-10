#include <iostream>
#include <vld.h>

struct Queue {
	int size;
	int front;
	int back;
	int* data;

	Queue() :size(4), front(0), back(0), data(nullptr) {
		data = new int[size];
	}

	~Queue() {
		delete[] data;
		size = 0;
		front = 0;
		back = 0;
	}

	void push(int el) {
		if ( (back + 1) % size == front) {
			resize();
		}
		data[back] = el;
		back = (back + 1) % size;
	}

	void pop() {
		if (empty()) {
			return;
		}
		front = (front + 1) % size;
	}

	int front_() const {
		return data[front];
	}

	void resize() {
		int* temp = new int[ size * 2];
		for (int i = 0; i < size; i++) {
			temp[i] = data[front];
			front = (front + 1) % size;
		}
		delete[] data;
		data = temp;
		front = 0;
		back = size - 1;
		size *= 2;
	}

	bool empty() const {
		return size == 0;
	}
};

int main() {
	Queue q;
	for (int i = 1; i <= 10; i++) {
		q.push(i * 10);
	}

	for (int i = 1; i <= 10; i++) {
		std::cout << q.front_() << std::endl;
		q.pop();
	}

	system("pause");
	return 0;
}