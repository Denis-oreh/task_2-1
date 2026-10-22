#include "../include/Task1Exercise.h"

Task1Exercise::Task1Exercise(Matrix& src, const Generator& gen) : Exercise(src, gen) {}

Matrix Task1Exercise::solve()
{
	Matrix result(source);

	const size_t rows = result.getRows();
	const size_t columns = result.getColumns();

	if (rows == 0 || columns == 0) { return result; }

	for (size_t i = 0; i < rows; i++)
	{
		// Íàõîäèì èíäåêñ ïåðâîãî ìàêñèìàëüíîãî ýëåìåíòà â ñòðîêå
		size_t maxCol = 0;
		int maxValue = result[i][0];
		for (size_t j = 1; j < columns; j++)
		{
			if (result[i][j] > maxValue)
			{
				maxValue = result[i][j];
				maxCol = j;
			}
		}
		// Çàìåíÿåì ìàêñèìàëüíûé ýëåìåíò ñòðîêè íóëåì
		result[i][maxCol] = 0;
	}

	return result;
}
