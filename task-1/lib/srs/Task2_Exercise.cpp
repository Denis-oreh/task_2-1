#include <vector>

#include "../include/Task2_Exercise.h"

Task2_Exercise::Task2_Exercise(Matrix& src, const Generator& gen) : Exercise(src, gen) {}

Matrix Task2_Exercise::solve()
{
	const size_t rows = source.getRows();
	const size_t columns = source.getColumns();

	if (rows == 0 || columns == 0) { return Matrix(); }

	std::vector<bool> insertBefore(rows, false);
	for (size_t i = 0; i < rows; i++)
	{
		if (source[i][0] % 3 == 0)
		{
			insertBefore[i] = true;
		}
	}

	size_t newRows = rows;
	for (size_t i = 0; i < rows; i++)
	{
		if (insertBefore[i])
		{
			newRows++;
		}
	}

	Matrix result(newRows, columns);

	size_t r = 0;
	for (size_t i = 0; i < rows; i++)
	{
		if (insertBefore[i])
		{
			r++;
		}
		for (size_t c = 0; c < columns; c++)
		{
			result[r][c] = source[i][c];
		}
		r++;
	}

	return result;
}
