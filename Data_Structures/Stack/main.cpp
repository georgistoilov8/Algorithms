#include <iostream>
#include <vld.h>
#include "stack.h"

int main() {
	Stack<int> s;
	for (int i = 1; i <= 10; i++) {
		s.push(i * 2);
	}

	for (int i = 1; i <= 10; i++) {
		std::cout << s.top() << ' ';
		s.pop();
	}

	std::cout << std::endl;
	
	for (int i = 1; i <= 10; i++) {
		s.push(i * 3);
	}

	for (int i = 1; i <= 10; i++) {
		std::cout << s.top() << ' ';
		s.pop();
	}
	std::cout << std::endl;

	for (int i = 1; i <= 10; i++) {
		s.push(i * 10);
	}

	Stack<int> s2 = s;
	for (int i = 1; i <= 10; i++) {
		std::cout << s.top() << ' ';
		s.pop();
	}
	std::cout << std::endl;

	for (int i = 1; i <= 10; i++) {
		std::cout << s2.top() << ' ';
		s2.pop();
	}
	std::cout << std::endl;

	return 0;
}
