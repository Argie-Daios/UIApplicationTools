#include "Scene.h"

static const char* invalidName = "--INVALID--";

Scene::Scene()
{
	
}

Scene::Scene(const UIString& name)
	: m_Name(name)
{
	
}

void Scene::RemoveItem(UIItem* item)
{
	UIString name = GetItemName(item);
	UIASSERT(name != invalidName, "Non-existant name!!");

	for (auto& child : item->GetChildren())
	{
		RemoveItem(child);
	}
	item->Dettach();
	m_DeletionQueue.push_back(name);
}

void Scene::RemoveItem(const UIString& name)
{
	UIASSERT(IsNameDupliacte(name), "Non-existant name!!");
	
	auto& item = m_Items.at(name);
	RemoveItem(item.get());
}

UIItem* Scene::ReceiveItem(const UIString& name)
{
	UIASSERT(IsNameDupliacte(name), "Non-existant name!!");
	return m_Items.at(name).get();
}

void Scene::ForEach(const std::function<void(UIItem* item)>& function)
{
	for (auto& [key, value] : m_Items)
	{
		function(value.get());
	}
	if (!m_DeletionQueue.empty())
	{
		for (auto& name : m_DeletionQueue)
		{
			m_Items.erase(name);
			m_PriorityList.erase(std::find(m_PriorityList.begin(), m_PriorityList.end(), name));
		}
		m_DeletionQueue.clear();
	}
}

void Scene::ForEachInPriority(const std::function<void(UIItem* item)>& function)
{
	for (auto& element : m_PriorityList)
	{
		UIItem* itemPtr = m_Items.at(element).get();
		function(itemPtr);
	}
	if (!m_DeletionQueue.empty())
	{
		for (auto& name : m_DeletionQueue)
		{
			m_Items.erase(name);
			m_PriorityList.erase(std::find(m_PriorityList.begin(), m_PriorityList.end(), name));
		}
		m_DeletionQueue.clear();
	}
}

void Scene::ResortItem(UIItem* item)
{
	auto& it = m_PriorityList.begin();
	UIFloat itemDepthValue = item->GetDepthValue();
	UIString name = GetItemName(item);
	UIASSERT(name != invalidName, "Invalid name!!");
	auto& itemIterator = std::find(m_PriorityList.begin(), m_PriorityList.end(), name);
	for (it; it != m_PriorityList.end(); it++)
	{
		if (itemIterator == it) continue;
		UIFloat elementDepthValue = m_Items.at(*it)->GetDepthValue();
		if (itemDepthValue <= elementDepthValue)
			break;
	}
	
	std::string elementName = *it;
	m_PriorityList.erase(itemIterator);
	m_PriorityList.insert(std::find(m_PriorityList.begin(), m_PriorityList.end(), elementName), name);
}

void Scene::PrintHierarchyOnConsole()
{
	std::cout << "Scene: " << m_Name << std::endl;
	std::cout << "============================================================" << std::endl;
	for (auto& [key, value] : m_Items)
	{
		if (value->GetParent() == nullptr)
		{
			PrintItemFamilyTree(value.get());
		}
	}
	std::cout << "============================================================" << std::endl;
	std::cout << std::endl;
}

void Scene::PrintHierarchyOnFile(const UIString& filepath)
{
	std::ofstream stream(filepath.c_str());
	stream << "Scene: " << m_Name << std::endl;
	stream << "============================================================" << std::endl;
	for (auto& [key, value] : m_Items)
	{
		if (value->GetParent() == nullptr)
		{
			PrintItemFamilyTree(value.get(), stream);
		}
	}
	stream << "============================================================" << std::endl;
	stream << std::endl;
	stream.close();
}

bool Scene::IsNameDupliacte(const UIString& name)
{
	for (auto& [key, value] : m_Items)
	{
		if (key == name) return true;
	}

	return false;
}

UIString Scene::GetItemName(UIItem* item)
{
	for (const auto& [key, value] : m_Items)
	{
		if (value.get() == item) return key;
	}

	return invalidName;
}

void Scene::PrintItemFamilyTree(UIItem* item, int stackDepth)
{
	std::string name = GetItemName(item);
	if (name == invalidName) return;
	SPACE(stackDepth * 3);
	std::cout << "-" << name << " [" << CropName(typeid(*item).name()) << "]" << std::endl;
	auto& children = item->GetChildren();
	for (int i = 0; i < children.size(); i++)
	{
		PrintItemFamilyTree(children.at(i), stackDepth + 1);
		if (i == children.size() - 1) return;
	}
}

void Scene::PrintItemFamilyTree(UIItem* item, std::ofstream& stream, int stackDepth)
{
	std::string name = GetItemName(item);
	if (name == invalidName) return;
	SSPACE(stackDepth * 3, stream);
	stream << "-" << name << " [" << CropName(typeid(*item).name()) << "]" << std::endl;
	auto& children = item->GetChildren();
	for (int i = 0; i < children.size(); i++)
	{
		PrintItemFamilyTree(children.at(i), stream, stackDepth + 1);
		if (i == children.size() - 1) return;
	}
}

UIString Scene::CropName(const UIString& name)
{
	size_t index = name.find("UI");
	UIASSERT(index != UIString::npos, "Error!!");
	UIString croppedName = name.substr(index);

	return croppedName;
}

void Scene::SortItem(const UIString& name)
{
	UIASSERT(IsNameDupliacte(name), "Non-existant name!!");
	auto& it = m_PriorityList.begin();
	UIFloat itemDepthValue = m_Items.at(name)->GetDepthValue();
	for (it; it != m_PriorityList.end(); it++)
	{
		UIFloat elementDepthValue = m_Items.at(*it)->GetDepthValue();
		std::cout << "ItemDepthValue: " << itemDepthValue << " | ElementDepthValue: " << elementDepthValue << std::endl;
		if (itemDepthValue <= elementDepthValue)
		{
			std::cout << "Break" << std::endl;
			break;
		}
	}
	m_PriorityList.insert(it, name);
}
