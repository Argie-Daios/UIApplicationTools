#include "UIItem.h"

#include "Core/Macros.h"

#include <algorithm>

UIItem::UIItem()
	: m_Transform{ Vector2f(0, 0), 0.0f, Vector2f(1, 1) }, m_Size(-1, -1), m_Parent(nullptr)
{

}

UIItem::UIItem(const Vector2f& position, const Vector2f& size)
	: m_Transform{ position, 0.0f, Vector2f(1, 1) }, m_Size(size), m_Parent(nullptr)
{

}

void UIItem::Attach(UIItem* parent)
{
	UIASSERT(parent, "Null parent!!");
	parent->AddChild(this);
}

void UIItem::AddChild(UIItem* child)
{
	UIASSERT(child, "Null child!!");
	if (child->IsChildOf(this))
	{
		UIERROR("The given child is already a child of this item!!");
		return;
	}
	if (child->IsAncestorOf(this))
	{
		UIERROR("The given child is an ancestor of this item!!");
		return;
	}

	if (child->m_Parent)
	{
		m_Parent->m_Children.erase(std::find(m_Parent->m_Children.begin(), m_Parent->m_Children.end(), child));
	}

	child->m_Parent = this;
	this->m_Children.push_back(child);
}

bool UIItem::IsChildOf(UIItem* subject)
{
	UIASSERT(subject, "Null subject!!");
	return std::find(subject->m_Children.begin(), subject->m_Children.end(), this) != subject->m_Children.end();
}

bool UIItem::IsAncestorOf(UIItem* subject)
{
	UIASSERT(subject, "Null subject!!");
	
	UIItem* current = subject->m_Parent;
	while (current)
	{
		if (current == this) return true;
		current = current->m_Parent;
	}

	return false;
}

bool UIItem::IsSuccessorOfRecursive(UIItem* current, UIItem* subject)
{
	if (current == subject) return true;

	auto& children = current->m_Children;
	while (!children.empty())
	{
		for (int i = 0; i < children.size(); i++)
		{
			bool result = IsSuccessorOfRecursive(children.at(i), subject);
			if (result) return true;
			if (i == children.size() - 1) return false;
		}
	}

	return false;
}

bool UIItem::IsSuccessorOf(UIItem* subject)
{
	UIASSERT(subject, "Null subject!!");

	return IsSuccessorOfRecursive(subject, this);
}
