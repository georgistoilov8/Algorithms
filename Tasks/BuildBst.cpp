#include <iostream>
#include <vector>

struct Node {
	int data;
	Node* left_child;
	Node* right_child;

	Node(int new_data, Node* left = nullptr, Node* right = nullptr)
		:data(new_data),left_child(left),right_child(right){}
};

Node* BuildBst(const std::vector<int>& arr, int begin, int end) {
	if (begin >= end) {
		return nullptr;
	}
	const int middle = (begin + end) / 2;
	Node* root = new Node(arr[middle]);
	root->left_child = BuildBst(arr, begin, middle);
	root->right_child = BuildBst(arr, middle + 1, end);
	return root;
}

Node* BuildBst(const std::vector<int>& arr) {
	return BuildBst(arr, 0, arr.size());
}

void printBst(Node* node) {
	if (!node) {
		return;
	}
	printBst(node->left_child);
	std::cout << node->data << std::endl;
	printBst(node->right_child);
}

void clean(Node* node) {
	if (!node) {
		return;
	}
	clean(node->left_child);
	clean(node->right_child);
	delete node;
}

int main() {
	std::vector<int> arr;
	arr.push_back(2);
	arr.push_back(4);
	arr.push_back(6);
	arr.push_back(8);
	arr.push_back(10);
	arr.push_back(12);


	Node* root = BuildBst(arr);
	printBst(root);
	clean(root);
	return 0;
}