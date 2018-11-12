#pragma once

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "LinkedList.h"
#include "Student.h"
#include "DynamicArray.h"

class System {
		DynamicArray<List<Student>> konga_collection;

	public:
		System();
		~System();
		void run();
	
	private:
		void append_konga();
		void remove_last_from_konga();
		void remove_first_from_konga();
		void remove();
		void merge();
		
		void checkKongaCollection(int line_index);
		void modifyKongaCollection(int line_index);
		bool shouldAppend(Student::university_type, int line_index);
		bool isTolerant(Student::university_type, Student::university_type);
		bool isValidIndex(int index);
		void toLowerCase(char*& text);
		char* getInput(char end_symbol);
};

#endif // !SYSTEM_HEADER
