#pragma once
#include <vector>
#include <map>
#include "colors.h"
#include "position.h"



class Block
{
public:
	Block();
	void Draw(int offsetX, int offsetY);
	void Move(int row, int column);
	std::vector<Position> getCellPositions();
	void Rotate(); 
	void UndoRotation();
	int id;
	std::map <int, std::vector<Position>> cells;
private:
	int cellSize;
	int rotationState;
	int rowOffset;
	int columnOffset;
	std::vector<Color> colors;
};
