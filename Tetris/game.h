#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void MoveBlockDown();
	void checkInput();
	Grid grid;
	bool gameOver;
	int score;
private:
	bool IsBlockOutside();
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int lines, int moveDownPoints);
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};