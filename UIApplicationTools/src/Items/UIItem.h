#pragma once

#include "Math/Structs.h"

class UIItem
{
public:
	UIItem();
	UIItem(const Vector2f& position, const Vector2f& size = Vector2f(-1, -1));
	UIItem(const UIItem& item) = default;
	virtual ~UIItem() = default;

	virtual void Draw() = 0;

	void Attach(UIItem* parent);
	void Translate(const Vector2f& deltaVector);
	void SetPosition(const Vector2f& positionVector);
	void Rotate(UIFloat degrees);

	void SetActive(bool active);
	inline UIBool GetActive() const { return m_Active; }

	inline void SetSize(const Vector2f& size) { m_Size = size; }

	inline Transform GetTransform() const { return m_Transform; }
	inline Vector2f GetSize() const { return m_Size; }
	inline UIItem* GetParent() { return m_Parent; }
	inline UIVector<UIItem*>& GetChildren() { return m_Children; }
	
	bool IsChildOf(UIItem* subject);
	bool IsAncestorOf(UIItem* subject);
	bool IsSuccessorOf(UIItem* subject);
private:
	void AddChild(UIItem* child);
	bool IsSuccessorOfRecursive(UIItem* current, UIItem* subject);
protected:
	Transform m_Transform;
	Vector2f m_Size;
	UIBool m_Active;

	UIItem* m_Parent;
	UIVector<UIItem*> m_Children;
};

class UIWidget : public UIItem
{
public:
	UIWidget() = default;
	UIWidget(const Vector2f& position, const Vector2f& size = Vector2f(-1, -1)) : UIItem(position, size) {}
	virtual ~UIWidget() = default;

	virtual void Update() = 0;
};