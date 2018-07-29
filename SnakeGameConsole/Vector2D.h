#pragma once

struct Vector2D
{
	float x, y;
	Vector2D operator+(Vector2D another) const;
	bool operator==(Vector2D another) const;
};
