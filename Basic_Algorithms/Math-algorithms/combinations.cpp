#include <iostream>

void generate_combinations(int* arr, int size, int k, int* result, int current, bool* taken, int position_in_set);

void combinations(int* arr, int size, int k) {
	int current = 0;
	bool* taken = new bool[size];
	int* result = new int[k];
	for (int i = 0; i < size; i++) {
		taken[i] = false;
	}
	generate_combinations(arr, size, k, result, current, taken, 0);
	delete[] result;
	delete[] taken;
}

void generate_combinations(int* arr, int size, int k, int* result, int current, bool* taken, int position_in_set) {
	if (current == k) {
		for (int i = 0; i < k; i++) {
			std::cout << result[i];
			std::cout << ' ';
		}
		std::cout << std::endl;
		return;
	}

	for (int i = position_in_set; i < size; i++) {
		if (!taken[i]) {
			taken[i] = true;
			result[current] = arr[i];
			generate_combinations(arr, size, k, result, current + 1, taken, i);
			taken[i] = false;
		}
	}
}

int main() {
	std::cout << "Combinations: " << std::endl;
	int arr[] = { 1,2,3,4 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	combinations(arr, arr_size, 2);
	
	std::cout << "Combinations: " << std::endl;
	int arr2[] = { 1,2,3,4,5 };
	int arr_size2 = sizeof(arr2) / sizeof(arr2[0]);
	combinations(arr2, arr_size2, 3);

	return 0;
}