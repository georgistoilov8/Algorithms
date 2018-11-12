#pragma once

#ifndef DYNAMIC_ARRAY_HEADER
#define DYNAMIC_ARRAY_HEADER

#include <iostream>
#include <cassert>

template <typename T>
class DynamicArray {
	int size;
	int capacity;
	T* data;
public:
	DynamicArray();
	DynamicArray(int capacity);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& rhs);
	~DynamicArray();

	void copyFrom(const DynamicArray& other);
	void clear();

	int get_capacity() const;
	int get_size() const;
	bool empty() const;
	void print() const;

	void push_back(const T& value);
	void pop_back();

	void resize();

	T& at(int position);
	T& front();
	T& back();
	T& operator[](int);
	const T& operator[](int) const;

	class iterator {
		T* ptr;
	public:
		iterator(T* ptr_) :ptr(ptr_) {};
		iterator operator++() { iterator it = *this; ptr++; return it; }
		iterator operator++(int) { ptr++; return ptr; }
		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }
		bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }
	};

	class const_iterator {
		T* ptr;
	public:
		const_iterator(T* ptr_) :ptr(ptr_) {};
		const_iterator operator++() { const_iterator it = *this; ptr++; return it; }
		const_iterator operator++(int) { ptr++; return ptr; }
		const T& operator*() { return *ptr; }
		const T* operator->() { return ptr; }
		bool operator==(const const_iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const const_iterator& rhs) { return ptr != rhs.ptr; }
	};

	class r_iterator {
		T* ptr;
	public:
		r_iterator(T* ptr_) :ptr(ptr_) {};
		r_iterator operator--() { r_iterator it = *this; ptr--; return it; }
		r_iterator operator--(int) { ptr--; return ptr; }
		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }
		bool operator==(const r_iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const r_iterator& rhs) { return ptr != rhs.ptr; }
	};

	class r_const_iterator {
		T* ptr;
	public:
		r_const_iterator(T* ptr_) :ptr(ptr_) {};
		r_const_iterator operator--() { r_const_iterator it = *this; ptr--; return it; }
		r_const_iterator operator--(int) { ptr--; return ptr; }
		const T& operator*() { return *ptr; }
		const T* operator->() { return ptr; }
		bool operator==(const r_const_iterator& rhs) { return ptr == rhs.ptr; }
		bool operator!=(const r_const_iterator& rhs) { return ptr != rhs.ptr; }
	};

	iterator begin() { return iterator(data); }
	iterator end() { return iterator(data + size); }

	const_iterator cbegin() const { return const_iterator(data); }
	const_iterator cend() const { return const_iterator(data + size); }

	r_iterator rbegin() { return r_iterator(data + size - 1); }
	r_iterator rend() { return r_iterator(data - 1); }

	r_const_iterator rcbegin() const { return r_const_iterator(data + size - 1); }
	r_const_iterator rcend() const { return r_const_iterator(data - 1); }

};

template <typename T>
DynamicArray<T>::DynamicArray()
	:size(0),
	capacity(4)
{
	data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(int capacity)
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
	for (int i = 0; i < size; i++) {
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
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
	capacity *= 2;
}

template <typename T>
T& DynamicArray<T>::at(int position) {
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
void DynamicArray<T>::print() const {
	for (int i = 0; i < size; i++) {
		std::cout << "Line" << i << ": ";
		data[i].print();
		std::cout << std::endl;
	}
}

#endif // !DYNAMIC_ARRAY_HEADER
