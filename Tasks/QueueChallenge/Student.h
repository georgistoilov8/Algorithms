#pragma once

#ifndef STUDENT_HEADER
#define STUDENT

#include <string>

class Student {
	std::string name;
	unsigned unique_id;

public:
	Student(const std::string& new_name, unsigned id);
	Student(const Student& other);
	Student& operator=(const Student& rhs);
	~Student() = default;

	std::string getName() const;

	unsigned getId() const;
};

#endif // !STUDENT_HEADER
