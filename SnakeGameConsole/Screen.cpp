#include "Screen.h"
#include "input.h"
#include "engine.h"

void Screen::KeyUp() {}
void Screen::KeyLeft() {}
void Screen::KeyDown() {}
void Screen::KeyRight() {}
void Screen::KeyEnter() {}
void Screen::KeyEscape()
{
	engine::end();
}

void Screen::reactToKeys()
{
	if (inputChannel::hasMessages())
		switch (inputChannel::popMessage())
		{
		case Key::up:
			this->KeyUp();
			break;
		case Key::left:
			this->KeyLeft();
			break;
		case Key::down:
			this->KeyDown();
			break;
		case Key::right:
			this->KeyRight();
			break;
		case Key::enter:
			this->KeyEnter();
			break;
		case Key::escape:
			this->KeyEscape();
			break;
		default:
			break;
		}
}
