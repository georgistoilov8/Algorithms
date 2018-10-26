#include <iostream>

void quicksort(int* arr, int size) {
	if (size > 1) {
		int middle = size / 2;

		// Left from middle
		int left = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i] < arr[middle]) {
				std::swap(arr[left], arr[i]);
				left++;
			}
		}
		quicksort(arr, left);

		// Right from middle
		int right = size - 1;
		for (int i = right; i >= left; i--) {
			if (arr[i] > arr[middle]) {
				std::swap(arr[right], arr[i]);
				right--;
			}
		}
		quicksort(arr + right + 1, size - right - 1);
	}
}

int main(){
  return 0;
}
