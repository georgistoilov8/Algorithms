#include <iostream>
#include "system.h"

int main(int argc, char* argv[]) {
	
	int k;
	std::cout << "Please give number of suggestions you want to see: ";
	std::cin >> k;
	std::cin.ignore();
	System s;
	s.start(argv[1], k);
	
	return 0;
}