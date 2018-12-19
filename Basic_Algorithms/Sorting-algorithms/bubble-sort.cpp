/*
	Author: Georgi Stoilov
*/

#include <iostream>

template <typename T>
void buble_sort(T* arr, unsigned arr_size) {
	bool is_sorted = false;
	while (!is_sorted) {
		is_sorted = true;
		for (unsigned i = 0; i < arr_size-1; i++) {
			if (arr[i] > arr[i + 1]) {
				std::swap(arr[i], arr[i + 1]);
				is_sorted = false;
			}
		}
	}
		
}

int main() {
	std::cout << "Input array size: ";
	int n;
	std::cin >> n;
	int* arr = new int[n];
	std::cout << "Input array: ";
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}
	buble_sort<int>(arr, n);
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << ' ';
	}
	delete[] arr;
	return 0;
}
