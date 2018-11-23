#pragma once

#include <iostream>

template <typename T>
class BinarySearchTree {
	public:
		struct Node {
			T data;
			Node* left_child;
			Node* right_child;

			Node(): left_child(nullptr), right_child(nullptr){}
			Node(const T& data): data(data), left_child(nullptr), right_child(nullptr){}
		};
	private:
		Node* root;

	public:
		BinarySearchTree();
		~BinarySearchTree();

		void insert(const T& element);
		void print() const;
		void remove(const T& element);

		bool contain(const T& element) const;	// return true if element is somewhere in the the tree, false if it's not.
	private:
		void removeAllElements(Node*& node);

		void insert(Node*& node, const T& element);
		void print(const Node* node) const;
		void remove(Node*& node, const T& element);
		
		bool contain(const Node* node, const T& element) const;

		void findBiggestLeft(Node* node, Node*& biggest_node);
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(): root(nullptr){}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	removeAllElements(root);
}

template <typename T>
void BinarySearchTree<T>::removeAllElements(Node*& node) {
	if (!node) {
		return;
	}
	removeAllElements(node->left_child);
	removeAllElements(node->right_child);
	
	delete node;
}

template <typename T>
void BinarySearchTree<T>::insert(Node*& node, const T& element) {
	if (!node) {
		node = new Node(element);
	}
	if (element > node->data) {
		insert(node->right_child, element);
	}
	else if (element < node->data) {
		insert(node->left_child, element);
	}
}

template <typename T>
void BinarySearchTree<T>::insert(const T& element) {
	insert(root, element);
}

template <typename T>
void BinarySearchTree<T>::print(const Node* node) const {
	if (!node) {
		return;
	}
	print(node->left_child);
	std::cout << node->data << ' ';
	print(node->right_child);
}

template <typename T>
void BinarySearchTree<T>::print() const {
	print(root);
}

template <typename T>
void BinarySearchTree<T>::remove(Node*& node, const T& element) {
	if (!node) {
		return;
	}
	if (node->data == element) {
		if (!node->left_child && !node->right_child) {
			delete node;
			return;
		}
		else if (node->left_child && node->right_child) {
			Node* temp_node;
			findBiggestLeft(node->left_child, temp_node);
			std::swap(node->data, temp_node->data);
			remove(node->left_child, element);
		}
		else if (node->left_child) {
			Node* temp_node = node->left_child;
			delete node;
			node = temp_node;
		}
		else if (node->right_child) {
			Node* temp_node = node->right_child;
			delete node;
			node = temp_node;
		}
	}
	else {
		remove(node->left_child, element);
		remove(node->right_child, element);
	}
}

template <typename T>
void BinarySearchTree<T>::remove(const T& element) {
	remove(root, element);
}

template <typename T>
void BinarySearchTree<T>::findBiggestLeft(Node* node, Node*& biggest_node) {
	if (!node) {
		return;
	}
	biggest_node = node;
	findBiggestLeft(node->right_child, biggest_node);
}

template <typename T>
bool BinarySearchTree<T>::contain(const Node* node, const T& element) const {
	if (!node || node->data == element) {
		return node;
	}
	if (element < node->data) {
		contain(node->left_child, element);
	}
	else {
		contain(node->right_child, element);
	}

}

template <typename T>
bool BinarySearchTree<T>::contain(const T& element) const {
	return contain(root, element);
}
