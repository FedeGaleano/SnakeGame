#include <iostream>
#include "rendering.h"

namespace rendering
{
	wchar_t FULL_BLOCK = 219, SOFT_BLOCK = 177, TRANSLUCENT_BLOCK = 176, UPPER_SQUARE = 220, LOWER_SQUARE = 223;
	const short unsigned int width = 90 /*max = 120*/, height = 30 /*max = 30*/;
}

static CHAR_INFO buffer[rendering::width * rendering::height] = {};

static HANDLE handle;

static CONSOLE_CURSOR_INFO info = { 100, false };

static SMALL_RECT windowRectangle;

int rendering::init()
{
	SetConsoleTitle("Snake Game");

	handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, NOT_SHARED, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	
	SetConsoleCursorInfo(handle, &info);

	windowRectangle = { 0, 0, rendering::width - 1, rendering::height - 1};

	return SetConsoleActiveScreenBuffer(handle)
		&& SetConsoleWindowInfo(handle, true, &windowRectangle);
}

void rendering::renderChar(wchar_t character, Vector2D coord, unsigned short int color)
{
	if (coord.x >= 0 && coord.x < rendering::width && coord.y >= 0 && coord.y < rendering::height)
		buffer[rendering::width * int(coord.y) + int(coord.x)] = { character, color };
};

void rendering::renderBlock(Vector2D coord, unsigned short int color)
{
	rendering::renderChar(FULL_BLOCK, coord, color);
};

void rendering::renderSoftBlock(Vector2D coord, unsigned short int color)
{
	rendering::renderChar(SOFT_BLOCK, coord, color);
};

void rendering::renderText(const wchar_t * text, Vector2D coord, unsigned short int color)
{
	for (int i = 0; text[i]; ++i)
		rendering::renderChar(text[i], {coord.x + i, coord.y}, color);
}

void rendering::renderCharMap(CharMask map, Vector2D offset, wchar_t ascii, unsigned short color)
{
	for (unsigned short y = 0; y < map.height; ++y)
		for (unsigned short x = 0; x < map.width; ++x)
			if (map.buffer[y * map.width + x] == 'X')
				rendering::renderChar(ascii, { offset.x + x, offset.y + y }, color);
}

void rendering::renderMap(const Map & map)
{
	for (unsigned short y = 0; y < map.height; ++y)
		for (unsigned short x = 0; x < map.width; ++x)
			if (map.data[y * map.width + x] == '#')
			{
				renderChar(FULL_BLOCK, { float(x * 2), float(y) }, map.color);
				renderChar(FULL_BLOCK, { float(x * 2 + 1), float(y) }, map.color);
			}
}

void rendering::renderSurroundingFrame(unsigned short color)
{
	const int bottom = width * (height - 1);

	for (int i = 0; i < width; ++i)
		buffer[i] = buffer[bottom + i] = { FULL_BLOCK, color };

	for (int i = 1; i < height; ++i)
		buffer[i * width] = buffer[i * width - 1] = { FULL_BLOCK, color };
}

bool rendering::show()
{
	return WriteConsoleOutput(handle, buffer, { width, height }, { 0, 0 }, &windowRectangle);
}

void rendering::clearBuffer()
{
	std::memset(buffer, 0, sizeof buffer);
}

CharMask::CharMask(const char * buffer, unsigned int scanline) : buffer(buffer), width(scanline), height(strlen(buffer) / scanline) {}
