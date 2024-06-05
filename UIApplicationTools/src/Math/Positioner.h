#pragma once

#include "Structs.h"

class UIItem;

namespace UIMath
{
	enum class PositioningAreas
	{
		UP_LEFT,
		UP,
		UP_RIGHT,
		LEFT,
		CENTER,
		RIGHT,
		DOWN_LEFT,
		DOWN,
		DOWN_RIGHT
	};

	class Positioner
	{
	public:
		static void PositionItemToWindow(UIItem* item, const PositioningAreas& positioning,
			const Vector2f& offset = Vector2f(0, 0));
		static void PositionItemToParent(UIItem* item, const PositioningAreas& positioning,
			const Vector2f& offset = Vector2f(0, 0));
		static void PositionItemToItem(UIItem* itemDst, UIItem* itemSrc, const PositioningAreas& positioning,
			const Vector2f& offset = Vector2f(0, 0));
	private:
		static Vector2f PerformPositioning(const PositioningAreas& positioning,
			const Vector2f& areaXY, const Vector2f& areaWH,
			const Vector2f& itemXY, const Vector2f& itemWH);
	};
}