#pragma once

#include <glm/glm.hpp>

struct Transform
{
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;
};

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};