#pragma once

#include <deque>
#include "Vector2D.h"
#include "rendering.h"

extern unsigned short width, height, maxWidth, maxHeight;
extern std::deque<Vector2D> snakeParts;
extern Vector2D velocity;
extern unsigned int score, highestScore;
extern Color snakeColor, snakeSecondColor;
extern wchar_t block;
extern bool took;
extern bool shouldGrow;

void moveSnake(Vector2D delta_xy);
void renderSnake();
void renderScore(float x, float y);
void powerUp();
