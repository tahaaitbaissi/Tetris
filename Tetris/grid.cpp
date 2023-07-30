#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialize();
	colors = getCellColors();
}

void Grid::Initialize()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void Grid::Print()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


void Grid::Draw()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			int cellVal = grid[i][j];
			DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellVal]);
		}
	}
}

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numCols)
	{
		return false;
	}
	return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}
	return false;
}

int Grid::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::IsRowFull(int row)
{
	for (int i = 0; i < numCols; i++)
	{
		if (grid[row][i] == 0)
			return false;
	}
	return true;
}

void Grid::ClearRow(int row)
{
	for (int i = 0; i < numCols; i++)
	{
		grid[row][i] = 0;
	}
}

void Grid::MoveRowDown(int row, int numRows)
{
	for (int i = 0; i < numCols; i++)
	{
		grid[row + numRows][i] = grid[row][i];
		grid[row][i] = 0;
	}
}
