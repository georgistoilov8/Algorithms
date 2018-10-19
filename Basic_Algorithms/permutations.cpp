#include <iostream>

void generate_permutations(int* set, int size, int current, bool* taken, int* result);

void permutations(int* set, int size) {
	bool* taken = new bool[size];
	int* result = new int[size];
	int current = 0;
	for (int i = 0; i < size; i++) {
		taken[i] = false;
	}

	generate_permutations(set, size, current, taken, result);
	
	delete[] result;
	delete[] taken;
}

void generate_permutations(int* set, int size, int current, bool* taken, int* result) {
	if (current == size) {
		for (int i = 0; i < size; i++) {
			std::cout << result[i] << ' ';
		}
		std::cout << std::endl;
		return;
	}

	for (int i = 0; i < size; i++) {
		if (!taken[i]) {
			result[current] = set[i];
			taken[i] = true;
			generate_permutations(set, size, current + 1, taken, result);
			taken[i] = false;
		}
	}
}

int main() {
	std::cout << "Combinations: " << std::endl;
	int arr[] = { 1,2,3 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	permutations(arr, arr_size);

	std::cout << "Combinations: " << std::endl;
	int arr2[] = { 1,2,3,4 };
	int arr_size2 = sizeof(arr2) / sizeof(arr2[0]);
	permutations(arr2, arr_size2);

	return 0;
}