#include <iostream>

bool binarySearch(const int* arr, int size, int number) {
	int start = 0;
	int end = size-1;
	while (start <= end) {
		int middle = (end + start) / 2;
		if (arr[middle] == number) {
			return true;
		}
		else if (arr[middle] > number) {
			end = middle - 1;
		}
		else if (arr[middle] < number) {
			start = middle + 1;
		}
	}

	return false;
}

int main() {
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,15,16,20,47,90,100 };
	bool b = binarySearch(arr, 16, 16);
	if (b) {
		std::cout << "Found";
	}
	else {
		std::cout << "Not Found";
	}
	return 0;
}
