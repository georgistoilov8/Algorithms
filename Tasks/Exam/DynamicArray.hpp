#pragma once

/*
* Author: Georgi Stoilov
*/

#include <iostream>
#include <cassert>

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

template <typename T>
class DynamicArray {
	std::size_t size;
	std::size_t capacity;
	T* data;
public:
	DynamicArray();
	DynamicArray(std::size_t capacity);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& rhs);
	~DynamicArray();

	void copyFrom(const DynamicArray& other);
	void clear();

	// Capacity:
	std::size_t get_capacity() const;
	std::size_t get_size() const;
	bool empty() const;

	// Modifiers:
	void push_back(const T& value);
	void pop_back();

	void resize();

	// Element access:
	T& at(std::size_t position);
	T& front();
	T& back();
	T& operator[](std::size_t);
	const T& operator[](std::size_t) const;

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

	Iterator begin() { return Iterator(data); }
	Iterator end() { return Iterator(data + size); }

	RIterator rbegin() { return RIterator(data + size - 1); }
	RIterator rend() { return RIterator(data - 1); }
};

template <typename T>
DynamicArray<T>::DynamicArray()
	:size(0),
	capacity(4)
{
	data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(std::size_t capacity)
	:size(0),
	capacity(capacity)
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
	data = new T[capacity];
	for (std::size_t i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

template <typename T>
void DynamicArray<T>::clear() {
	delete[] data;
	size = 0;
	capacity = 4;
}

template <typename T>
std::size_t DynamicArray<T>::get_capacity() const {
	return capacity;
}

template <typename T>
std::size_t DynamicArray<T>::get_size() const {
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
	data[size++] = value;
}

template <typename T>
void DynamicArray<T>::pop_back() {
	if (!empty()) {
		size--;
	}
}

template <typename T>
void DynamicArray<T>::resize() {
	T* temp;
	temp = new T[capacity * 2];
	for (std::size_t i = 0; i < size; i++) {
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
	capacity *= 2;
}

template <typename T>
T& DynamicArray<T>::at(std::size_t position) {
	assert(position < size);
	return data[position];
}

template <typename T>
T& DynamicArray<T>::front() {
	assert(!empty());
	return data[0];
}

template <typename T>
T& DynamicArray<T>::back() {
	assert(!empty());
	return data[size - 1];
}

template <typename T>
T& DynamicArray<T>::operator[](std::size_t position) {
	assert(position < size);
	return data[position];
}

template <typename T>
const T& DynamicArray<T>::operator[](std::size_t position) const {
	assert(position < size);
	return data[position];
}

#endif // !DYNAMIC_ARRAY