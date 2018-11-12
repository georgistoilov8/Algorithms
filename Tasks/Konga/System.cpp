#include <iostream>
#include "System.h"

System::System() {}

System::~System(){}

void System::run() {
	const char* append_command = "append";
	const char* removeLast_command = "removeLast";
	const char* removeFirst_command = "removeFirst";
	const char* remove_command = "remove";
	const char*	merge_command = "merge";
	const char* print_command = "print";
	const char* quit_command = "quit";

	try {
		/* Initialize first konga with integralcho */
		List<Student> konga;
		konga.push_back(Student("integralcho", Student::university_type::EMPTY));
		konga_collection.push_back(konga);
		while (true) {
			if (konga_collection.get_size() == 0) {
				std::cout << "System is now empty.\n";
				break;
			}

			char* command = getInput(' ');
			if (strcmp(command, append_command) == 0) {
				append_konga();
			}
			else if (strcmp(command, removeLast_command) == 0) {
				remove_last_from_konga();
			}
			else if (strcmp(command, removeFirst_command) == 0) {
				remove_first_from_konga();
			}
			else if (strcmp(command, remove_command) == 0) {
				remove();
			}
			else if (strcmp(command, merge_command) == 0) {
				merge();
			}
			else if (strcmp(command, print_command) == 0) {
				konga_collection.print();
			}
			else if (strcmp(command, quit_command) == 0) {
				delete[] command;
				std::cout << "System is now empty.\n";
				break;
			}
			else {
				std::cout << "Unexpected command.\n";
			}
			delete[] command;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation error: " << e.what() << "\n";
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of range error: " << oor.what() << "\n";
	}
	
	std::cout << "End of the program. Goodbay!\n";
}

void System::append_konga() {
	char* name = getInput(' ');
	char* university = getInput(' ');
	int line_index;
	std::cin >> line_index;
	if (isValidIndex(line_index)) {
		toLowerCase(university);
		bool wrong_university = false;
		Student::university_type student_university;
		if (strcmp(university, "fmi") == 0) {
			student_university = Student::university_type::FMI;
		}
		else if (strcmp(university, "tu") == 0) {
			student_university = Student::university_type::TU;
		}
		else if (strcmp(university, "unss") == 0) {
			student_university = Student::university_type::UNSS;
		}
		else {
			wrong_university = true;
		}
		if (!wrong_university) {
			if (shouldAppend(student_university, line_index)) {
				Student student(name, student_university);
				konga_collection[line_index].push_back(student);
				std::cout << "Append was successful.\n";
			}
			else {
				std::cout << "Incompatible people\n";
			}
		}
		else {
			std::cout << "Unexpected university\n";
		}
	}
	else {
		std::cout << "Invalid line index.\n";
	}

	delete[] university;
	delete[] name;
}

void System::remove_last_from_konga() {
	int line_index;
	std::cin >> line_index;
	if (isValidIndex(line_index)) {
		konga_collection[line_index].pop_back();
		checkKongaCollection(line_index);
		std::cout << "Remove last was successful.\n";
	}
	else {
		std::cout << "Invalid line index.\n";
	}
}

void System::remove_first_from_konga() {
	int line_index;
	std::cin >> line_index;
	if (isValidIndex(line_index)) {
		konga_collection[line_index].pop_front();
		checkKongaCollection(line_index);
		std::cout << "Remove first was successful.\n";
	}
	else {
		std::cout << "Invalid line index.\n";
	}
}

void System::remove() {
	char* name = getInput(' ');
	int line_index;
	std::cin >> line_index;
	int count = 0;
	bool was_successful = false;
	if (isValidIndex(line_index)) {
		for (List<Student>::iterator it = konga_collection[line_index].begin(); it != konga_collection[line_index].end(); it++) {
			count++;
			if (strcmp(name, (*it).data.get_name() ) == 0) {
				if (count == 1) { // if we want to delete the first person in the line
					konga_collection[line_index].pop_front();
					checkKongaCollection(line_index);
				}
				else if (count == konga_collection[line_index].get_size()) {
					konga_collection[line_index].pop_back();
					checkKongaCollection(line_index);
				}
				else {
					List<Student>::Node* left_back = it->ptr_previous->ptr_next;
					List<Student>::Node* right_front = it->ptr_next;
					List<Student> new_line = konga_collection[line_index].remove(left_back, right_front, count);
					konga_collection.push_back(new_line);
				}
				was_successful = true;
				break;
			}
		}
		if (was_successful) {
			std::cout << "Remove was successful.\n";
		}
		else {
			std::cout << "Student not found on this line.\n";
		}
	}
	else {
		std::cout << "Invalid line index.\n";
	}
	delete[] name;
}

void System::merge() {
	int left_index, right_index;
	std::cin >> left_index;
	std::cin >> right_index;
	if (isValidIndex(left_index) && isValidIndex(right_index)) {
		if (left_index == right_index) {
			std::cout << "Trying to merge only one line. Well nice try.\n";
		}
		else {
			if (isTolerant(konga_collection[left_index].back().get_university(), konga_collection[right_index].front().get_university())) {
				konga_collection[left_index].append_and_remove(konga_collection[right_index]);
				modifyKongaCollection(right_index);
				std::cout << "Merge was successful.\n";
			}
			else {
				std::cout << "Incompatible people\n";
			}
		}
	}
	else {
		std::cout << "Invalid line index.\n";
	}
}

void System::checkKongaCollection(int line_index) {
	if (konga_collection[line_index].get_size() == 0) {
		modifyKongaCollection(line_index);
	}
}

void System::modifyKongaCollection(int line_index) {
	if (konga_collection.get_size() - 1 != line_index) {
		konga_collection[line_index] = konga_collection[konga_collection.get_size() - 1];
	}
	konga_collection.pop_back();
}

bool System::shouldAppend(Student::university_type uni_type, int line_index) {
		
	Student::university_type last_person_uni = konga_collection[line_index].back().get_university();
	
	return isTolerant(last_person_uni, uni_type);
}

bool System::isTolerant(Student::university_type left, Student::university_type right) {
	/*
		fmi толерират: fmi и tu
		tu толерират: tu и unss
		unss толерират: unss и fmi
		Всички толерират Empty, но Empty е само началният Интегралчо.
	*/
	bool append = false;
	switch (left) {
	case Student::university_type::FMI:
		if (right == Student::university_type::TU) {
			append = false;
		}
		else {
			append = true;
		}
		break;
	case Student::university_type::TU:
		if (right == Student::university_type::UNSS) {
			append = false;
		}
		else {
			append = true;
		}
		break;
	case Student::university_type::UNSS:
		if (right == Student::university_type::FMI) {
			append = false;
		}
		else {
			append = true;
		}
		break;
	case Student::university_type::EMPTY:
		append = true;
		break;
	}
	return append;
}

bool System::isValidIndex(int index) {
	return index < konga_collection.get_size();
}

void System::toLowerCase(char*& text) {
	int length = strlen(text);
	char* result = new char[length + 1];
	for (int i = 0; i < length; i++) {
		result[i] = tolower(text[i]);
	}
	result[length] = '\0';
	delete[] text;
	text = result;
}

char* System::getInput(char c) {
	char* argument = new char[8];
	char symbol;
	int position = 0;
	int capacity = 8;
	while (true) {
		std::cin.get(symbol);
		if (symbol != c && symbol != '\n') {
			if (position >= capacity) {
				char* new_memory = new char[capacity * 2];
				capacity *= 2;
				for (int i = 0; i < position; ++i) {
					new_memory[i] = argument[i];
				}
				delete[] argument;
				argument = new_memory;
			}
			argument[position] = symbol;
			position++;
		}
		else {
			if (position != 0) {
				if (position >= capacity) {
					char* new_memory = new char[capacity * 2];
					capacity *= 2;
					for (int i = 0; i < position; ++i) {
						new_memory[i] = argument[i];
					}
					delete[] argument;
					argument = new_memory;
				}
				argument[position] = '\0';
				break;
			}
		}
	}
	return argument;
}

