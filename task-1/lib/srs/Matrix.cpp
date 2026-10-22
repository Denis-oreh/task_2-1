#include <iostream>
#include <utility>
#include "../include/Matrix.h"

Matrix::Matrix() : rows(0), columns(0), arr() {}

Matrix::Matrix(const size_t r, const size_t c)
	: rows(r), columns(c), arr(r, std::vector<int>(c, 0))
{
	if (rows == 0 || columns == 0)
	{
		rows = 0;
		columns = 0;
		arr.clear();
	}
}

Matrix::Matrix(Matrix&& other) noexcept
	: rows(other.rows), columns(other.columns), arr(std::move(other.arr))
{
	other.rows = 0;
	other.columns = 0;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
	if (this == &other) return *this;
	rows = other.rows;
	columns = other.columns;
	arr = std::move(other.arr);
	other.rows = 0;
	other.columns = 0;
	return *this;
}

size_t Matrix::getRows() const noexcept { return rows; }

size_t Matrix::getColumns() const noexcept { return columns; }

int* Matrix::operator[](size_t row_index)
{
	return arr[row_index].data();
}

const int* Matrix::operator[](const size_t row_index) const
{
	return arr[row_index].data();
}

std::string Matrix::toString() const
{
	std::string result;
	if (rows == 0 || columns == 0)
	{
		return result;
	}
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			result += std::to_string(arr[i][j]);
			if (j + 1 < columns)
			{
				result += ' ';
			}
		}
		if (i + 1 < rows)
		{
			result += '\n';
		}
	}
	return result;
}

bool Matrix::operator==(const Matrix& other) const
{
	return rows == other.rows && columns == other.columns && arr == other.arr;
}

bool Matrix::operator!=(const Matrix& other) const
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Matrix& M)
{
	os << M.getRows() << ' ' << M.getColumns() << '\n';
	os << M.toString();
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& M)
{
	size_t newRows = 0;
	size_t newColumns = 0;
	is >> newRows >> newColumns;
	if (!is) return is;
	if ((newRows == 0) != (newColumns == 0))
	{
		is.setstate(std::ios::failbit);
		return is;
	}
	else if (newRows == 0 && newColumns == 0)
	{
		M = Matrix();
		return is;
	}
	Matrix temp(newRows, newColumns);
	for (size_t i = 0; i < newRows; i++)
	{
		for (size_t j = 0; j < newColumns; j++)
		{
			if (!(is >> temp[i][j])) return is;
		}
	}
	M = std::move(temp);
	return is;
}

void Matrix::fillArray(const Generator& generator)
{
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++)
		{
			arr[i][j] = generator.generate();
		}
	}
}
