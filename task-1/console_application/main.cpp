#include <iostream>
#include <cstdlib>
#include <memory>

#include "../lib/include/Matrix.h"
#include "../lib/include/RandomGenerator.h"
#include "../lib/include/ConstGenerator.h"
#include "../lib/include/InputGenerator.h"
#include "../lib/include/Task1_Exercise.h"
#include "../lib/include/Task2_Exercise.h"

/**
 * @brief enum для выбора генератора
 */
enum gen { random_fill, const_fill, input_fill };

/**
 * @brief enum для выбора задания
 */
enum task { task1_choice, task2_choice };

/**
 * @brief Функция для получения целого положительного числа
 * @param message - сообщение
 * @return полученное число, если ввод успешен и пройдена проверка, иначе - завершает программу
 */
size_t getPos(const char* message);

/**
 * @brief Функция для получения целого числа
 * @param message - сообщение
 * @return полученное число, если ввод успешен, иначе - завершает программу
 */
int getInt(const char* message);

/**
 * @brief Функция выбора генератора
 * @param message - сообщение
 * @return умный указатель на выбранный генератор
 */
std::unique_ptr<Generator> chooseGenerator(const char* message);

/**
 * @brief Функция выбора задания
 * @param matrix - ссылка на матрицу
 * @param generator - константная ссылка на генератор
 */
void runTask(Matrix& matrix, const Generator& generator);

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена успешно
 */
int main(void) {
	const size_t rows = getPos("Введите количество строк:");
	const size_t columns = getPos("Введите количество столбцов:");

	Matrix matrix(rows, columns);
	
	auto generator = chooseGenerator("Выберите тип заполнения массива:");
	matrix.fillArray(*generator);

	std::cout << "Полученная матрица:\n" << matrix.toString() << std::endl;

	runTask(matrix, *generator);
	return 0;
}

size_t getPos(const char* message)
{
	size_t value = 0;
	std::cout << message << std::endl;
	if (std::cin >> value && value > 0)
	{
		return value;
	}
	std::cerr << "Некорректный ввод (введено не целое положительное число)" << std::endl;
	std::exit(1);
}

int getInt(const char* message)
{
	int value = 0;
	std::cout << message << std::endl;
	if (std::cin >> value) return value;
	std::cerr << "Некорректный ввод (введено не целое число)" << std::endl;
	std::exit(1);
}

std::unique_ptr<Generator> chooseGenerator(const char* message)
{
	std::cout << message << std::endl;
	std::cout << random_fill << " - случайными числами\n"
		<< const_fill << " - одинаковым числом (константой)\n"
		<< input_fill << " - ввод с клавиатуры\n" << std::endl;
	int var = getInt("");
	switch (var)
	{
		case random_fill:
			{
			int minVal = getInt("Введите минимум диапазона:");
			int maxVal = getInt("Введите максимум диапазона:");
			return std::make_unique<RandomGenerator>(minVal, maxVal);
		}
		case const_fill:
			{
			int value = getInt("Введите значение константы:");
			return std::make_unique<ConstGenerator>(value);
		}
		case input_fill:
			{
			std::cout << "Введите значения массива:" << std::endl;
			return std::make_unique<InputGenerator>(std::cin);
		}
		default:
			std::cerr << "Некорректный выбор" << std::endl;
			std::exit(1);
	}
}

void runTask(Matrix& matrix, const Generator& generator)
{
	std::cout << "Выберите задание:\n"
		<< task1_choice << " - Задание 1. Заменить максимальный элемент каждой строки нулем\n"
		<< task2_choice << " - Задание 2. Вставить перед строками, первый элемент которых делится на 3, строку из нулей" << std::endl;
	const int var = getInt("");

	switch (var)
	{
		case task1_choice:
			{
			Task1_Exercise task(matrix, generator);
			Matrix result = task.solve();
			std::cout << "Результат:\n" << result.toString() << std::endl;
			break;
		}
		case task2_choice:
			{
			Task2_Exercise task(matrix, generator);
			Matrix result = task.solve();
			std::cout << "Результат:\n" << result.toString() << std::endl;
			break;
		}
		default:
			std::cerr << "Некорректный выбор" << std::endl;
			std::exit(1);
	}
}
