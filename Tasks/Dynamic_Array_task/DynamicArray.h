<<<<<<< HEAD
=======
/*
* Author: Georgi Stoilov
*/
>>>>>>> a6415bfa7952230819cd1f356b7c03192a55f2f5
#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <iostream>
#include <cassert>

template <typename T>
class DynamicArray {
	int size;
	int capacity;
	bool sorted;
	T* data;
public:
	DynamicArray();
	DynamicArray(int capacity);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& rhs);
	~DynamicArray();

	void copyFrom(const DynamicArray& other);
	void clear();

	// Capacity:
	int get_capacity() const;
	int get_size() const;
	bool empty() const;

	// Modifiers:
	void push_back(const T& value);
	void pop_back();
	void remove(int position);

	void resize();

	// Element access:
	T& at(int position) const;
	T& front() const;
	T& back() const ;
	T& operator[](int);
	const T& operator[](int) const;

	T& min() const;
	T& max() const;

	// Sort and search:
	void sort();
	bool search(const T& element);

	// Show array:
	void print() const;

	// Iterator:
	class Iterator {
		T* ptr;
	public:
		Iterator(T* ptr_) :ptr(ptr_) {};
		Iterator operator++() { Iterator it = *this; ptr++; return it; }
		Iterator operator++(int) { ptr++; return ptr; }
		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }
		bool operator==(const Iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const Iterator& rhs) { return ptr != rhs.ptr; }
	};

	class Const_Iterator {
		T* ptr;
	public:
		Const_Iterator(T* ptr_) :ptr(ptr_) {};
		Const_Iterator operator++() { Const_Iterator it = *this; ptr++; return it; }
		Const_Iterator operator++(int) { ptr++; return ptr; }
		const T& operator*() { return *ptr; }
		const T* operator->() { return ptr; }
		bool operator==(const Const_Iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const Const_Iterator& rhs) { return ptr != rhs.ptr; }
	};

	class RIterator {
		T* ptr;
	public:
		RIterator(T* ptr_) :ptr(ptr_) {};
		RIterator operator--() { RIterator it = *this; ptr--; return it; }
		RIterator operator--(int) { ptr--; return ptr; }
		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }
		bool operator==(const RIterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const RIterator& rhs) { return ptr != rhs.ptr; }
	};

	class Const_RIterator {
		T* ptr;
	public:
		Const_RIterator(T* ptr_) :ptr(ptr_) {};
		Const_RIterator operator--() { Const_RIterator it = *this; ptr--; return it; }
		Const_RIterator operator--(int) { ptr--; return ptr; }
		const T& operator*() { return *ptr; }
		const T* operator->() { return ptr; }
		bool operator==(const Const_RIterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const Const_RIterator& rhs) { return ptr != rhs.ptr; }
	};

	Iterator begin() { return Iterator(data); }
	Iterator end() { return Iterator(data + size); }

	Const_Iterator cbegin() const { return Const_Iterator(data); }
	Const_Iterator cend() const { return Const_Iterator(data + size); }

	RIterator rbegin() { return RIterator(data + size - 1); }
	RIterator rend() { return RIterator(data - 1); }

	Const_RIterator crbegin() const { return Const_RIterator(data + size - 1); }
	Const_RIterator crend() const { return Const_RIterator(data - 1); }
private:
	void quicksort(T* arr, int size);
	bool binary_search(T* arr, int size, const T& element);
};

template <typename T>
DynamicArray<T>::DynamicArray()
	:size(0),
	 capacity(4),
	 sorted(true)
{
	data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(int capacity)
	:size(0),
	 capacity(capacity),
	 sorted(true)
{
	data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {
	copyFrom(other);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs) {
	if (this != &rhs) {
		clear();
		copyFrom(rhs);
	}
	return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
	clear();
}

template <typename T>
void DynamicArray<T>::copyFrom(const DynamicArray<T>& other) {
	capacity = other.capacity;
	size = other.size;
	sorted = other.sorted;
	data = new T[capacity];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

template <typename T>
void DynamicArray<T>::clear() {
	delete[] data;
	size = 0;
	capacity = 4;
	sorted = true;
}

template <typename T>
int DynamicArray<T>::get_capacity() const {
	return capacity;
}

template <typename T>
int DynamicArray<T>::get_size() const {
	return size;
}

template <typename T>
bool DynamicArray<T>::empty() const {
	return size == 0;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
	if (size >= capacity) {
		resize();
	}
	if(size > 0 && data[size-1] > value){
		sorted = false;
	}
	data[size++] = value;

}

template <typename T>
void DynamicArray<T>::pop_back() {
	if (!empty()) {
		size--;
	}
}

template <typename T>
void DynamicArray<T>::remove(int position) {
	assert(position < size);
	for (int i = position; i < size - 1; i++) {
		std::swap(data[i], data[i + 1]);
	}
	size--;
}

template <typename T>
void DynamicArray<T>::resize() {
	T* temp;
	temp = new T[capacity * 2];
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
	capacity *= 2;
}

template <typename T>
T& DynamicArray<T>::at(int position) const {
	assert(position < size);
	return data[position];
}

template <typename T>
T& DynamicArray<T>::front() const {
	assert(!empty());
	return data[0];
}

template <typename T>
T& DynamicArray<T>::back() const {
	assert(!empty());
	return data[size - 1];
}

template <typename T>
T& DynamicArray<T>::operator[](int position) {
	assert(position < size);
	return data[position];
}

template <typename T>
const T& DynamicArray<T>::operator[](int position) const {
	assert(position < size);
	return data[position];
}

template <typename T>
T& DynamicArray<T>::min() const {
	if (sorted) {
		return data[0];
	}
	T min_element = data[0];
	for (int i = 1; i < size; i++) {
		if (min_element > data[i]) {
			min_element = data[i];
		}
	}
	return min_element;
}

template <typename T>
T& DynamicArray<T>::max() const {
	if (sorted) {
		return data[size-1];
	}
	T max_element = data[0];
	for (int i = 1; i < size; i++) {
		if (max_element < data[i]) {
			max_element = data[i];
		}
	}
	return max_element;
}

template <typename T>
void DynamicArray<T>::print() const {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << ' ';
	}
	std::cout << std::endl;
}

template <typename T>
void DynamicArray<T>::sort() {
	quicksort(data, size);
	sorted = true;
}

template <typename T>
void DynamicArray<T>::quicksort(T* arr, int arr_size) {
	if (arr_size > 1) {
		T element = arr[std::rand() % arr_size];

		int left = 0;
		for (int i = 0; i < arr_size; i++) {
			if (arr[i] < element) {
				std::swap(arr[i], arr[left++]);
			}
		}
		quicksort(arr, left);

		int right = arr_size - 1;
		for (int i = right; i >= left; i--) {
			if (arr[i] > element) {
				std::swap(arr[i], arr[right--]);
			}
		}
		quicksort(arr+right+1, arr_size - right - 1);
	}
}

template <typename T>
bool DynamicArray<T>::search(const T& element) {
	if (sorted) {
		return binary_search(data, size, element);
	}
	for (int i = 0; i < size; i++) {
		if (data[i] == element) {
			return true;
		}
	}
	return false;
}

template <typename T>
bool DynamicArray<T>::binary_search(T* arr, int arr_size, const T& element) {
	int middle = arr_size / 2;
	T middle_element = arr[middle];

	if (arr_size <= 0) {
		return false;
	}

	if (element == middle_element) {
		return true;
	}

	if (element < middle_element) {
		binary_search(arr, middle, element);
	}
	else {
		binary_search(arr + middle, middle, element);
	}
}

#endif // !DYNAMIC_ARRAY
