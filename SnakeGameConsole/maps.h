#pragma once
#include "Color.h"

struct Map
{
	char * data;
	unsigned int width, height;
	const wchar_t * name;
	Color color;
	unsigned int points;
	Map(char * data, unsigned int scanline, Color colors, const wchar_t * name, unsigned int points);
};

namespace maps
{
	extern Map level1, level2, level3, secret, level8, level4, level5, level6, level7;
}
