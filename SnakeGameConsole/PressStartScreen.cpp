#include "Screen.h"
#include "input.h"
#include "game.h"
#include "rendering.h"
#include "charmasks.h"
#include "utils.h"

void setMap(const Map & selectedMap);

using byte = unsigned char;

static const wchar_t * pressStartText = L"";
constexpr unsigned long long operator"" _ticks(unsigned long long n) { return n; }
static bool onSelectionStep = false;

static const byte yBase = 19, yStep = 1;
static byte yOffset = 0;

static const byte numberOfOptions = 8;
Map options[numberOfOptions] = { maps::level1 , maps::level2, maps::level3, maps::level4, maps::level5, maps::level6, maps::level7, maps::level8 };

void PressStartScreen::KeyEnter()
{
	if(!onSelectionStep) onSelectionStep = true;
	else
	{
		setMap(options[yOffset / yStep]);
		PlayingScreen::initialState();
		game::setScreen(PLAYING);
	}
}

void PressStartScreen::initialState()
{
	yOffset = 0;
}

void PressStartScreen::KeyUp()
{
	if (onSelectionStep) yOffset = utils::math::modulus(yOffset - yStep, yStep * numberOfOptions);
}

void PressStartScreen::KeyDown()
{
	if (onSelectionStep) yOffset = utils::math::modulus(yOffset + yStep, yStep * numberOfOptions);
}

void PressStartScreen::update()
{
	pressStartText = utils::switchValuesByTimeLapse(L"PRESS ENTER TO START", L"", 10_ticks);

	this->reactToKeys();
}

void renderOptions()
{
	float ySelector = float(yBase + yOffset);
	rendering::renderText(L"*", { 33, ySelector });

	unsigned i; float y;
	for (i = 0, y = yBase; i < numberOfOptions; ++i, y += yStep)
	{
		auto map = options[i];
		rendering::renderText(map.name, { 34, y }, ySelector == y ? map.color : Color::GRAY);
	}
}

void PressStartScreen::render()
{
	rendering::renderCharMap(charmasks::title, { 32, 10 }, rendering::FULL_BLOCK, Color::CYAN);
	rendering::renderCharMap(charmasks::underline, { 32, 17 }, rendering::FULL_BLOCK, Color::GREEN);

	if (!onSelectionStep) rendering::renderText(pressStartText, { 34, 19 });
	else renderOptions();

	rendering::renderText(L"Developed by FedeGaleano", { 65, 29 }, Color::GRAY | Color::BACK_MAGENTA);
}
