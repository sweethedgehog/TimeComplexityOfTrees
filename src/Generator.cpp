#include "Generator.h"

std::random_device rand_dev;
std::mt19937 generator (rand_dev());
std::uniform_int_distribution<> distrC(0, 1);

Generator::Generator(std::string path, std::string format, std::string sep) {
	this->path = path;
	this->format = format;
	this->sep = sep;
}
void Generator::genAscending(int size, int step, bool reversed, bool teeth, int limits) {
	std::ofstream outfile(path + R"(\data\Ascending_)" + std::to_string(size) + (reversed ? "_reversed" : "") +
		(teeth ? "_teethed" : "") + (limits ? "_limited" : "") + "." + format);
	for (int i = (size - 1) * reversed; i < size && i >= 0; i += step * (reversed ? -1 : 1)) {
		if (limits ? !(i % limits) : false) {
			if (distrC(generator)) outfile << INT_MAX << sep;
			else outfile << INT_MIN << sep;
		}
		else if (!teeth || i % 2) outfile << i << sep;
		else outfile << size - size % 2 - i << sep;
	}
	outfile.close();
}
void Generator::genRandom(int size, int min, int max, bool teeth, int limits) {
	std::uniform_int_distribution<> distr(min, max / (teeth ? 2 : 1));
	std::ofstream outfile(path + R"(\data\Random_)" + std::to_string(size) +
		(teeth ? "_teethed" : "") + (limits ? "_limited" : "") + "." + format);
	for (int i = 0; i < size; ++i) {
		if (limits ? !(i % limits) : false) {
			if (distrC(generator)) outfile << INT_MAX << sep;
			else outfile << INT_MIN << sep;
		}
		else if (!teeth || i % 2) outfile << distr(generator) << sep;
		else outfile << max - distr(generator) << sep;
	}
	outfile.close();
}