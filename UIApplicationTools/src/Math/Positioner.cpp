#include "Positioner.h"

#include "Items/UIItem.h"
#include "Core/Macros.h"
#include "Core/Application.h"

namespace UIMath
{
	void Positioner::PositionItemToWindow(UIItem* item, const PositioningAreas& positioning,
		const Vector2f& offset)
	{
		UIASSERT(item, "Null item!!");
		if (Application::Get() == nullptr)
		{
			UIERROR("Application error!!");
			return;
		}

		Vector2f windowPosition = Vector2f(0, 0);
		Vector2f windowSize = Vector2f((UIFloat)Application::GetWindow()->GetWidth(),
			(UIFloat)Application::GetWindow()->GetHeight());
		Vector2f itemPosition = item->GetTransform().position;
		Vector2f itemSize = item->GetSize();

		Vector2f newPosition = PerformPositioning(positioning, windowPosition, windowSize,
			itemPosition, itemSize);
		item->SetPosition(newPosition + offset);
	}

	void Positioner::PositionItemToParent(UIItem* item, const PositioningAreas& positioning,
		const Vector2f& offset)
	{
		UIASSERT(item, "Null item!!");
		PositionItemToItem(item, item->GetParent(), positioning, offset);
	}

	void Positioner::PositionItemToItem(UIItem* itemDst, UIItem* itemSrc, const PositioningAreas& positioning, const Vector2f& offset)
	{
		UIASSERT(itemSrc, "Null item!!");
		UIASSERT(itemDst, "Null item!!");

		Vector2f srcItemPosition = itemSrc->GetTransform().position;
		Vector2f srcItemSize = itemSrc->GetSize();
		Vector2f dstItemPosition = itemDst->GetTransform().position;
		Vector2f dstItemSize = itemDst->GetSize();

		Vector2f newPosition = PerformPositioning(positioning, srcItemPosition, srcItemSize,
			dstItemPosition, dstItemSize);
		itemDst->SetPosition(newPosition + offset);
	}

	Vector2f Positioner::PerformPositioning(const PositioningAreas& positioning,
		const Vector2f& areaXY, const Vector2f& areaWH,
		const Vector2f& itemXY, const Vector2f& itemWH)
	{
		Vector2f newPosition = itemXY;
		switch (positioning)
		{
		case PositioningAreas::UP_LEFT:
		{
			newPosition = areaXY;
			break;
		}
		case PositioningAreas::UP:
		{
			newPosition = Vector2f((2.0f * areaXY.X() + areaWH.X() - itemWH.X()) / 2.0f,
				areaXY.Y());
			break;
		}
		case PositioningAreas::UP_RIGHT:
		{
			newPosition = Vector2f(areaXY.X() + areaWH.X() - itemWH.X(), areaXY.Y());
			break;
		}
		case PositioningAreas::LEFT:
		{
			newPosition = Vector2f(areaXY.X(),
				(2.0f * areaXY.Y() + areaWH.Y() - itemWH.Y()) / 2.0f);
			break;
		}
		case PositioningAreas::CENTER:
		{
			newPosition = Vector2f((2.0f * areaXY.X() + areaWH.X() - itemWH.X()) / 2.0f,
				(2.0f * areaXY.Y() + areaWH.Y() - itemWH.Y()) / 2.0f);
			break;
		}
		case PositioningAreas::RIGHT:
		{
			newPosition = Vector2f(areaXY.X() + areaWH.X() - itemWH.X(),
				(2.0f * areaXY.Y() + areaWH.Y() - itemWH.Y()) / 2.0f);
			break;
		}
		case PositioningAreas::DOWN_LEFT:
		{
			newPosition = Vector2f(areaXY.X(),
				areaXY.Y() + areaWH.Y() - itemWH.Y());
			break;
		}
		case PositioningAreas::DOWN:
		{
			newPosition = Vector2f((2.0f * areaXY.X() + areaWH.X() - itemWH.X()) / 2.0f,
				areaXY.Y() + areaWH.Y() - itemWH.Y());
			break;
		}
		case PositioningAreas::DOWN_RIGHT:
		{
			newPosition = Vector2f(areaXY.X() + areaWH.X() - itemWH.X(),
				areaXY.Y() + areaWH.Y() - itemWH.Y());
			break;
		}
		}

		return newPosition;
	}
}