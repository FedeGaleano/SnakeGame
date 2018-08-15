#pragma once

#define NOT_SHARED 0
//#define UNICODE

#include <windows.h>
#include <string>
#include "Vector2D.h"
#include "maps.h"
#include "Color.h"

struct CharMask
{
	const char * buffer;
	unsigned int width, height;
	CharMask(const char * buffer, unsigned int scanline);
};

namespace rendering
{
	extern wchar_t FULL_BLOCK, SOFT_BLOCK, TRANSLUCENT_BLOCK, UPPER_SQUARE, LOWER_SQUARE;
	extern const short unsigned int width, height;

	void renderBlock(Vector2D coord, unsigned short int color = Color::GRAY);
	void renderSoftBlock(Vector2D coord, unsigned short int color);
	void renderSurroundingFrame(unsigned short color);
	void renderCharMap(CharMask map, Vector2D offset, wchar_t ascii, unsigned short color);
	void renderText(const wchar_t * text, Vector2D coord, unsigned short int color = Color::GRAY);
	void renderChar(wchar_t character, Vector2D coord, unsigned short int color = Color::GRAY);
	bool show();
	void clearBuffer();
	int init();
	void renderMap(const Map & map);
}
