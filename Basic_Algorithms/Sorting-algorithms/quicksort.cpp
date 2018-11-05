#include <iostream>

void print(int* array, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << ' ';
	}
	std::cout << std::endl;
}

void quicksort(int* arr, int size) {
	if (size > 1) {
		int middle_element = arr[std::rand() % size];

		// Left from middle
		int left = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i] < middle_element) {
				std::swap(arr[i], arr[left]);
				left++;
			}
		}
		quicksort(arr, left);

		// Right from middle
		int right = size - 1;
		for (int i = right; i >= left; i--) {
			if (arr[i] > middle_element) {
				std::swap(arr[i], arr[right]);
				right--;
			}
		}
		quicksort(arr + right + 1, size - right - 1);
	}
}

int main(){
	// Example:
	int test_arr[] = { 1,2,3,4,20,15,13,12,116, 19, 59, 39, 18, 5,6,7,8,50 };
	int size = sizeof(test_arr) / sizeof(test_arr[0]);
	quicksort(test_arr, size);
	print(test_arr, size);
  	return 0;
}
