#include <deque>
#include "Screen.h"
#include "rendering.h"
#include "charmaps.h"
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
	rendering::renderCharMap(charmaps::title, { float(x), 10 }, Color::CYAN);
}