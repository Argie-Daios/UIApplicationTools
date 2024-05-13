#pragma once

#include "Math/Structs.h"

class Item
{
public:
	Item() = default;
	Item(const glm::vec2& position) : m_Transform{ position, 0.0f, glm::vec2(1, 1) } {}
	virtual ~Item() = default;

	virtual void Draw() = 0;
protected:
	Transform m_Transform;
};

class Widget : public Item
{
public:
	Widget() = default;
	Widget(const glm::vec2& position) : Item(position) {}
	virtual ~Widget() = default;

	virtual void Update() = 0;
};