#pragma once

#include "Exercise.h"

/**
 * @brief Класс Task1_Exercise абстрактного класса Exercise
 * Задание: заменить максимальный элемент каждой строки нулем
 */
class Task1_Exercise : public Exercise
{
public:
	/**
	 * @brief Конструктор
	 * @param src - ссылка на матрицу
	 * @param gen - ссылка на генератор
	 */
	Task1_Exercise(Matrix& src, const Generator& gen);

	/**
	 * @brief Перегруженный деструктор
	 */
	~Task1_Exercise() override = default;

	/**
	 * @brief Выполнить задание 1
	 * @return Выполненное задание (новая матрица)
	 */
	Matrix solve() override;
};
