#pragma once

#include "Core/UIDefinitions.h"
#include <glm/glm.hpp>

struct SDL_Color;
struct SDL_Rect;

struct Vector2f
{
public:
	Vector2f() = default;
	Vector2f(UIFloat value) : vector(value) {}
	Vector2f(UIFloat x, UIFloat y) : vector(x, y) {}
	Vector2f(const Vector2f& vector) : vector(vector.vector) {}

	const Vector2f operator+(const Vector2f& vector) const;
	const Vector2f operator-(const Vector2f& vector) const;
	const Vector2f operator*(const Vector2f& vector) const;
	const Vector2f operator/(const Vector2f& vector) const;

	Vector2f operator+(const Vector2f& vector);
	Vector2f operator-(const Vector2f& vector);
	Vector2f operator*(const Vector2f& vector);
	Vector2f operator/(const Vector2f& vector);

	Vector2f& operator+=(const Vector2f& vector);
	Vector2f& operator-=(const Vector2f& vector);
	Vector2f& operator*=(const Vector2f& vector);
	Vector2f& operator/=(const Vector2f& vector);

	Vector2f& operator=(const Vector2f& vector);

	bool operator==(const Vector2f& vector) const { return this->vector == vector.vector; }
	bool operator!=(const Vector2f& vector) const { return this->vector != vector.vector; }

	inline void SetX(UIFloat x) { vector.x = x; }
	inline void SetY(UIFloat y) { vector.y = y; }
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

	const Vector2i operator+(const Vector2i& vector) const;
	const Vector2i operator-(const Vector2i& vector) const;
	const Vector2i operator*(const Vector2i& vector) const;
	const Vector2i operator/(const Vector2i& vector) const;

	Vector2i operator+(const Vector2i& vector);
	Vector2i operator-(const Vector2i& vector);
	Vector2i operator*(const Vector2i& vector);
	Vector2i operator/(const Vector2i& vector);

	Vector2i& operator+=(const Vector2i& vector);
	Vector2i& operator-=(const Vector2i& vector);
	Vector2i& operator*=(const Vector2i& vector);
	Vector2i& operator/=(const Vector2i& vector);

	Vector2i& operator=(const Vector2i& vector);

	inline bool operator==(const Vector2i& vector) { return this->vector == vector.vector; }
	inline bool operator!=(const Vector2i& vector) const { return this->vector != vector.vector; }

	inline void SetX(UIInt x) { vector.x = x; }
	inline void SetY(UIInt y) { vector.y = y; }
	UIInt X() const { return vector.x; }
	UIInt Y() const { return vector.y; }
private:
	glm::ivec2 vector;
};

struct Rectanglef
{
public:
	Rectanglef() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}
	Rectanglef(UIFloat x, UIFloat y, UIFloat w, UIFloat h) : x(x), y(y), w(w), h(h) {}
	Rectanglef(const Rectanglef& rect) : x(rect.x), y(rect.y), w(rect.w), h(rect.h) {}

	operator SDL_Rect();

	UIFloat x;
	UIFloat y;
	UIFloat w;
	UIFloat h;
};

struct Rectanglei
{
public:
	Rectanglei() : x(0), y(0), w(0), h(0) {}
	Rectanglei(UIInt x, UIInt y, UIInt w, UIInt h) : x(x), y(y), w(w), h(h) {}
	Rectanglei(const Rectanglei& rect) : x(rect.x), y(rect.y), w(rect.w), h(rect.h) {}

	operator SDL_Rect();

	UIInt x;
	UIInt y;
	UIInt w;
	UIInt h;
};

struct Rotator
{
	UIFloat Degrees;

	Rotator() = default;
	Rotator(UIFloat degrees) : Degrees(degrees) {}

	void Rotate(UIFloat degrees)
	{
		if (degrees == 0) return;
		UIFloat newDegrees = Degrees + degrees;
		if (newDegrees >= 360.0f)
		{
			Degrees = newDegrees - 360.0f;
			return;
		}
		Degrees = newDegrees;
	}
};

struct Transform
{
	Vector2f position;
	Rotator rotation;
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

	ColorRGB(UIUnsignedByte r = 255, UIUnsignedByte g = 255, UIUnsignedByte b = 255) : r(r), g(g), b(b) {}
	ColorRGB(const ColorRGB& colorRGB) : r(colorRGB.r), g(colorRGB.g), b(colorRGB.b) {}

	operator SDL_Color();
};

struct ColorRGBA
{
	UIUnsignedByte r;
	UIUnsignedByte g;
	UIUnsignedByte b;
	UIUnsignedByte a;

	ColorRGBA(UIUnsignedByte r = 255, UIUnsignedByte g = 255, UIUnsignedByte b = 255,
		UIUnsignedByte a = 255) : r(r), g(g), b(b), a(a)
	{}
	ColorRGBA(const ColorRGBA& colorRGBA) : r(colorRGBA.r), g(colorRGBA.g), b(colorRGBA.b), a(colorRGBA.a) {}

	operator SDL_Color();
};