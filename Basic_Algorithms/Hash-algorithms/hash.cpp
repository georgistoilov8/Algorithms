#include <iostream>

int simple_hash(const char* text) {
	/*
		The problem here is if we give this two words for example: "abc" and "cba" the hash will be the same
	*/ 
	int result = 0;
	while (*text) {
		result += *text++;
	}
	return result;
}

int advanced_hash(const char* text) {
	/*
		Two problems here. If we have module division and our module is small then we will have a lot of
		repeating numbers. In our case if our module is 10, then every char* will be transormed into numbers
		between 0 and 10. To fix this we can make the module bigger. In our requirement we need for every number
		to have no more than 5 words. Each word has 32 symbols. Well 2^32 is 4294967296, so the new module is 
		for example: 1 000 000 000. This means we can generate 1 bilion numbers. In that case the requirement for
		the number of words in each hash is done. 

		Second problem: 256 and 1 000 000 000 are even numbers. This means they will have common devisor.
		For example 2 devides 256 and 1 000 000 000. When the numbers are even we will miss some of the
		hash numbers. Example: Our module is 4 and we multiply by 2. Our hash numbers are 0, 1, 2, 3.
		But we can't generate hash numbers 1 and 3 because every number multiply by two gives even number.
		To fix that our numbers 4 and 2 must be coprime. Or 256 and 1 000 000 000 must be coprime.
	*/
	long long int result = 0;
	//int mod = 10;
	//int mod = 1000000000;
	int mod = 1000000007;
	while (*text) {
		//result = ((result * 256) + *text++) % mod;
		result = (long long)((result * 257) + *text++) % mod;
	}
	return result;
}

int number_hash(int number) {
	return number % 100;
}

int main() {
	
	std::cout << "Generated hash for string \"Georgi\": " << simple_hash("Georgi") << std::endl;
	std::cout << "Generated hash for string \"Stoilov\": " << simple_hash("Stoilov") << std::endl;
	std::cout << "Generated hash for string \"Levski\": " << simple_hash("Levski") << std::endl;
	std::cout << "Generated hash for string \"Albus Dumbledore\": " << simple_hash("Albus Dumbledore") << std::endl;
	std::cout << "Generated hash for string \"Hulk\": " << simple_hash("Hulk") << std::endl;
	std::cout << "Generated hash for string \"Thanos\": " << simple_hash("Thanos") << std::endl;
	/* Example of the problem with simple hash */
	std::cout << "Why simple_hash is not very good:" << std::endl;
	std::cout << "Generated hash for string \"abc\": " << simple_hash("abc") << std::endl;
	std::cout << "Generated hash for string \"cba\": " << simple_hash("cba") << std::endl;
	
	std::cout << std::endl;
	std::cout << "Next type of hash function:" << std::endl;
	std::cout << std::endl;

	std::cout << "Generated hash for string \"Georgi\": " << advanced_hash("Georgi") << std::endl;
	std::cout << "Generated hash for string \"Stoilov\": " << advanced_hash("Stoilov") << std::endl;
	std::cout << "Generated hash for string \"Levski\": " << advanced_hash("Levski") << std::endl;
	std::cout << "Generated hash for string \"Albus Dumbledore\": " << advanced_hash("Albus Dumbledore") << std::endl;
	std::cout << "Generated hash for string \"Hulk\": " << advanced_hash("Hulk") << std::endl;
	std::cout << "Generated hash for string \"Thanos\": " << advanced_hash("Thanos") << std::endl;

	std::cout << std::endl;
	std::cout << "Next type of hash function:" << std::endl;
	std::cout << std::endl;

	std::cout << "Generated hash for number \"50\": " << number_hash(50) << std::endl;
	std::cout << "Generated hash for number \"142\": " << number_hash(142) << std::endl;
	std::cout << "Generated hash for number \"1999\": " << number_hash(1999) << std::endl;
	std::cout << "Generated hash for number \"35324\": " << number_hash(35324) << std::endl;

	return 0;
}