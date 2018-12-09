#include <iostream>
/*
	Created by Georgi Stoilov
*/

/*
	Task:
	Given an array of integers, return a new array such that each element at index i of the new array 
	is the product of all the numbers in the original array except the one at i.

	For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. 
	If our input was [3, 2, 1], the expected output would be [2, 3, 6].

	Follow-up: what if you can't use division?
*/


/*
	First way:
*/
int* productOfElements(int* arr, int array_length) {
	int max_product = 1;
	int* result = new int[array_length];
	for (int i = 0; i < array_length; i++) {
		max_product *= arr[i];
	}
	for (int i = 0; i < array_length; i++) {
		result[i] = max_product / arr[i];
	}
	return result;
}

int main() {
	int length;
	std::cout << "Number of elements in the array: ";
	std::cin >> length;
	int* numbers = new int[length];
	for (int i = 0; i < length; i++) {
		std::cin >> numbers[i];
	}

	int* result = productOfElements(numbers, length);
	for (int i = 0; i < length; i++) {
		std::cout << result[i] << ' ';
	}
	delete[] numbers;
	delete[] result;

	return 0;
}