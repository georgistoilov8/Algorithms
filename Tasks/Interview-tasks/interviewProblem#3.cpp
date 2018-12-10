#include <iostream>
/*
	Created by Georgi Stoilov
*/

/*
	Task:
	Given an array of integers, find the first missing positive integer in linear time and 
	constant space. In other words, find the lowest positive integer that does not exist in 
	the array. The array can contain duplicates and negative numbers as well.

	For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.
*/

int separate(int* arr, int arr_length) {
	int count = 0;
	for (int i = 0; i < arr_length; i++) {
		if (arr[i] <= 0) {
			std::swap(arr[count], arr[i]);
			count++;
		}
	}
	return count;
}

int findLowestPositiveNumber(int* arr, int arr_length) {
	for (int i = 0; i < arr_length; i++) {
		if (arr[i] - 1 < arr_length && arr[arr[i] - 1] > 0) {
			arr[arr[i] - 1] = -arr[arr[i] - 1];
		}
	}
	for (int i = 0; i < arr_length; i++) {
		if (arr[i] > 0) {
			return i + 1;
		}
	}
	return arr_length + 1;
}

int main() {
	int length;
	std::cout << "Number of elements in the array: ";
	std::cin >> length;
	int* numbers = new int[length];
	for (int i = 0; i < length; i++) {
		std::cin >> numbers[i];
	}

	int shift = separate(numbers, length);
	int result = findLowestPositiveNumber(numbers+shift, length-shift);

	std::cout << "Lowest positive number is: " << result;
	delete[] numbers;
	
	return 0;
}