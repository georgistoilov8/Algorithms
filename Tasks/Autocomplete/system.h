#pragma once

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include <iostream>
#include <string>
#include <fstream>

#include "automata.h"
class System {

	Automata automata;

	public:
		System() = default;
		System(const System& other) = delete;
		System& operator=(const System& rhs) = delete;
		~System() = default;

		void start(const std::string filepath, int K);
};

#endif // !SYSTEM_HEADER
