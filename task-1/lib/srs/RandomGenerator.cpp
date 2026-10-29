#include <utility>

#include "../include/RandomGenerator.h"

RandomGenerator::RandomGenerator(const int minVal, const int maxVal)
	: minValue(minVal), maxValue(maxVal), engine(std::random_device{}()), distribution(0, 1)
{
	if (minValue > maxValue)
	{
		std::swap(minValue, maxValue);
	}
	distribution = std::uniform_int_distribution<int>(minValue, maxValue);
}

int RandomGenerator::generate() const
{
	return distribution(engine);
}
