#include "system.h"

void System::start(const std::string filepath, int K) {
	std::ifstream inFile(filepath);
	int number_words = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
	inFile.close();
	std::fstream file(filepath);

	std::vector<std::string> words(number_words+1);
	std::string phrase;
	int counter = 0;
	while (!file.eof()) {
		if (file.good()) {
			std::getline(file, phrase);
			words[counter] = phrase;
			counter++;
		}
	}
	file.close();
	
	std::cout << "File loaded.\n";
	automata.construct(words);

	words.clear();
	words.shrink_to_fit();

	int k = K;
	const std::string changeK = "/changeK";
	const std::string insertWord = "/insert";
	const std::string memoryInformation = "/memory";
	//const int size = changeK.size();
	while (true) {
		std::cout << "Try me: ";
		std::string command;
		std::cin >> command;
		//std::getline(std::cin, input);
		if (command == "/exit") {
			return;
		}
		//std::string temp_str = input.substr(0, size);
		if (command == changeK) {
			//std::cout << "Please insert new number of suggestions: ";
			int new_k;
			std::cin >> new_k;
			k = new_k;
			std::cin.ignore();
			std::cout << "Number of suggestions changed successfully.\n";
		}
		else if (command == insertWord) {
			//std::cout << "Please insert new phrase: ";
			std::string new_word;
			std::getline(std::cin, new_word);
			//std::cin.ignore();
			automata.addWord(new_word);
			std::cout << "Word inserted successfully.\n";
		}
		else if (command == memoryInformation) {
			std::cout << "Memory used: ";
			automata.printMemoryUsage();
			std::cout << " bytes.\n";
		}
		else {
			std::string input;
			std::getline(std::cin, input);
			std::string final_string = input.size() ? command + " " + input : command;
			//automata.search(input) ? std::cout << "Found\n" : std::cout << "Not Found\n";
			automata.printAutoSuggestions(final_string, k);
		}
		
	}
}