#pragma once

#ifndef SYSTEM_HEADER
#define SYSTEM

#include <iostream>
#include <fstream>
#include <string>

#include "Student.h"

class System {
	// queue from students
	public:
		System();
		System(const System& other) = delete;
		System& operator=(const System& rhs) = delete;
		~System();

		void start(const char* filepath);
};

#endif // !SYSTEM_HEADER
