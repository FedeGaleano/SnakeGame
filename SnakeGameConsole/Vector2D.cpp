#include "Vector2D.h"

Vector2D Vector2D::operator+(Vector2D another) const
{
	return { this->x + another.x, this->y + another.y };
}

bool Vector2D::operator==(Vector2D another) const
{
	return this->x == another.x && this->y == another.y;
}

Vector2D::operator bool() const
{
	return this->x != 0 || this->y != 0;
}
