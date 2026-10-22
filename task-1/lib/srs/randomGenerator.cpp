#include <utility>

#include "../include/RandomGenerator.h"

RandomGenerator::RandomGenerator(int minVal, int maxVal)
	: minValue(minVal), maxValue(maxVal), engine(std::random_device{}()), distribution(0, 0)
{
	if (minValue > maxValue)
	{
		std::swap(minValue, maxValue);
	}
	distribution = std::uniform_int_distribution<int>(minValue, maxValue);
}

int RandomGenerator::generate()
{
	return distribution(engine);
}