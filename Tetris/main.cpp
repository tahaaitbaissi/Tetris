#include <iostream>
#include <raylib.h>
#include "game.h"

const int WIDTH = 500;
const int HEIGHT = 620;

double LastUpdateTime = 0;

bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - LastUpdateTime >= interval)
	{
		LastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main(void)
{
	
	InitWindow(WIDTH, HEIGHT, "Tetris");
	SetWindowState(FLAG_VSYNC_HINT);

	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

	Game game;

	while (!WindowShouldClose())
	{
		game.checkInput();
		if (EventTriggered(0.3)) 
			game.MoveBlockDown();
		BeginDrawing();
		
		ClearBackground(DARKGRAY);
		DrawTextEx(font, "Score", { 365, 15 }, 38, 2 ,WHITE);
		DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
		if (game.gameOver)
			DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, LIGHTGRAY);

		char scoreText[10];
		sprintf_s(scoreText, 10, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, LIGHTGRAY);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}