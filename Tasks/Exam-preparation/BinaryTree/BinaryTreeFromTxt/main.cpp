#include <iostream>
#include <fstream>

struct Node {
	int data;
	Node* left_child;
	Node* right_child;

	Node(int data): data(data), left_child(nullptr), right_child(nullptr){}
};

struct Tree {
	Node* root;
	Tree(): root(nullptr){}

	void insert(int data) {
		insert(root, data);
	}

	void print() {
		print(root);
	}

	void opposite_print() {
		opposite_print(root);
	}

	void clear() {
		clear(root);
	}

	void insert(Node*& n, int data) {
		if (!n) {
			n = new Node(data);
			return;
		}
		if (data == n->data) {
			std::cout << "Number: " << data << " is already in the tree.\n";
			return;
		}
		else if (data < n->data) {
			insert(n->left_child, data);
		}
		else {
			insert(n->right_child, data);
		}
	}

	void print(Node*& n) {
		if (!n) {
			return;
		}
		print(n->left_child);
		std::cout << n->data << ' ';
		print(n->right_child);
	}

	void opposite_print(Node*& n) {
		if (!n) {
			return;
		}
		opposite_print(n->right_child);
		std::cout << n->data << ' ';
		opposite_print(n->left_child);
	}

	void clear(Node*& n) {
		if (!n) {
			return;
		}
		clear(n->left_child);
		clear(n->right_child);
		delete n;
	}

	int countSubTrees(Node*& n, int number){
		return 0;
		// TO DO:
	}

	int countSubTrees(int number) {
		return countSubTrees(root, number);
	}

	void addToFile(Node*& n, std::fstream& file) {
		if (!n) {
			return;
		}
		file << n->data;
		file << ' ';
		addToFile(n->left_child, file);
		addToFile(n->right_child, file);
	}

	void addToFile(std::fstream& file) {
		addToFile(root, file);
	}
};

int main() {

	Tree t;

	int number;
	std::fstream file("numbers.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			file >> number;
			if (file.good()) {
				t.insert(number);
			}
		}
	}
	file.close();

	t.print();

	std::cout << std::endl;

	t.opposite_print();

	std::cout << std::endl;

	std::cout << t.countSubTrees(1) << std::endl;

	std::fstream file2("numbers.txt", std::ios::out | std::ios::trunc);
	t.addToFile(file2);
	file2.close();
	t.clear();

	return 0;
}

