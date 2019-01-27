#pragma once

#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include <iostream>
#include <fstream>
#include <string>

#include "MapZone.h"

class System {
	MapZone map;
	public:
		System();
		System(const System& other) = delete;
		System& operator=(const System& rhs) = delete;
		~System();

		void run(const char* filepath, const char* start);

	private:
		void processFile(const char* filepath, const char* start);

		std::string subtractKeyZones(std::fstream& file);
		std::string subtractKeyKeys(std::fstream& file);
};

#endif // !SYSTEM_HEADER
