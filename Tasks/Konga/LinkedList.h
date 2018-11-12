#pragma once

#ifndef LIST_HEADER
#define LIST_HEADER

template <typename T>
class List {
public:
	class Node {
	public:
		T data;
		Node* ptr_next;
		Node* ptr_previous;
	public:
		Node() :
			ptr_next(nullptr),
			ptr_previous(nullptr)
		{}
		Node(const T& new_data) :
			ptr_next(nullptr),
			ptr_previous(nullptr)
		{
			data = new_data;
		}
	};
private:
	int size;
	Node* front_node;
	Node* back_node;
public:
	List();
	List(const List& other);
	List& operator=(const List& rhs);
	~List();

	void copy(const List& other);
	void clear();

	void push_back(const T& element);
	void pop_back();

	void push_front(const T& element);
	void pop_front();

	void append_and_remove(List& other);

	List remove(Node* left_back, Node* right_front, int count);
	
	T& back();
	T& front();
	bool empty() const;
	int get_size() const;
	void print() const;

	class iterator {
		Node* ptr;
	public:
		iterator(Node* ptr_) :ptr(ptr_) {};
		iterator operator++() { iterator it = *this; ptr = ptr->ptr_next; return it; }
		iterator operator++(int) { ptr = ptr->ptr_next; return ptr; }
		Node& operator*() { return *ptr; }
		Node* operator->() { return ptr; }
		T& getData() { return ptr->data; }
		bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }
	};

	class const_iterator {
		Node* ptr;
	public:
		const_iterator(Node* ptr_) :ptr(ptr_) {};
		const_iterator operator++() { const_iterator it = *this; ptr = ptr->ptr_next; return it; }
		const_iterator operator++(int) { ptr = ptr->ptr_next; return ptr; }
		const Node& operator*() { return *ptr; }
		const Node* operator->() { return ptr; }
		const T& getData() const { return ptr->data; }
		bool operator==(const const_iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const const_iterator& rhs) { return ptr != rhs.ptr; }
	};

	class r_iterator {
		Node* ptr;
	public:
		r_iterator(Node* ptr_) :ptr(ptr_) {};
		r_iterator operator--() { r_iterator it = *this; ptr = ptr->ptr_previous; return it; }
		r_iterator operator--(int) { ptr = ptr->ptr_previous; return ptr; }
		Node& operator*() { return *ptr; }
		Node* operator->() { return ptr; }
		T& getData() { return ptr->data; }
		bool operator==(const r_iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const r_iterator& rhs) { return ptr != rhs.ptr; }
	};

	class r_const_iterator {
		Node* ptr;
	public:
		r_const_iterator(Node* ptr_) :ptr(ptr_) {};
		r_const_iterator operator--() { r_const_iterator it = *this; ptr = ptr->ptr_previous; return it; }
		r_const_iterator operator--(int) { ptr = ptr->ptr_previous; return ptr; }
		const Node& operator*() { return *ptr; }
		const Node* operator->() { return ptr; }
		const T& getData() const { return ptr->data; }
		bool operator==(const r_const_iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const r_const_iterator& rhs) { return ptr != rhs.ptr; }
	};
	iterator begin() { return iterator(front_node); }
	iterator end() { return iterator(back_node->ptr_next); } // If we return only back_node, the last element in the list is not checked!!

	const_iterator cbegin() const { return const_iterator(front_node); }
	const_iterator cend() const { return const_iterator(back_node->ptr_next); }
	
	r_iterator rbegin() { return r_iterator(back_node); }
	r_iterator rend() { return r_iterator(front_node->ptr_previous); }

	r_const_iterator rcbegin() const { return r_const_iterator(back_node); }
	r_const_iterator rcend() const { return r_const_iterator(front_node->ptr_previous); }
};

template <typename T>
List<T>::List()
	:size(0),
	front_node(nullptr),
	back_node(nullptr) {
}

template <typename T>
List<T>::List(const List<T>& other) {
	copy(other);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

template <typename T>
List<T>::~List() {
	clear();
}

template <typename T>
void List<T>::copy(const List<T>& other) {
	size = 0;
	int new_size = other.size;
	Node* current = other.front_node;
	while (size < new_size) {
		push_back(current->data);
		current = current->ptr_next;
	}
}

template <typename T>
void List<T>::clear() {
	while (size > 0) {
		Node* next = front_node->ptr_next;
		delete front_node;
		front_node = next;
		size--;
	}
	size = 0;
	front_node = nullptr;
	back_node = nullptr;
}

template <typename T>
void List<T>::push_back(const T& element) {
	Node* new_element = new Node;
	new_element->data = element;
	if (empty()) {
		new_element->ptr_next = nullptr;
		new_element->ptr_previous = nullptr;
		front_node = back_node = new_element;
	}
	else {
		new_element->ptr_previous = this->back_node;
		this->back_node->ptr_next = new_element;
		this->back_node = new_element;
	}
	size++;
}

template <typename T>
void List<T>::push_front(const T& element) {
	Node* new_element = new Node;
	new_element->data = element;
	if (empty()) {
		new_element->ptr_next = nullptr;
		new_element->ptr_previous = nullptr;
		front_node = back_node = new_element;
	}
	else {
		new_element->ptr_next = this->front_node;
		this->front_node->ptr_previous = new_element;
		this->front_node = new_element;
	}
	size++;
}

template <typename T>
void List<T>::pop_back() {
	if (empty()) {
		return;
	}
	Node* previous_node = back_node->ptr_previous;
	delete back_node;
	back_node = previous_node;
	if (back_node != nullptr) {
		back_node->ptr_next = nullptr;
	}
	size--;
}

template <typename T>
void List<T>::pop_front() {
	if (empty()) {
		return;
	}

	Node* next_node = front_node->ptr_next;
	delete front_node;
	front_node = next_node;
	if (front_node != nullptr) {
		front_node->ptr_previous = nullptr;
	}
	size--;
}

template <typename T>
void List<T>::append_and_remove(List<T>& other) {
	back_node->ptr_next = other.front_node;
	other.front_node->ptr_previous = back_node;
	back_node = other.back_node;
	size += other.size;
	other.front_node = nullptr;
	other.back_node = nullptr;
	other.size = 0;
}

template <typename T>
List<T> List<T>::remove(Node* left_back, Node* right_front, int count) {
	List<T> new_line;
	new_line.front_node = right_front;
	new_line.back_node = back_node;
	new_line.size = size - count;
	
	size = count;
	back_node = left_back;
	pop_back();
	return new_line;
}

template <typename T>
T& List<T>::back() {
	return back_node->data;
}

template <typename T>
T& List<T>::front() {
	return front_node->data;
}

template <typename T>
bool List<T>::empty() const {
	return size == 0;
}

template <typename T>
int List<T>::get_size() const {
	return size;
}
template <typename T>
void List<T>::print() const {
	Node* current = front_node;
	int count = 0;
	while (count < size ) {
		if (count + 1 >= size) {
			current->data.print_information(true);
		}
		else {
			current->data.print_information(false);
		}
		current = current->ptr_next;
		count++;
	}
}

#endif // !LIST_HEADER