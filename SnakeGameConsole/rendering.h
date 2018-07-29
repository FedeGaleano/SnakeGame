#pragma once

#define NOT_SHARED 0
//#define UNICODE

#include <windows.h>
#include <string>
#include "Vector2D.h"

enum Color
{
	BLACK,
	RED     = FOREGROUND_RED,
	GREEN   = FOREGROUND_GREEN,
	BLUE    = FOREGROUND_BLUE,
	YELLOW  = RED  | GREEN,
	CYAN    = BLUE | GREEN,
	MAGENTA = RED  | BLUE,
	GRAY    = RED  | GREEN | BLUE
};

struct CharMap
{
	const char * buffer;
	unsigned int width, height;
	CharMap(const char * buffer, unsigned int scanline);
};

namespace rendering
{
	static wchar_t FULL_BLOCK = 219;
	static const short unsigned int width = 90 /*max = 120*/, height = 30 /*max = 30*/;

	void renderBlock(Vector2D coord, unsigned short int color = Color::GRAY);
	void renderWalls(unsigned short color);
	void renderCharMap(CharMap map, Vector2D initialCoords, unsigned short color = Color::GRAY);
	void renderText(const wchar_t * text, Vector2D coord, unsigned short int color = Color::GRAY);
	bool show();
	void clearBuffer();
	int init();
}
