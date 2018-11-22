#include <iostream>
#include <vld.h>

struct List {
	struct Node {
		int data;
		Node* ptr_next;
		Node* ptr_prev;

		Node(): ptr_next(nullptr), ptr_prev(nullptr){}
		Node(int data): data(data), ptr_next(nullptr), ptr_prev(nullptr){}
	};
	int size;
	Node* front_node;
	Node* back_node;

	List(): size(0), front_node(nullptr), back_node(nullptr){}

	~List() {
		while (!empty()) {
			pop_back();
		}
		size = 0;
		front_node = nullptr;
		back_node = nullptr;
	}

	void push_back(int el) {
		Node* new_node = new Node(el);
		if (empty()) {
			back_node = front_node = new_node;
		}
		else {
			new_node->ptr_prev = back_node;
			back_node->ptr_next = new_node;
			back_node = new_node;
		}
		
		size++;
	}

	void pop_back() {
		if (empty()) {
			return;
		}
		Node* prev_node = back_node->ptr_prev;
		delete back_node;
		back_node = prev_node;
		size--;
	}

	bool empty() const {
		return size == 0;
	}

	int back() const {
		return back_node->data;
	}
};

int main() {
	List l;
	for (int i = 1; i <= 10; i++) {
		l.push_back(i * 10);
	}
	for (int i = 1; i <= 10; i++) {
		std::cout << l.back() << std::endl; 
		l.pop_back();
	}

	system("pause");
	return 0;
}