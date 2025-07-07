#include <fstream>
#include <random>
#include <climits>
#pragma once

class Generator {
public:
	Generator(std::string path, std::string format, std::string sep);
	void genAscending(int size, int step, bool reversed = false, bool teeth = false, int limits = 0);
	void genRandom(int size, int min, int max, bool teeth = false, int limits = 0);
private:
	std::string path;
	std::string format;
	std::string sep;
};