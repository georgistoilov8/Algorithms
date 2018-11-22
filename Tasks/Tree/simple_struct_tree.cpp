#include <iostream>

struct Tree {
	struct Node {
		int data;
		Node* left_child;
		Node* right_child;
		Node(): left_child(nullptr), right_child(nullptr){}
		Node(int element) : data(element), left_child(nullptr), right_child(nullptr){}
	};

	Node* root;

	Tree(): root(nullptr){}

	void insert(Node*& node, int element) {
		if (!node) {
			node = new Node(element);
		}
		else {
			if (node->data > element) {
				insert(node->left_child, element);
			}
			else {
				insert(node->right_child, element);
			}
		}
	}

	void remove(Node*& node, int element) {
		if (!node) {
			return;
		}
		if (element == node->data) {
			if (!node->left_child && !node->right_child) {
				delete node;
				node = nullptr;
			}
			else if(node->left_child && node->right_child) {
				Node* temp_node;
				findBiggestLeft(node->left_child, temp_node);
				std::swap(node->data, temp_node->data);
				remove(node->left_child, temp_node->data);
			}
			else if (!node->left_child) {
				Node* temp = node->right_child;
				delete node;
				node = temp;
			}
			else if (!node->right_child) {
				Node* temp = node->left_child;
				delete node;
				node = temp;
			}
		}
		else {
			if (element < node->data) {
				remove(node->left_child, element);
			}
			else {
				remove(node->right_child, element);
			}
		}
	}

	void findBiggestLeft(Node* node, Node*& biggest_node) {
		if(!node){
			return;
		}
		biggest_node = node;
		findBiggestLeft(node->right_child, biggest_node);
	}

	void findSmallestRight(Node* node, Node*& smallest_node) {
		if (!node) {
			return;
		}
		smallest_node = node;
		findSmallestRight(node->left_child, smallest_node);
	}

	void print(Node* node){
		if (!node) {
			return;
		}
		print(node->left_child);
		std::cout << node->data << ' ';
		print(node->right_child);
	}

	void print() {
		print(root);
	}

	void insert(int element) {
		insert(root, element);
	}

	void remove(int element) {
		remove(root, element);
	}
};

int main() {

	Tree t;
	t.insert(5);
	t.insert(3);
	t.insert(1);
	t.insert(4);
	t.insert(12);
	t.insert(8);
	t.insert(7);
	t.insert(10);
	t.insert(11);
	t.insert(14);
	t.print();

	t.remove(11);
	
	std::cout << std::endl;
	t.print();

	system("pause");
	return 0;
}