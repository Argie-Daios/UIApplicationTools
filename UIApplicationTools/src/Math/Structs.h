#pragma once

#include "Core/UIDefinitions.h"
#include <glm/glm.hpp>

struct SDL_Color;

struct Vector2f
{
public:
	Vector2f() = default;
	Vector2f(UIFloat value) : vector(value) {}
	Vector2f(UIFloat x, UIFloat y) : vector(x, y) {}
	Vector2f(const Vector2f& vector) : vector(vector.vector) {}

	// float Magnitude() const;
	// float Direction() const;
	// Vector2f Normalize() const;

	bool operator==(const Vector2f& vector) const { return this->vector == vector.vector; }
	bool operator!=(const Vector2f& vector) const { return this->vector != vector.vector; }

	UIFloat X() const { return vector.x; }
	UIFloat Y() const { return vector.y; }
private:
	glm::vec2 vector;
};

struct Vector2i
{
public:
	Vector2i() = default;
	Vector2i(UIInt value) : vector(value) {}
	Vector2i(UIInt x, UIInt y) : vector(x, y) {}
	Vector2i(const Vector2i& vector) : vector(vector.vector) {}

	bool operator==(const Vector2i& vector) { return this->vector == vector.vector; }
	bool operator!=(const Vector2i& vector) const { return this->vector != vector.vector; }

	UIInt X() const { return vector.x; }
	UIInt Y() const { return vector.y; }
private:
	glm::ivec2 vector;
};

struct Transform
{
	Vector2f position;
	UIFloat rotation;
	Vector2f scale;

	Transform() = default;
	Transform(const Vector2f& position, UIFloat rotation = 0.0f, const Vector2f& scale = Vector2f(1.0f, 1.0f)) : 
		position(position), rotation(rotation), scale(scale) {}
	Transform(const Transform& transform) : position(transform.position), rotation(transform.rotation),
		scale(transform.scale) {}
};

struct ColorRGB
{
	UIUnsignedByte r;
	UIUnsignedByte g;
	UIUnsignedByte b;

	ColorRGB() = default;
	ColorRGB(UIUnsignedByte r, UIUnsignedByte g, UIUnsignedByte b) : r(r), g(g), b(b) {}
	ColorRGB(const ColorRGB& colorRGB) : r(colorRGB.r), g(colorRGB.g), b(colorRGB.b) {}

	operator SDL_Color();
};

struct ColorRGBA
{
	UIUnsignedByte r;
	UIUnsignedByte g;
	UIUnsignedByte b;
	UIUnsignedByte a;

	ColorRGBA() = default;
	ColorRGBA(UIUnsignedByte r, UIUnsignedByte g, UIUnsignedByte b, UIUnsignedByte a) : r(r), g(g), b(b), a(a)
	{}
	ColorRGBA(const ColorRGBA& colorRGBA) : r(colorRGBA.r), g(colorRGBA.g), b(colorRGBA.b), a(colorRGBA.a) {}

	operator SDL_Color();
};