#include <iostream>

void insertionSort(int* arr, int arr_size) {
	for (int i = 0; i < arr_size; i++) {
		int key = arr[i];
		int count = i;
		while (count >= 1 && key < arr[count - 1]) {
			arr[count] = arr[count - 1];
			count--;
		}
		arr[count] = key;
	}
}

int main()
{
	int arr[] = { 5, 4, 6, 10, 2, 15, 8, 3 };
	int arr_size = 8;

	insertionSort(arr, arr_size);

	for (int i = 0; i < arr_size; i++) {
		std::cout << arr[i] << ' ';
	}
	
  return 0;
}
