#include "game.h"
#include "gameplay.h"
#include "utils.h"

unsigned short width = rendering::width / 2, height = rendering::height;
unsigned short maxWidth = width - 1, maxHeight = height - 1;

std::deque<Vector2D> snakeParts = { { 10, 2 }, { 9, 2 }, { 8, 2 }, { 7, 2 }, { 6, 2 } };
Vector2D velocity = { 1, 0 };
unsigned int score = 0, highestScore = 0;
Color snakeColor = Color::GRAY, snakeSecondColor = Color::GRAY;
wchar_t block = rendering::FULL_BLOCK;
bool took = false;
bool shouldGrow = false;
extern Map map;

void moveSnake(Vector2D delta_xy)
{
	if (delta_xy)
	{
		snakeParts.push_front(snakeParts.at(0) + delta_xy);

		if (!shouldGrow) snakeParts.pop_back();

		shouldGrow = false;
	}
}

void renderSnake()
{
	auto color = utils::switchValuesByTimeLapse(snakeColor, snakeSecondColor, 3);

	for (const auto &part : snakeParts)
	{
		rendering::renderChar(block, { part.x * 2, part.y }, color);
		rendering::renderChar(block, { part.x * 2 + 1, part.y }, color);
	}
}

void renderScore(float x, float y)
{
	rendering::renderText((L"SCORE: " + std::to_wstring(score)).c_str(), { x, y }, Color::GRAY | Color::BACK_BLACK);
}
