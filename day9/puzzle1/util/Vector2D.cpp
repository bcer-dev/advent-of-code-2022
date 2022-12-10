#include "Vector2D.hpp"
#include <cmath>

Vector2D::Vector2D(int x, int y) : x{x}, y{y} {}

void Vector2D::move(char direction)
{
    switch (direction)
	{
	case 'U':
		y--;
		break;

	case 'D':
		y++;
		break;

	case 'L':
		x--;
		break;

	case 'R':
		x++;
		break;
	}
}

bool Vector2D::isTouching(const Vector2D& other) const
{
	if (std::abs(x - other.x) > 1)
		return false;

	if (std::abs(y - other.y) > 1)
		return false;

	return true;
}

bool Vector2D::isDiagonalTo(const Vector2D& other) const
{
	if (x == other.x + 1 && y == other.y + 1)
		return true;

	if (x == other.x - 1 && y == other.y + 1)
		return true;

	if (x == other.x + 1 && y == other.y - 1)
		return true;

	if (x == other.x - 1 && y == other.y - 1)
		return true;

	return false;
}