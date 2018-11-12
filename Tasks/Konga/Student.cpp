#include "Student.h"

Student::Student():name(nullptr),university(university_type::EMPTY){}

Student::Student(const char* student_name, Student::university_type uni) 
:university(uni)
{
	copy_name(student_name);
}

Student::Student(const Student& other) {
	copy_student(other);
}

Student& Student::operator=(const Student& rhs) {
	if (this != &rhs) {
		clear();
		copy_student(rhs);
	}
	return *this;
}

Student::~Student() {
	clear();
}

void Student::copy_student(const Student& other) {
	copy_name(other.name);
	university = other.university;
}

void Student::clear() {
	university = university_type::EMPTY;
	delete[] name;
}

void Student::copy_name(const char* new_name) {
	int length = strlen(new_name);
	name = new char[length + 1];
	for (int i = 0; i < length; i++) {
		name[i] = new_name[i];
	}
	name[length] = '\0';
}

void Student::print_information(bool isLast) const {
	std::cout << "( " << name;
	std::cout << " - ";
	switch (university) {
		case university_type::FMI:
			std::cout << "FMI";
			break;
		case university_type::TU:
			std::cout << "TU";
			break;
		case university_type::UNSS:
			std::cout << "UNSS";
			break;
		case university_type::EMPTY:
			std::cout << "EMPTY";
			break;
	}
	std::cout << " )";
	if (!isLast) {
		std::cout << " - ";
	}
}

Student::university_type Student::get_university() const {
	return university;
}

char* Student::get_name() const {
	return name;
}