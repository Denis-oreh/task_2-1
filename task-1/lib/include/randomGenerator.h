#pragma once

#include <random>

#include "Generator.h"

/**
 * @brief Генератор случайных чисел в диапазоне от minValue до maxValue
 */
class RandomGenerator : public Generator
{
private:
	/**
	 * @brief Минимальное значение диапазона генерации
	 */
	int minValue;

	/**
	 * @brief Максимальное значение диапазона генерации
	 */
	int maxValue;

	/**
	 * @brief Движок генерации псевдослучайных чисел
	 */
	mutable std::mt19937 engine;

	/**
	 * @brief Распределение для движка
	 */
	mutable std::uniform_int_distribution<int> distribution;
public:
	/**
	 * @brief Конструктор
	 * @param minVal - минимальное значение диапазона
	 * @param maxVal - максимальное значение диапазона
	 */
	RandomGenerator(int minVal, int maxVal);

	/**
	 * @brief Перегруженный деструктор
	 */
	~RandomGenerator() override = default;

	/**
	 * @brief Генерация случайного числа
	 * @return сгенерированное число
	 */
	int generate() const override;
};
