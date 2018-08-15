#pragma once
#include "Screen.h"

namespace game
{
	void update(), render();
	extern unsigned long long int ticks;
	extern bool over;
	bool init();
	void setScreen(State state);
	extern Screen ** screens;	
}
