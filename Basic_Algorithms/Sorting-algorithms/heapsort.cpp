#include <iostream>

void siftDown(int* arr, int arrSize, int position) {
	int left = position * 2 + 1;
	int right = left + 1;
	int max = position;
	if (left < arrSize && arr[left] > arr[max]) {
		max = left;
	}
	if (right < arrSize && arr[right] > arr[max]) {
		max = right;
	}
	if (max != position) {
		std::swap(arr[position], arr[max]);
		siftDown(arr, arrSize, max);
	}
}

void heapSort(int* arr, int arrSize) {
	for (int i = (arrSize - 1) / 2; i >= 0; i--) {
		siftDown(arr, arrSize, i);
	}

	for (int i = arrSize - 1; i >= 0; i--) {
		std::swap(arr[0], arr[i]);
		siftDown(arr, i, 0);
	}
}

int main() {
	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = rand();
	}

	for (int i = 0; i < 10; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
	heapSort(arr, 10);

	for (int i = 0; i < 10; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
  
	return 0;
}
