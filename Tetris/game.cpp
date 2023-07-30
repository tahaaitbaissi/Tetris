#include "game.h"
#include <random>

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
}

Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return { LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw(11, 11);
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255, 280);
		break;
	default:
		nextBlock.Draw(270, 270);
	}
}

void Game::MoveBlockDown()
{
	if (!gameOver) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || !BlockFits())
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::checkInput()
{
	if (gameOver && GetKeyPressed() != 0)
	{
		gameOver = false;
		Reset();
	}
	switch (GetKeyPressed())
	{
	case KEY_LEFT:
		if (!gameOver) {
			currentBlock.Move(0, -1);
			if (IsBlockOutside() || !BlockFits())
				currentBlock.Move(0, 1);
		}
		break;
	case KEY_RIGHT:
		if (!gameOver) {
			currentBlock.Move(0, 1);
			if (IsBlockOutside() || !BlockFits())
				currentBlock.Move(0, -1);
		}
		break;
	case KEY_DOWN:
		MoveBlockDown();
		UpdateScore(0, 1);
		break;
	case KEY_UP:
		if (!gameOver) {
			currentBlock.Rotate();
			if (IsBlockOutside())
				currentBlock.UndoRotation();
		}
		break;
	}
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.column))
		{
			return true;
		}
	}
	return false;
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	UpdateScore( grid.ClearFullRows(), 0);
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row, item.column) == false)
		{
			return false;
		}
	}
	return true;
}

void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
}

void Game::UpdateScore(int lines, int moveDownPoints)
{
	switch (lines)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	}
	score += moveDownPoints;
}


