#include <iostream>
#include "rendering.h"

static CHAR_INFO buffer[rendering::width * rendering::height] = {};

static HANDLE handle;

static CONSOLE_CURSOR_INFO info = { 100, false };

static SMALL_RECT windowRectangle;

static void renderChar(wchar_t character, Vector2D coord, unsigned short int color)
{
	buffer[rendering::width * int(coord.y) + int(coord.x)] = { character, color };
};

int rendering::init()
{
	SetConsoleTitle("Snake Game");

	handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, NOT_SHARED, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	
	SetConsoleCursorInfo(handle, &info);

	windowRectangle = { 0, 0, rendering::width - 1, rendering::height - 1 };

	return SetConsoleActiveScreenBuffer(handle)
		&& SetConsoleWindowInfo(handle, true, &windowRectangle);
}

void rendering::renderBlock(Vector2D coord, unsigned short int color)
{
	renderChar(FULL_BLOCK, coord, color);
};

void rendering::renderText(const wchar_t * text, Vector2D coord, unsigned short int color)
{
	for (int i = 0; text[i]; ++i)
		renderChar(text[i], {coord.x + i, coord.y}, color);
}

void rendering::renderCharMap(CharMap map, Vector2D offset, unsigned short color)
{
	for (unsigned short y = 0; y < map.height; ++y)
		for (unsigned short x = 0; x < map.width; ++x)
			if (map.buffer[y * map.width + x] == 'X')
				rendering::renderBlock({ offset.x + x, offset.y + y }, color);
}

void rendering::renderWalls(unsigned short color)
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

CharMap::CharMap(const char * buffer, unsigned int scanline) : buffer(buffer), width(scanline), height(strlen(buffer) / scanline) {}
