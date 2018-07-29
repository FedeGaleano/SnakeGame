#include <deque>
#include "Vector2D.h"
#include "Screen.h"
#include "rendering.h"
#include "input.h"
#include "game.h"
#include "utils.h"

static unsigned short width = rendering::width / 2, height = rendering::height;
static unsigned short maxWidth = width - 2, maxHeight = height - 2;

static Vector2D foodPosition = { 20, 20 };
static Vector2D velocity = { 1, 0 };
static bool shouldGrow = false;
static std::deque<Vector2D> snakeParts = { { 10, 2 },{ 9, 2 },{ 8, 2 },{ 7, 2 },{ 6, 2 } };
static unsigned int score = 0;

static bool selfCollided()
{
	bool did = false;

	for (auto it = snakeParts.begin() + 1; it != snakeParts.end(); ++it)
		if (snakeParts.at(0) == *it)
			did = true;
	return did;
}

static void setRandomXY(Vector2D &coord)
{
	coord.x = random::between(1, maxWidth);
	coord.y = random::between(1, maxHeight);
}

static bool snakeIsOccupiyingPosition(Vector2D coord)
{
	for (auto &part : snakeParts)
		if (part == coord)
			return true;
	return false;
}

void placeNewFood()
{
	do setRandomXY(foodPosition);
	while (snakeIsOccupiyingPosition(foodPosition));
}

void moveSnake(Vector2D delta_xy)
{
	snakeParts.push_front(snakeParts.at(0) + delta_xy);

	if (!shouldGrow) snakeParts.pop_back();

	shouldGrow = false;
}

static void renderFood()
{
	rendering::renderBlock({ foodPosition.x * 2, foodPosition.y }, Color::YELLOW);
	rendering::renderBlock({ foodPosition.x * 2 + 1, foodPosition.y }, Color::YELLOW);
}

static void renderSnake()
{
	for (const auto &part : snakeParts)
	{
		rendering::renderBlock({ part.x * 2, part.y });
		rendering::renderBlock({ part.x * 2 + 1, part.y });
	}
}

static void renderScore()
{
	rendering::renderText((L"SCORE: " + std::to_wstring(score)).c_str(), { 1, 0 }, Color::GRAY | Color::BACK_BLACK);
}

void PlayingScreen::KeyUp()
{
	if (velocity.y != 1)
		velocity = { 0, -1 };
}

void PlayingScreen::KeyLeft()
{
	if (velocity.x != 1)
		velocity = { -1, 0 };
}

void PlayingScreen::KeyDown()
{
	if (velocity.y != -1)
		velocity = { 0, 1 };
}

void PlayingScreen::KeyRight()
{
	if (velocity.x != -1)
		velocity = { 1, 0 };
}

void PlayingScreen::update()
{
	auto &head = snakeParts.at(0);

	if (head.x < 1 || head.x > maxWidth || head.y < 1 || head.y > maxHeight || selfCollided())
	{
		game::setScreen(GAME_OVER);
		return;
	}

	if (snakeParts.at(0) == foodPosition)
	{
		++score;
		placeNewFood();
		shouldGrow = true;
	}

	this->reactToKeys();

	moveSnake(velocity);
}

void PlayingScreen::render()
{
	renderFood();
	renderSnake();
	renderScore();
}

void PlayingScreen::initialState()
{
	snakeParts = { { 10, 2 }, { 9, 2 }, { 8, 2 }, { 7, 2 }, { 6, 2 } };
	shouldGrow = false;
	score = 0;

	foodPosition = { 20, 20 };
	velocity = { 1, 0 };
}