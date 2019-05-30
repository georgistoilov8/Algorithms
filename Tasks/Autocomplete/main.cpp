#include <iostream>
#include "system.h"

int main(int argc, char* argv[]) {
	
	int suggestions_count;
	std::cout << "Please give number of suggestions you want to see: ";
	std::cin >> suggestions_count;
	std::cin.ignore();
	System s;
	s.start(argv[1], suggestions_count);
	
	return 0;
}
