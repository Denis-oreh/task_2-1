#pragma once
#include <iosfwd>
#include <string>
#include <vector>

#include "Generator.h"

/**
 * @brief Класс Matrix(массив) на std::vector
 */
class Matrix
{
private:
	/**
	 * @brief количество строк в массиве
	 */
	size_t rows;

	/**
	 * @brief количество столбцов в массиве
	 */
	size_t columns;

	/**
	 * @brief двумерный массив на std::vector
	 */
	std::vector<std::vector<int>> arr;
public:
	/**
	 * @brief Конструктор по умолчанию
	 */
	Matrix();

	/**
	 * @brief Конструктор матрицы rows * columns, заполненной нулями
	 * @param r - количество строк массива
	 * @param c - количество столбцов массива
	 */
	Matrix(const size_t r, const size_t c);

	/**
	 * @brief Конструктор копирования (глубокое копирование обеспечивает vector)
	 * @param other - ссылка на другую матрицу
	 */
	Matrix(const Matrix& other) = default;

	/**
	 * @brief Конструктор перемещения (обнуляет rows/columns у источника)
	 * @param other - ссылка на другую (временную) матрицу
	 */
	Matrix(Matrix&& other) noexcept;

	/**
	 * @brief Деструктор (RAII: vector сам освобождает память)
	 */
	~Matrix() = default;

	/**
	 * @brief оператор присваивания копированием
	 * @param other - ссылка на другую матрицу
	 * @return ссылку на скопированную матрицу
	 */
	Matrix& operator=(const Matrix& other) = default;

	/**
	 * @brief оператор присваивания перемещением (обнуляет rows/columns у источника)
	 * @param other - ссылка на другую (временную) матрицу
	 * @return ссылку на перемещённую матрицу
	 */
	Matrix& operator=(Matrix&& other) noexcept;

	/**
	 * @brief перегрузка оператора сдвига влево
	 * @param os - поток вывода
	 * @param M - ссылка на матрицу M
	 * @return перегруженный поток вывода
	 */
	friend std::ostream& operator<<(std::ostream& os, const Matrix& M);

	/**
	 * @brief перегрузка оператора сдвига вправо
	 * @param is - поток ввода
	 * @param M - ссылка на матрицу M
	 * @return перегруженный поток ввода
	 */
	friend std::istream& operator>>(std::istream& is, Matrix& M);

	/**
	 * @brief оператор "равно"
	 * @param other - ссылка на другую матрицу
	 * @return 1 - если матрицы равны, иначе 0
	 */
	bool operator==(const Matrix& other) const;

	/**
	 * @brief оператор "не равно"
	 * @param other - ссылка на другую матрицу
	 * @return 1 - если матрицы не равны, иначе 0
	 */
	bool operator!=(const Matrix& other) const;

	/**
	 * @brief Вывести содержимое массива в строку
	 * @return Содержимое строки
	 */
	std::string toString() const;

	/**
	 * @brief Получить указатель на строку по индексу (только чтение)
	 * @param index - номер элемента
	 * @return элемент по индексу
	 */
	const int* operator[](const size_t index) const;

	/**
	 * @brief получить указатель на строку по индексу
	 * @param index - номер элемента
	 * @return элемент по индексу
	 */
	int* operator[](const size_t index);

	/**
	 * @brief Функция получения количества строк массива
	 * @return число строк
	 */
	size_t getRows() const noexcept;

	/**
	 * @brief Функция получения количества столбцов массива
	 * @return число столбцов
	 */
	size_t getColumns() const noexcept;

	/**
	 * @brief Заполнение массива, используя абстрактный класс Generator
	 * @param generator - ссылка на генератор
	 */
	void fillArray(Generator& generator);
};
