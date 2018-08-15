#include <deque>
#include "Vector2D.h"
#include "Screen.h"
#include "rendering.h"
#include "input.h"
#include "game.h"
#include "utils.h"
#include "gameplay.h"
#include "maps.h"

static Vector2D foodPosition = { 20, 20 };
Map map = maps::level1;
static Color foodColor = map.color;

void setMap(const Map & selectedMap)
{
	map = selectedMap;
}

static bool selfCollided()
{
	bool did = false;

	for (auto it = snakeParts.begin() + 1; it != snakeParts.end(); ++it)
		if (snakeParts.at(0) == *it)
			did = true;
	return did;
}

static void setRandomXY(Vector2D & coord)
{
	coord.x = utils::random::between(1, maxWidth);
	coord.y = utils::random::between(1, maxHeight);
}

static bool snakeIsOccupiyingPosition(const Vector2D & coord)
{
	for (auto &part : snakeParts)
		if (part == coord)
			return true;
	return false;
}

static bool mapIsOcupyingPosition(const Vector2D & position)
{
	return map.data[int(map.width * position.y + position.x)] == '#';
}

void placeNewFood()
{
	do setRandomXY(foodPosition);
	while (snakeIsOccupiyingPosition(foodPosition) || mapIsOcupyingPosition(foodPosition));
}

static void renderFood()
{
	rendering::renderChar(rendering::LOWER_SQUARE, { foodPosition.x * 2, foodPosition.y }, foodColor);
	rendering::renderChar(rendering::UPPER_SQUARE, { foodPosition.x * 2 + 1, foodPosition.y }, foodColor);
}

int scoreWidth()
{
	return (L"SCORE: " + std::to_wstring(score)).size();
}

static bool doorCondition()
{
	auto &head = snakeParts.at(0);
	return head.x > 0 && head.x * 2 + 1 <= scoreWidth() && head.y < 1;
}

static void normalWallCollisionLogic (Vector2D & head)
{
	if (!doorCondition() && mapIsOcupyingPosition(head))
		game::setScreen(GAME_OVER);
}

static void powerUpWallCollisionLogic (Vector2D & head)
{
	if (!doorCondition())
	{
		head.x = utils::math::modulus(head.x, width);
		head.y = utils::math::modulus(head.y, height);
	}
}

static void(*wallCollisionLogic)(Vector2D & head) = normalWallCollisionLogic;

void powerUp()
{
	wallCollisionLogic = powerUpWallCollisionLogic;
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
	if (selfCollided())
	{
		game::setScreen(GAME_OVER);
		return;
	}

	if (doorCondition() && velocity.y < 0)
	{
		game::setScreen(SECRET);
		return;
	}

	if (snakeParts.at(0) == foodPosition)
	{
		score += map.points;
		placeNewFood();
		shouldGrow = true;
	}

	wallCollisionLogic(snakeParts.at(0));

	foodColor = utils::switchValuesByTimeLapse(map.color, Color::GRAY, 3);

	this->reactToKeys();

	moveSnake(velocity);
}

void PlayingScreen::render()
{
	rendering::renderMap(map);
	renderFood();
	renderSnake();
	renderScore(1, 0);
}

void PlayingScreen::initialState()
{
	extern bool beaten;

	snakeParts = { { 10, 1 }, { 9, 1 }, { 8, 1 }, { 7, 1 }, { 6, 1 } };
	shouldGrow = false;
	score = 0;
	foodColor = map.color;
	snakeColor = snakeSecondColor = Color::GRAY;
	block = rendering::FULL_BLOCK;
	took = false;
	wallCollisionLogic = normalWallCollisionLogic;
	beaten = false;

	placeNewFood();
	velocity = { 1, 0 };
}
