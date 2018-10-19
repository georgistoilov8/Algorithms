#include <iostream>

void generate_variations(int* set, int set_size, int k, int* result, bool* taken, int current_number);

void variations(int* set, int set_size, int k) {
	int* result = new int[k];						// Save the variation. And print it when we find it.
	bool* taken = new bool[set_size];				// Array to check if number from the set is taken. 
	int current_number = 0;							

	for (int i = 0; i < set_size; i++) {
		taken[i] = false;
	}

	generate_variations(set, set_size, k, result, taken, current_number);

	delete[] taken;
	delete[] result;
}

void generate_variations(int* set, int set_size, int k, int* result, bool* taken, int current_number) {
	if (k == current_number) {
		// We are ready with the variation. Should be printed on the screen.
		for (int i = 0; i < k; i++) {
			std::cout << result[i] << ' ';
		}
		std::cout << std::endl;
		return;
	}

	for (int i = 0; i < set_size; i++) {
		if (!taken[i]) {
			result[current_number] = set[i];
			taken[i] = true;
			generate_variations(set, set_size, k, result, taken, current_number + 1);
			taken[i] = false;
		}
	}
}

int main() {
	int arr[] = { 1,2,3,4 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	std::cout << "Variations: " << std::endl;
	variations(arr, arr_size, 2);

	int arr2[] = { 1,2,3,4,5 };
	int arr_size2 = sizeof(arr2) / sizeof(arr2[0]);
	std::cout << "Variations: " << std::endl;
	variations(arr2, arr_size2, 3);

	return 0;
}