/*
	Author: Georgi Stoilov
*/
#ifndef LIST_INCLUDED
#define LIST

// Linked list

template <typename T>
struct Node {
	T data;
	Node<T>* ptr_next;
	Node<T>* ptr_previous;
};

template <typename T>
class List {
		int size;
		Node<T>* front_node;
		Node<T>* back_node;
	public:
		List();
		List(const List& other);
		List& operator=(const List& rhs);
		~List();

		// help functions:
		void append(const List& other);
		void clear();

		void push_back(const T& element);
		void pop_back();

		void push_front(const T& element);
		void pop_front();

		T& back();
		T& front();
		bool empty() const;
};

template <typename T>
List<T>::List()
	:size(0),
	front_node(nullptr),
	back_node(nullptr) {
}

template <typename T>
List<T>::List(const List<T>& other) {
	append(other);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs) {
	if (this != &rhs) {
		clear();
		append(rhs);
	}
}

template <typename T>
List<T>::~List() {
	clear();
}

template <typename T>
void List<T>::append(const List<T>& other) {
	size = 0;
	int new_size = other.size;
	Node<T>* current = other.front_node;
	while (size < new_size) {
		push_back(current->data);
		current = current->ptr_next;
	}
}

template <typename T>
void List<T>::clear() {
	std::cout << size << std::endl;
	while (size > 0) {
		Node<T>* next = front_node->ptr_next;
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
	Node<T>* new_element = new Node<T>;
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
	Node<T>* new_element = new Node<T>;
	new_element->data = element;
	if (empty()) {
		new_element->ptr_next = nullptr;
		new_element->ptr_previous = nullptr;
		front_node = back_node = new_element;
	} else {
		new_element->ptr_next = this->front_node;
		this->front_node->ptr_previous = new_element;
		this->front_node = new_element;
	}
}

template <typename T>
void List<T>::pop_back() {
	if (empty()) {
		return;
	}
	Node<T>* previous_node = back_node->ptr_previous;
	delete back_node;
	back_node = previous_node;
	size--;
}

template <typename T>
void List<T>::pop_front() {
	if (empty()) {
		return;
	}
	Node<T>* next_node = front_node->ptr_next;
	delete front_node;
	front_node = next_node;
	size--;
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
#endif // !LIST_INCLUDED
