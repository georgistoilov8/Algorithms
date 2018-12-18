#include "System.h"

System::System(){}

System::~System(){}

void System::start(const char* filepath) {
	std::fstream file(filepath);

	while (!file.eof()) {
		if (file.good()) {
			std::string name;
			unsigned id;

			file >> name;
			file >> id;
			Student new_student(name, id);
			std::cout << name << " --- " << id << std::endl;
		}
	}

	file.close();
}