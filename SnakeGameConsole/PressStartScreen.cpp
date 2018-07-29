#include "Screen.h"
#include "input.h"
#include "game.h"
#include "rendering.h"
#include "charmaps.h"
#include "utils.h"

static const wchar_t * pressStartText = L"";
constexpr unsigned long long operator"" _ticks(unsigned long long n) { return n; }

void PressStartScreen::KeyEnter()
{
	game::setScreen(PLAYING);
}

void PressStartScreen::update()
{
	pressStartText = switchValuesByTimeLapse(L"PRESS ENTER TO START", L"", 10_ticks);

	this->reactToKeys();
}

void PressStartScreen::render()
{
	rendering::renderCharMap(charmaps::title, { 32, 10 }, Color::CYAN);
	rendering::renderCharMap(charmaps::underline, { 32, 17 }, Color::GREEN);
	rendering::renderText(pressStartText, { 34, 19 });
	rendering::renderText(L"Developed by FedeGaleano", { 65, 29 }, Color::GRAY | Color::BACK_MAGENTA);
}
