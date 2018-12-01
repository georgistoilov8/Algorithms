#include <iostream>
#include <fstream>

struct Node {
	int data;
	Node* left_child;
	Node* right_child;

	Node(int data):data(data), left_child(nullptr), right_child(nullptr){}
};

struct Tree {
	Node* root;

	Tree() : root(nullptr) {}

	void insert(Node*& node, int element) {
		if (!node) {
			node = new Node(element);
			return;
		}
		if (element == node->data) {
			std::cout << "Element is already in the tree.\n";
			return;
		}
		if (element < node->data) {
			insert(node->left_child, element);
		}
		else {
			insert(node->right_child, element);
		}
	}

	void print(Node*& node) {
		// Left-Root-Right
		if (!node) {
			return;
		}
		print(node->left_child);
		std::cout << node->data << ' ';
		print(node->right_child);
	}

	void reverse_print(Node*& node) {
		// Right-Root-Left
		if (!node) {
			return;
		}
		reverse_print(node->right_child);
		std::cout << node->data << ' ';
		reverse_print(node->left_child);
	}

	void clear(Node*& node) {
		if (!node) {
			return;
		}
		clear(node->left_child);
		clear(node->right_child);
		delete node;
	}

	bool searchForElement(Node*& node, int element) {
		if (!node) {
			return false;
		}
		if (element == node->data) {
			return true;
		}
		if (element < node->data) {
			searchForElement(node->left_child, element);
		}
		else {
			searchForElement(node->right_child, element);
		}
	}

	void addToFile(Node*& node, std::fstream& file) {
		if (!node) {
			return;
		}
		file << node->data;
		file << ' ';
		addToFile(node->left_child, file);
		addToFile(node->right_child, file);
	}

	void insert(int element) {
		insert(root, element);
	}

	void print() {
		print(root);
	}

	void reverse_print() {
		reverse_print(root);
	}

	void clear(){
		clear(root);
	}

	bool searchForElement(int element) {
		return searchForElement(root, element);
	}

	void addToFile(std::fstream& file) {
		addToFile(root, file);
	}
};

int main(int argc, char** argv) {

	Tree t;

	//std::fstream file("numbers.txt");
	std::fstream file(argv[1]);
	while (!file.eof()) {
		int number;
		if (file.good()) {
			file >> number;
			t.insert(number);
		}
	}
	file.close();
	
	t.print();
	std::cout << std::endl;
	t.reverse_print();

	std::fstream file2(argv[1], std::ios::out | std::ios::trunc);

	//std::fstream file2("numbers.txt", std::ios::out | std::ios::trunc);
	t.addToFile(file2);
	file2.close();

	std::cout << std::endl;

	if (t.searchForElement(15)) {
		std::cout << "Yes"  << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}
	t.clear();
	
	return 0;
}