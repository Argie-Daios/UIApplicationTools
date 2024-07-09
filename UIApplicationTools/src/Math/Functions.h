#pragma once

#include "Structs.h"

namespace UIMath
{
	inline Vector2f Rotate(const Vector2f& size, float degrees)
	{
		float theta = degrees;
		if (degrees > 90)
		{
			theta -= 90;
		}

		Vector2f newSize = Vector2f(
			abs(size.X() * glm::cos(glm::radians(theta)) + size.Y() * glm::sin(glm::radians(theta))),
			abs(size.X() * glm::sin(glm::radians(theta)) + size.Y() * glm::cos(glm::radians(theta))));

		return newSize;
	}
}