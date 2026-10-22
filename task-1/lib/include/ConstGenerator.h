#pragma once

#include "Generator.h"

/**
 * @brief Класс ConstGenerator абстрактного класса Generator
 */
class ConstGenerator : public Generator
{
private:
	/**
	 * @brief значение константы
	 */
	int const_value;
public:
	/**
	 * @brief Конструктор
	 * @param value - значение, которое будет возвращать generate
	 */
	explicit ConstGenerator(int value);

	/**
	 * @brief Перегруженный деструктор
	 */
	~ConstGenerator() override = default;

	/**
	 * @brief Возвращает значение константы
	 * @return значение, заданное в конструкторе
	 */
	int generate() const override;
};
