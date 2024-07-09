#pragma once

#include "UIDefinitions.h"

#include "Items/UIItem.h"
#include "Macros.h"

#include <fstream>
#include <functional>

class Scene
{
public:
	Scene();
	Scene(const UIString& name);
	virtual ~Scene() = default;

	template<typename T, typename ... Args>
	T* AddItem(const UIString& name, Args&& ... args)
	{
		UIASSERT(!IsNameDupliacte(name), "Duplicate Name");
		m_Items.emplace(name, CreateUIReferencePointer<T>(std::forward<Args>(args)...));
		SortItem(name);
		return Cast<T*>(m_Items.at(name).get());
	}
	void RemoveItem(UIItem* item);
	void RemoveItem(const UIString& name);
	UIItem* ReceiveItem(const UIString& name);
	void ForEach(const std::function<void(UIItem* item)>& function);
	void ForEachInPriority(const std::function<void(UIItem* item)>& function);

	void ResortItem(UIItem* item);

	virtual void Init() {};
	virtual void Update() {};

	void PrintHierarchyOnConsole();
	void PrintHierarchyOnFile(const UIString& filepath);
	
protected:
	UIString m_Name;
private:
	bool IsNameDupliacte(const UIString& name);
	void PrintItemFamilyTree(UIItem* item, int stackDepth = 0);
	void PrintItemFamilyTree(UIItem* item, std::ofstream& stream, int stackDepth = 0);
	UIString CropName(const UIString& name);
	void SortItem(const UIString& name);

	UIString GetItemName(UIItem* item);
private:
	UIHashMap<UIString, UIReferencePointer<UIItem>> m_Items;
	UIVector<UIString> m_PriorityList;
	UIVector<UIString> m_DeletionQueue;
};