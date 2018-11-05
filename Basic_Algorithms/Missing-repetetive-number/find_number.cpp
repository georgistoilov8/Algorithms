/*
	Author: Georgi Stoilov
*/

#include <iostream>

void find_repetetive_number(int* arr, int size) {
	// Sum of 1+2+....+n = n*(n+1)/2
	// In our case size = n + 1
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
	}
	int repetetive_number = sum - (size - 1) * (size) / 2;
	std::cout << "The repetetive number is: " << repetetive_number << std::endl;
}

void find_missing_number(int* arr, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
	}
	int missing_number = (size + 1) * ((size + 1) + 1) / 2 - sum;
	std::cout << "The missing number is: " << missing_number << std::endl;
}

int main() {
	int arr[] = { 1,2,5,4,3,9,8,7,10,6,6 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	find_repetetive_number(arr, arr_size);

	int arr2[] = { 1,2,3,4,5,6,8,9,10 }; // 7 is missing
	int arr2_size = sizeof(arr2) / sizeof(arr2[0]);
	find_missing_number(arr2, arr2_size);
	int x;
	std::cin >> x;
	return 0;
}