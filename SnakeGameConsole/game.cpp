#include <random>
#include "game.h"
#include "rendering.h"
#include "charmaps.h"
#include "Vector2D.h"
#include "Screen.h"
#include "input.h"
#include <iostream>
#include <algorithm>

Screen ** game::screens, * currentScreen;

unsigned long long int game::ticks = 0;

static void clearInput()
{
	std::queue<int> empty;
	std::swap(inputChannel::messageQueue, empty);
}

void game::setScreen(State newState)
{
	if (newState != BEGINNING_ANIMATION)
		inputChannel::closeFor(40000);

	if (newState == PLAYING)
		PlayingScreen::initialState();

	clearInput();
	game::ticks = 0;
	currentScreen = screens[newState];
}

bool game::init()
{
	screens = new Screen*[4];
	//Find the best moment to free each memory
	screens[BEGINNING_ANIMATION] = new BeginningAnimationScreen();
	screens[PRESS_START]         = new PressStartScreen();
	screens[PLAYING]             = new PlayingScreen();
	screens[GAME_OVER]           = new GameOverScreen();

	clearInput();
	setScreen(BEGINNING_ANIMATION);
	return rendering::init();
}

void game::update()
{
	currentScreen->update();
}

void game::render()
{
	rendering::clearBuffer();
	rendering::renderWalls(Color::MAGENTA);

	currentScreen->render();
}
