#include "Screen.h"
#include "rendering.h"
#include "charmaps.h"
#include "input.h"
#include "engine.h"
#include "game.h"
#include "utils.h"

Color color = Color::GRAY;

void GameOverScreen::KeyEnter()
{
	game::setScreen(PLAYING);
}

void GameOverScreen::update()
{
	color = switchValuesByTimeLapse(Color::GRAY, Color::YELLOW, 4);
	this->reactToKeys();
}

void GameOverScreen::render()
{
	rendering::renderWalls(Color::RED);
	rendering::renderCharMap(charmaps::gameOverTitle, { 21, 12 }, color);
	rendering::renderText(L"PRESS ENTER TO RESTART, ESCAPE TO EXIT", { 27, 18 });
}