#include <iostream>
#include "DynamicArray.h"

/*
	Reverse dynami_array
*/
template <typename T>
DynamicArray<T> reverse(DynamicArray<T>& arr) {
	DynamicArray<T> result;
	for (typename DynamicArray<T>::RIterator it = arr.rbegin(); it != arr.rend(); it--) {
		result.push_back(*it);
	}
	return result;
}
/*
	Using const iterator
*/
template <typename T>
DynamicArray<T> reverse_c(const DynamicArray<T>& arr) {
	DynamicArray<T> result;
	for (typename DynamicArray<T>::Const_RIterator it = arr.crbegin(); it != arr.crend(); it--) {
		result.push_back(*it);
	}
	return result;
}

/*
	Merge two dynamic_arrays
*/
template <typename T>
DynamicArray<T> merge(DynamicArray<T>& arr1, DynamicArray<T>& arr2) {
	DynamicArray<T> result = arr1;
	for (typename DynamicArray<T>::Iterator it = arr2.begin(); it != arr2.end(); it++) {
		result.push_back(*it);
	}
	return result;
}

/*
	Remove duplicate elements from dynamic_array
*/
template <typename T>
DynamicArray<T> set(DynamicArray<T>& arr) {
	arr.sort();
	DynamicArray<T> result;
	int size = arr.get_size();
	for (int i = 1; i < size; i++) {
		if (arr[i] != arr[i-1]) {
			result.push_back(arr[i-1]);
		}
	}
	result.push_back(arr[size - 1]);
	return result;
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
	arr.print();
	DynamicArray<int> arr2 = reverse(arr);
	arr2.print();
	DynamicArray<int> arr3 = merge(arr, arr2);
	arr3.print();
	DynamicArray<int> arr4 = set(arr3);
	arr4.print();

	arr = reverse_c(arr4);
	arr.print();
	int x;
	std::cin >> x;
	return 0;
}