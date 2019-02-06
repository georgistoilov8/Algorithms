#include <iostream>
#include <vector>
#include <queue>

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

void printBstHead(Node* node) {
	if (!node) {
		return;
	}
	std::cout << node->data << std::endl;
	printBstHead(node->left_child);
	printBstHead(node->right_child);
}

void clean(Node* node) {
	if (!node) {
		return;
	}
	clean(node->left_child);
	clean(node->right_child);
	delete node;
}

Node* findCommonAncestor(Node* node, int left, int right) {
	if (node->data > left && node->data > right) {
		return findCommonAncestor(node->left_child, left, right);
	}

	if (node->data < left && node->data < right) {
		return findCommonAncestor(node->right_child, left, right);
	}
	return node;
}

Node* findPreviousByLevel(Node* root, int key) {
	if (root->data == key) {
		return nullptr;
	}
	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty()) {
		Node* node = queue.front();
		if (node->left_child) {
			if (node->left_child->data == key) {
				return queue.back();
			}
			else {
				queue.push(node->left_child);
			}
		}
		if (node->right_child) {
			if (node->right_child->data == key) {
				return queue.back();
			}
			else {
				queue.push(node->right_child);
			}
		}
		queue.pop();
	}
	return nullptr;
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
	std::cout << "Binary-search tree printed in: Left-Head-Right way.\n";
	printBst(root);

	int A = 2;
	int B = 6;
	Node* common = findCommonAncestor(root, A, B);
	std::cout << "Common ancestor of " << A << " and " << B << " is: " << common->data << std::endl;

	clean(root);

	std::vector<int> arr2;
	arr2.push_back(2);
	arr2.push_back(4);
	arr2.push_back(5);
	arr2.push_back(6);
	arr2.push_back(8);
	arr2.push_back(11);

	root = BuildBst(arr2);
	Node* previous = findPreviousByLevel(root, 4);
	std::cout << "Previous element by level is: ";
	//std::cout << previous->data << std::endl;
	(previous) ? std::cout << previous->data : std::cout << "nullptr";
	std::cout << std::endl;
	printBstHead(root);


	clean(root);

	return 0;
}
