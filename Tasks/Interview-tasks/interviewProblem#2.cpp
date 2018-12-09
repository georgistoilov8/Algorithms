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

/*
	Second way:
*/
int* productOfElements2(int* arr, int array_length) {
	int* result = new int[array_length];
	for (int i = 0; i < array_length; i++) {
		result[i] = 1;
		for (int j = 0; j < array_length; j++) {
			if (i != j) {
				result[i] *= arr[j];
			}
		}
	}
	return result;
}

void print(int* arr, int array_length) {
	for (int i = 0; i < array_length; i++) {
		std::cout << arr[i] << ' ';
	}
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
	int* result2 = productOfElements2(numbers, length);

	print(result, length);
	std::cout << std::endl;
	print(result2, length);

	delete[] numbers;
	delete[] result;
	delete[] result2;

	return 0;
}