#include "UIItem.h"

#include "Core/Macros.h"
#include "Math/Functions.h"
#include "Tools/AssetManager.h"

#include <algorithm>

UIItem::UIItem()
	: m_Transform{ Vector2f(0, 0), 0.0f, Vector2f(1, 1) }, m_DepthValue(0.0f), m_Size(-1, -1), m_Parent(nullptr),
	m_Active(true)
{

}

UIItem::UIItem(const Vector2f& position, const Vector2f& size, const UIMesh& mesh)
	: m_Transform{ position, 0.0f, Vector2f(1, 1) }, m_DepthValue(0.0f), m_Size(size), m_Parent(nullptr),
	m_Active(true), m_Mesh(mesh)
{

}

void UIItem::Attach(UIItem* parent)
{
	UIASSERT(parent, "Null parent!!");
	parent->AddChild(this);
}

void UIItem::DettachChildren()
{
	for (auto& child : m_Children)
	{
		child->m_Parent = nullptr;
	}
	m_Children.clear();
}

void UIItem::Dettach()
{
	if (m_Parent)
	{
		m_Parent->m_Children.erase(std::find(m_Parent->m_Children.begin(), m_Parent->m_Children.end(), this));
	}
}

void UIItem::ForEachOnFamilyTree(const std::function<void(UIItem* item)>& function)
{
	for (auto& child : m_Children)
	{
		function(child);
		child->ForEachOnFamilyTree(function);
	}
}

void UIItem::Translate(const Vector2f& deltaVector)
{
	m_Transform.position += deltaVector;

	for (auto& element : m_Children)
	{
		element->Translate(deltaVector);
	}
}

void UIItem::SetPosition(const Vector2f& positionVector)
{
	Vector2f prevPosition = m_Transform.position;
	m_Transform.position = positionVector;

	for (auto& element : m_Children)
	{
		Vector2f childNewPos = element->m_Transform.position - prevPosition;
		element->SetPosition(positionVector + childNewPos);
	}
}

void UIItem::Rotate(UIFloat degrees)
{
	m_Transform.rotation.Rotate(degrees);

	for (auto& element : m_Children)
	{
		element->Rotate(degrees);
	}
}

void UIItem::SetActive(bool active)
{
	m_Active = active;

	for (auto& element : m_Children)
	{
		element->SetActive(active);
	}
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
		child->m_Parent->m_Children.erase(
			std::find(child->m_Parent->m_Children.begin(),
				child->m_Parent->m_Children.end(), child));
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
	for (int i = 0; i < children.size(); i++)
	{
		bool result = IsSuccessorOfRecursive(children.at(i), subject);
		if (result) return true;
		if (i == children.size() - 1) return false;
	}

	return false;
}

void UIItem::AddMesh(const UIMesh& mesh)
{
	m_Mesh = mesh;
}

bool UIItem::IsSuccessorOf(UIItem* subject)
{
	UIASSERT(subject, "Null subject!!");

	return IsSuccessorOfRecursive(subject, this);
}
