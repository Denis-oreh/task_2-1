#include "../include/ConstGenerator.h"

ConstGenerator::ConstGenerator(const int value) : const_value(value) {}

int ConstGenerator::generate() const
{
	return const_value;
}
