#include <iostream>

#include "Stack.hpp"
#include "DynamicArray.hpp"

typedef DynamicArray<Stack<double>> stackCalc;

void create(stackCalc& arr) {
	Stack<double> s;
	arr.push_back(s);
}

void push(stackCalc& arr, int index, double d) {
	/*for (DynamicArray<Stack<double>>::Iterator it = arr.begin(); it != arr.end; it++) {
		
	}*/
	arr[index].push(d);
}

void pop(stackCalc& arr, int index) {
	arr[index].pop();
	if (arr[index].empty()) {
		for (int i = index; i < arr.get_size()-1; i++) {
			arr[i] = arr[i + 1];
		}
	}
}

void add(stackCalc& arr) {
	int size = arr.get_size();
	for (int i = 0; i < size; i++) {
		double a = arr[i].top();
		arr[i].pop();
		double b = arr[i].top();
		arr[i].pop();
		arr[i].push(a + b);
	}
}

void sub(stackCalc& arr) {
	int size = arr.get_size();
	for (int i = 0; i < size; i++) {
		double a = arr[i].top();
		arr[i].pop();
		double b = arr[i].top();
		arr[i].pop();
		arr[i].push(b - a);
	}
}

void negative(stackCalc& arr) {
	int size = arr.get_size();
	for (int i = 0; i < size; i++) {
		double a = arr[i].top();
		arr[i].pop();
		arr[i].push(-a);
	}
}

void print(stackCalc& arr) {
	int size = arr.get_size();
	for (int i = 0; i < size; i++) {
		arr[i].print();
	}
}

int main() {

	DynamicArray<Stack<double>> s;
	create(s);

	push(s, 0, 20.2);
	push(s, 0, 20.3);
	push(s, 0, 20.4);
	push(s, 0, 20.5);

	pop(s, 0);
	add(s);
	negative(s);

	print(s);

	int x;
	std::cin >> x;
	return 0;
}

