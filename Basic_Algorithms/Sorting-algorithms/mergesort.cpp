/*
	Author: Georgi Stoilov
*/

#include <iostream>

void print(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

void merge(int* left_arr, int* right_arr, int* result, int left_arr_size, int right_arr_size) {
	int new_size = left_arr_size + right_arr_size;
	
	int left_i = 0;
	int right_i = 0;
	int iter = 0;
	while (left_i < left_arr_size && right_i < right_arr_size) {
		if (left_arr[left_i] < right_arr[right_i]) {
			result[iter++] = left_arr[left_i++];
		}
		else {
			result[iter++] = right_arr[right_i++];
		}
	}
	while (left_i < left_arr_size) {
		result[iter++] = left_arr[left_i++];
	}
	while (right_i < right_arr_size) {
		result[iter++] = right_arr[right_i++];
	}
}


void mergesort(int* arr, int size, int* result) {
	if (size > 1) {
		mergesort(arr, size / 2, result);
		mergesort(arr + size / 2, size - size / 2, result + size / 2);
		merge(arr, arr + size / 2, result, size / 2, size - size / 2);
		memcpy(arr, result, sizeof(arr[0]) * size);
	}
}

int main() {
	int arr[] = { 1,3,5,4,0,9,2,4 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	int *result = new int[arr_size];
	mergesort(arr, arr_size, result);
	print(result, arr_size);
	delete[] result;
	return 0;
}