#include <chrono>
#include <queue>
#include "game.h"
#include "Error.h"
#include "rendering.h"
#include "engine.h"
#include "Screen.h"
#include "input.h"

static bool playing = true;

void engine::end()
{
	playing = false;
}

int main()
{
	using namespace std::chrono_literals;
	using std::chrono::system_clock;

	if (!game::init())
	{
		return Error("init");
	}

	/*
	 --------------------
	      Main Loop
	 --------------------
	*/
	auto lastTime = system_clock::now();
	auto millisPerFrame = 80ms;

	while (playing)
	{
		auto deltaTime = system_clock::now() - lastTime;
		unsigned long long int framesPassed = deltaTime / millisPerFrame;

		if (deltaTime > 40ms)
			inputChannel::processInput();

		if (framesPassed >= 1)
		{
			lastTime = system_clock::now();

			while (framesPassed >= 1)
			{
				game::update();
				framesPassed--;
				game::ticks++;
			}

			game::render();

			if (!rendering::show())
			{
				return Error("Show");
			}
		}
	}

	delete[] game::screens;

	return 0;
}