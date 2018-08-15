#include "Screen.h"
#include "gameplay.h"
#include "rendering.h"
#include "utils.h"
#include "charmasks.h"
#include "maps.h"

static Vector2D itemPosition = { 22, 3 };
static Color itemColor = maps::secret.color;
extern Map map;
int scoreWidth();

namespace secretScreen
{
	Color color = Color::BACK_CYAN, itemBackColor = Color::BACK_YELLOW;
	Color doorBackColor = Color::BACK_CYAN;
}

static void renderItem()
{
	rendering::renderChar(rendering::LOWER_SQUARE, { itemPosition.x * 2, itemPosition.y }, itemColor);
	rendering::renderChar(rendering::UPPER_SQUARE, { itemPosition.x * 2 + 1, itemPosition.y }, itemColor);
}

void renderContainer()
{
	float min_x = 32, max_x = 56;
	for (float y = 1; y < 5; ++y)
	{/*
		rendering::renderBlock({ min_x,     y }, Color::CYAN);
		rendering::renderBlock({ min_x + 1, y }, Color::CYAN);
		rendering::renderBlock({ max_x,     y }, Color::CYAN);
		rendering::renderBlock({ max_x + 1, y }, Color::CYAN);*/

		for (float x = min_x + 2; x < max_x; ++x)
		{
			rendering::renderSoftBlock({ x, y }, Color::CYAN);
		}
	}
}

void SecretScreen::init()
{
	for (auto & part : snakeParts)
		part.y += height;
}

void SecretScreen::KeyUp()
{
	if (velocity.y != 1)
		velocity = { 0, -1 };
}

void SecretScreen::KeyLeft()
{
	if (velocity.x != 1)
		velocity = { -1, 0 };
}

void SecretScreen::KeyDown()
{
	if (velocity.y != -1)
		velocity = { 0, 1 };
}

void SecretScreen::KeyRight()
{
	if (velocity.x != -1)
		velocity = { 1, 0 };
}

static bool doorCondition()
{
	auto &head = snakeParts.at(0);
	return head.x > 0 && head.x * 2 < scoreWidth() && head.y >= maxHeight;
}

static bool mapIsOcupyingPosition(const Vector2D & position)
{
	return maps::secret.data[int(maps::secret.width * position.y + position.x)] == '#';
}

static void sendSnake()
{
	velocity = { 1, 0 };
	snakeParts = { { 10, 1 },{ 9, 1 },{ 8, 1 },{ 7, 1 },{ 6, 1 } };
	game::setScreen(PLAYING);
}

void SecretScreen::update()
{
	itemColor = utils::switchValuesByTimeLapse(maps::secret.color, Color::GRAY, 3);
	secretScreen::itemBackColor = utils::switchValuesByTimeLapse(Color::BACK_YELLOW, Color::BACK_GRAY, 4);
	secretScreen::doorBackColor = utils::switchValuesByTimeLapse(Color::BACK_CYAN, Color::BACK_GRAY, 4);

	auto &head = snakeParts.at(0);

	if (doorCondition() && velocity.y > 0)
	{
		for (auto & part : snakeParts)
			part.y -= height;

		game::setScreen(PLAYING);
		return;
	}

	if (!doorCondition() && mapIsOcupyingPosition(head))
	{
		sendSnake();
	}

	if (snakeParts.at(0) == itemPosition && !took)
	{
		took = true;
		score += 1000;
		snakeColor = map.color;
		powerUp();

		velocity = { 0, -1 };
		snakeParts = { { 30, float(maxHeight) },{ 30, float(maxHeight + 1) },{ 30, float(maxHeight + 2) },{ 30, float(maxHeight + 3) },{ 30, float(maxHeight + 4) } };
		game::setScreen(PLAYING);
	}

	this->reactToKeys();

	moveSnake(velocity);
}

void SecretScreen::render()
{
	rendering::renderMap(maps::secret);
	renderScore(1, height - 1);
	if (!took)
	{
		rendering::renderCharMap(charmasks::misterious, { 10, 20 }, rendering::SOFT_BLOCK, Color::CYAN);
		renderItem();
	}
	renderSnake();
}
