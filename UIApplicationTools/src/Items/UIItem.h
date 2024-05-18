#pragma once

#include "Math/Structs.h"

class UIItem
{
public:
	UIItem();
	UIItem(const Vector2f& position, const Vector2f& size = Vector2f(-1, -1));
	virtual ~UIItem() = default;

	virtual void Draw() = 0;

	void Attach(UIItem* parent);
	// void Translate(const Vector2f& deltaVector);
	// void SetPosition(const Vector2f& positionVector);
private:
	void AddChild(UIItem* child);

	bool IsChildOf(UIItem* subject);
	bool IsAncestorOf(UIItem* subject);
	bool IsSuccessorOfRecursive(UIItem* current, UIItem* subject);
	bool IsSuccessorOf(UIItem* subject);
protected:
	Transform m_Transform;
	Vector2f m_Size; // Need to be (-1, -1) if the size is coming from other source

	UIItem* m_Parent;
	UIVector<UIItem*> m_Children;
};

class Widget : public UIItem
{
public:
	Widget() = default;
	Widget(const Vector2f& position, const Vector2f& size = Vector2f(-1, -1)) : UIItem(position, size) {}
	virtual ~Widget() = default;

	virtual void Update() = 0;
};