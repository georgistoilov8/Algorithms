#include "Student.h"

Student::Student(const std::string& new_name, unsigned id):name(new_name), unique_id(id) {}

Student::Student(const Student& other) {
	name = other.name;
	unique_id = other.unique_id;
}

Student& Student::operator=(const Student& rhs) {
	if (this != &rhs) {
		name = rhs.name;
		unique_id = rhs.unique_id;
	}
	return *this;
}

std::string Student::getName() const {
	return name;
}

unsigned Student::getId() const {
	return unique_id;
}