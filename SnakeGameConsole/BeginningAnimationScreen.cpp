#include <deque>
#include "Screen.h"
#include "rendering.h"
#include "charmasks.h"
#include "input.h"
#include "game.h"

static short x = 0;

void BeginningAnimationScreen::KeyEnter()
{
	game::setScreen(PRESS_START);
}

void BeginningAnimationScreen::update()
{
	this->reactToKeys();
	if (x++ == 32) game::setScreen(PRESS_START);
}

void BeginningAnimationScreen::render()
{
	rendering::renderCharMap(charmasks::title, { float(x), 10 }, rendering::FULL_BLOCK, Color::CYAN);
}