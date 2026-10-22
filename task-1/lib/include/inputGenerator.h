#pragma once

#include <iosfwd>

#include "Generator.h"

/**
 * @brief Класс InputGenerator абстрактного класса Generator
 */
class InputGenerator : public Generator
{
private:
	/**
	 * @brief поток ввода
	 */
	std::istream& input;

public:
	/**
	 * @brief Конструктор
	 * @param input_value - ссылка на поток ввода
	 */
	explicit InputGenerator(std::istream& input_value);

	/**
	 * @brief Перегруженный деструктор
	 */
	~InputGenerator() override = default;

	/**
	 * @brief Прочитать число из потока
	 * @return прочитанное число, либо 0 при ошибке
	 */
	int generate() override;
};