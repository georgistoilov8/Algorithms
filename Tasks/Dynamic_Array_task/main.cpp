#include <iostream>
#include "DynamicArray.h"

template <typename T>
DynamicArray<T> reverse(DynamicArray<T>& arr) {
	DynamicArray<T> temp;
	int index = arr.get_size() - 1;
	for (typename DynamicArray<T>::RIterator it = arr.rbegin(); it != arr.rend(); it--) {
		temp.push_back(*it);
	}
	return temp;
}

int main() {
	
	return 0;
}