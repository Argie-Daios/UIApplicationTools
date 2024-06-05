#include "Structs.h"

#include "Core/Macros.h"

#include <SDL.h>

const Vector2f Vector2f::operator+(const Vector2f& vector) const
{
	glm::vec2 vec2 = this->vector + vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

const Vector2f Vector2f::operator-(const Vector2f& vector) const
{
	glm::vec2 vec2 = this->vector - vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

const Vector2f Vector2f::operator*(const Vector2f& vector) const
{
	glm::vec2 vec2 = this->vector * vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

const Vector2f Vector2f::operator/(const Vector2f& vector) const
{
	UIASSERT(vector.X() != 0 && vector.Y() != 0, "Division with 0!!");
	glm::vec2 vec2 = this->vector / vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

Vector2f Vector2f::operator+(const Vector2f& vector)
{
	glm::vec2 vec2 = this->vector + vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

Vector2f Vector2f::operator-(const Vector2f& vector)
{
	glm::vec2 vec2 = this->vector - vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

Vector2f Vector2f::operator*(const Vector2f& vector)
{
	glm::vec2 vec2 = this->vector * vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

Vector2f Vector2f::operator/(const Vector2f& vector)
{
	UIASSERT(vector.X() != 0 && vector.Y() != 0, "Division with 0!!");
	glm::vec2 vec2 = this->vector / vector.vector;
	return Vector2f(vec2.x, vec2.y);
}

Vector2f& Vector2f::operator+=(const Vector2f& vector)
{
	this->vector += vector.vector;
	return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& vector)
{
	this->vector -= vector.vector;
	return *this;
}

Vector2f& Vector2f::operator*=(const Vector2f& vector)
{
	this->vector *= vector.vector;
	return *this;
}

Vector2f& Vector2f::operator/=(const Vector2f& vector)
{
	UIASSERT(vector.X() != 0 && vector.Y() != 0, "Division with 0!!");
	this->vector /= vector.vector;
	return *this;
}

Vector2f& Vector2f::operator=(const Vector2f& vector)
{
	if (this->vector == vector.vector) return *this;

	this->vector = vector.vector;
	return *this;
}

const Vector2i Vector2i::operator+(const Vector2i& vector) const
{
	glm::ivec2 vec2 = this->vector + vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

const Vector2i Vector2i::operator-(const Vector2i& vector) const
{
	glm::ivec2 vec2 = this->vector - vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

const Vector2i Vector2i::operator*(const Vector2i& vector) const
{
	glm::ivec2 vec2 = this->vector * vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

const Vector2i Vector2i::operator/(const Vector2i& vector) const
{
	UIASSERT(vector.X() != 0 && vector.Y() != 0, "Division with 0!!");
	glm::ivec2 vec2 = this->vector / vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

Vector2i Vector2i::operator+(const Vector2i& vector)
{
	glm::ivec2 vec2 = this->vector + vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

Vector2i Vector2i::operator-(const Vector2i& vector)
{
	glm::ivec2 vec2 = this->vector - vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

Vector2i Vector2i::operator*(const Vector2i& vector)
{
	glm::ivec2 vec2 = this->vector * vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

Vector2i Vector2i::operator/(const Vector2i& vector)
{
	UIASSERT(vector.X() != 0 && vector.Y() != 0, "Division with 0!!");
	glm::ivec2 vec2 = this->vector / vector.vector;
	return Vector2i(vec2.x, vec2.y);
}

Vector2i& Vector2i::operator+=(const Vector2i& vector)
{
	this->vector += vector.vector;
	return *this;
}

Vector2i& Vector2i::operator-=(const Vector2i& vector)
{
	this->vector -= vector.vector;
	return *this;
}

Vector2i& Vector2i::operator*=(const Vector2i& vector)
{
	this->vector *= vector.vector;
	return *this;
}

Vector2i& Vector2i::operator/=(const Vector2i& vector)
{
	UIASSERT(vector.X() != 0 && vector.Y() != 0, "Division with 0!!");
	this->vector /= vector.vector;
	return *this;
}

Vector2i& Vector2i::operator=(const Vector2i& vector)
{
	if (this->vector == vector.vector) return *this;

	this->vector = vector.vector;
	return *this;
}

Rectanglef::operator SDL_Rect()
{
	SDL_Rect rectangle;
	rectangle.x = (UIInt)x;
	rectangle.y = (UIInt)y;
	rectangle.w = (UIInt)w;
	rectangle.h = (UIInt)h;

	return rectangle;
}

Rectanglei::operator SDL_Rect()
{
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;

	return rectangle;
}

ColorRGB::operator SDL_Color()
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;

	return color;
}

ColorRGBA::operator SDL_Color()
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	return color;
}