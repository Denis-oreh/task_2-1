#include "../include/ConstGenerator.h"

ConstGenerator::ConstGenerator(int value) : const_value(value) {}

int ConstGenerator::generate()
{
	return const_value;
}