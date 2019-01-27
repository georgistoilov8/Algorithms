#include "System.h"

System::System(){}

System::~System(){}

void System::run(const char* filepath, const char* start) {
	processFile(filepath, start);
}

void System::processFile(const char* filepath, const char* start) {
	/*
		line in file: zone_1 -> zone_2 [key]; or zone_1 -> zone_2;
		zone_1 and zone_2 won't have whitespaces...
	*/
	std::fstream file(filepath);
	bool isZones = false;
	bool isKeys = false;
	std::unordered_multimap<std::string, std::string> keysInZones;
	while (!file.eof()) {
		if (file.good()) {
			std::string word;
			file >> word;
			if (word == "") {
				// skip
				// In case we have empty lines;
			}else if (word == "[zones]") {
				isZones = true;
				isKeys = false;
			}
			else if (word == "[keys]") {
				isZones = false;
				isKeys = true;
			}
			else {
				/*
					Everytime when I read from the file the first word on 
					every line is saved in variable "word". First time i use
					the variable "word" to determine if I will read Zones or
					Keys, and then it is the first word on each line.
				*/

				if (isZones) {
					/*
						Here the first word is actually the zone left from 
						->.
					*/
					std::string line;
					std::string right_side;
					file >> line;
					file >> right_side;
					std::string key = "";
					if (right_side.back() == ';') {
						right_side.erase(right_side.end()-1);
					}
					else {
						key = subtractKeyZones(file);
					}
					map.addNode(word);
					map.addNode(right_side);
					map.addEdge(word, right_side, key);
				}

				if (isKeys) {
					/*
						Here the first word is part of the key so I add it 
						to the string for the key.
					*/
					std::string key = word + ' ' + subtractKeyKeys(file);
					std::string zone;
					file >> zone;
					zone.erase(zone.end() - 1);
					map.addKey(key, zone);
				}
			}
		}
	}
	file.close();

	map.analyzeAndGenerate(start);
}

std::string System::subtractKeyZones(std::fstream& file) {
	std::string key;
	std::string word;
	file >> word;
	if (word.back() == ';') {
		/*
			In this case we have key like this: [key];
			So to remove [, ] and ; we do this:
		*/
		word.erase(word.begin());
		word.erase(word.end() - 2, word.end());
		/*
			Here we have:
			section 1 - left_side
			section 2 - right_side
			Key - word
		*/
	}
	else {
		/*
			The key here can be: [iron key];
		*/
		word.erase(word.begin()); // remove [ from [iron key];
		while (true) {
			file >> key;
			if (key.back() == ';') {
				key.erase(key.end() - 2, key.end());
				word += ' ';
				word += key;
				break;
			}
			word += ' ';
			word += key;
		}
	}
	return word;
}

std::string System::subtractKeyKeys(std::fstream& file) {
	std::string word = "";
	while (true) {
		std::string key;
		file >> key;
		if (key == "->") {
			break;
		}
		word += key;
	}
	return word;
}
