#include <iostream>
#include "DynamicArray.h"

template <typename T>
void reverse(DynamicArray<T>& arr) {
	for (typename DynamicArray<T>::Iterator it = arr.begin(); it != arr.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

int main() {
	DynamicArray<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);
	arr.push_back(5);
	arr.push_back(6);
	arr.push_back(7);
	arr.push_back(8);
	reverse(arr);
	int x;
	std::cin >> x;
	return 0;
}