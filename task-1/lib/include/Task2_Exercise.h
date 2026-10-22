#pragma once

#include "Exercise.h"

/**
 * @brief Класс Task2_Exercise абстрактного класса Exercise
 * Задание: вставить перед всеми строками, первый элемент которых делится на 3,
 * строку из нулей
 */
class Task2_Exercise : public Exercise
{
public:
	/**
	 * @brief Конструктор
	 * @param src - ссылка на матрицу
	 * @param gen - ссылка на генератор
	 */
	Task2_Exercise(Matrix& src, const Generator& gen);

	/**
	 * @brief Перегруженный деструктор
	 */
	~Task2_Exercise() override = default;

	/**
	 * @brief Выполнить задание 2
	 * @return Выполненное задание (новая матрица)
	 */
	Matrix solve() override;
};
