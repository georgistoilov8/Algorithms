#pragma once

#ifndef STUDENT_HEADER
#define STUDENT_HEADER

#include <iostream>

class Student {
	public:
		enum university_type { FMI, UNSS, TU, EMPTY };
	private:
		char* name;
		university_type university;

	public:
		Student();
		Student(const char*, university_type);
		Student(const Student& other);
		Student& operator=(const Student& other);
		~Student();

		void print_information(bool isLast) const;
		university_type get_university() const;

		char* get_name() const;
	private:
		void copy_student(const Student& other);
		void clear();

		void copy_name(const char* name);
};
#endif // !PERSON_INCLUDED
