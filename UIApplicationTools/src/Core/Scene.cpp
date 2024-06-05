#include "Scene.h"

Scene::Scene()
{
	
}

Scene::Scene(const UIString& name)
	: m_Name(name)
{
	
}

UIItem* Scene::ReceiveItem(const UIString& name)
{
	UIASSERT(IsNameDupliacte(name), "Non-existant name!!");
	return m_Items.at(name).get();
}

void Scene::ForEach(void(*function)(UIItem* item))
{
	for (auto& [key, value] : m_Items)
	{
		function(value.get());
	}
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

	return "--INVALID--";
}

void Scene::PrintItemFamilyTree(UIItem* item, int stackDepth)
{
	std::string name = GetItemName(item);
	if (name == "--INVALID--") return;
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
	if (name == "--INVALID--") return;
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
