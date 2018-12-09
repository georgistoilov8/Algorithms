#include <iostream>
/*
	Created by Georgi Stoilov
*/

#include <unordered_set>

/*
	Task:
	Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

	For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

	Bonus: Can you do this in one pass?
*/

/*
	Version 1
*/
bool addUpNumber(int* arr, int arr_length, int number) {
	for (int i = 0; i < arr_length; i++) {
		for (int j = i; j < arr_length; j++) {
			if (arr[i] + arr[j] == number) {
				return true;
			}
		}
	}
	return false;
}

/*
	Version 2
*/
bool addUpNumber2(int* arr, int arr_length, int number) {
	std::unordered_set<int> set;
	for (int i = 0; i < arr_length; i++) {
		int searched_number = number - arr[i];
		if (searched_number >= 0) {
			if (set.find(searched_number) != set.end()) {
				return true;
			}
		}
		set.insert(arr[i]);
	}
	return false;
}

int main() {
	int length;
	std::cout << "Number of elements in the array: ";
	std::cin >> length;
	int* numbers = new int[length];
	for (int i = 0; i < length; i++) {
		std::cin >> numbers[i];
	}

	std::cout << "Number to check: ";
	int k;
	std::cin >> k;

	if (addUpNumber(numbers, length, k)) {
		std::cout << "Yes, there are numbers, which can be added up to " << k;
	}
	else {
		std::cout << "Not found any numbers.";
	}
	std::cout << std::endl;
	if (addUpNumber2(numbers, length, k)) {
		std::cout << "Yes, there are numbers, which can be added up to " << k;
	}
	else {
		std::cout << "Not found any numbers.";
	}
	std::cout << std::endl;
	delete[] numbers;

	return 0;
}
