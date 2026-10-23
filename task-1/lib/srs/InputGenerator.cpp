#include <istream>

#include "../include/InputGenerator.h"

InputGenerator::InputGenerator(std::istream& input_value) : input(input_value) {}

int InputGenerator::generate() const
{
	int value = 0;
	input >> value;
	return value;
}
